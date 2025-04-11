#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data, QoSReliabilityPolicy
from rclpy.qos import QoSProfile, QoSDurabilityPolicy, QoSHistoryPolicy

from sensor_msgs.msg import Image, PointCloud2
from sensor_msgs_py import point_cloud2 as pc2

from geometry_msgs.msg import PointStamped, Vector3, Pose, Quaternion
from turtle_tf2_py.turtle_tf2_broadcaster import quaternion_from_euler

from visualization_msgs.msg import Marker, MarkerArray

import tf2_geometry_msgs as tfg
from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener

from cv_bridge import CvBridge, CvBridgeError
import cv2
import numpy as np
import os
import time

from ultralytics import YOLO

import math

import pygame
from gtts import gTTS
from threading import Thread, Lock
import os
import time

# Define QoS profile for persistent markers
qos_profile = QoSProfile(
    durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
    reliability=QoSReliabilityPolicy.RELIABLE,
    history=QoSHistoryPolicy.KEEP_LAST,
    depth=1)

class DetectFaces(Node):

    def __init__(self, logimages=False):
        super().__init__('detect_faces')

        self.declare_parameters(
            namespace='',
            parameters=[
                ('device', ''),
            ]
        )

        # Audio setup
        pygame.mixer.init()
        self.audio_files = {}
        self.audio_lock = Lock()
        self.last_voice_announcement = {}
        self.voice_cooldown_time = 5.0

        audio_file = f"/tmp/hello.mp3"
        if not os.path.exists(audio_file):
            self.get_logger().info(f"Generating audio file for hello")
            tts = gTTS(f"Hello, nice to meet you", lang='en')
            tts.save(audio_file)
        self.audio_files["hello"] = audio_file

        # Detection setup
        self.logimages = logimages
        self.detection_color = (0, 0, 255)
        self.device = self.get_parameter('device').get_parameter_value().string_value

        self.bridge = CvBridge()
        self.scan = None

        # Subscriptions
        self.rgb_image_sub = self.create_subscription(Image, "/oakd/rgb/preview/image_raw", self.rgb_callback, qos_profile_sensor_data)
        self.pointcloud_sub = self.create_subscription(PointCloud2, "/oakd/rgb/preview/depth/points", self.pointcloud_callback, qos_profile_sensor_data)

        # Publishers using the persistent QoS profile
        self.face_marker_pub = self.create_publisher(MarkerArray, "/face_markers", qos_profile)
        self.greeting_marker_pub = self.create_publisher(MarkerArray, "/greeting_markers", qos_profile)

        self.greeting_position = self.create_publisher(Marker, "/greeting_position", qos_profile)

        # New publisher specifically for RViz display
        self.rviz_image_pub = self.create_publisher(
            Image, "/face_detection_rviz", 10)

        # Load YOLO model
        map_path = "yolov8n.pt"
        self.validator = YOLO(map_path)

        # Data storage
        self.pc_data = None
        self.faces = []
        self.face_positions = {}  # Dictionary mapping position hash to position array
        self.face_published = {}  # Dictionary mapping position hash to published status
        self.face_permanently_published = {}  # Dictionary for faces that have been permanently published
        self.face_confidence = {}  # Dictionary mapping position hash to detection confidence
        self.face_last_seen = {}  # Dictionary mapping position hash to last seen timestamp
        self.face_rgb = {}  # Dictionary for RGB color
        self.idx_save = 0

        # Parameters
        self.min_confidence_threshold = 3  # Number of detections needed before publishing
        self.face_position_threshold = 1.0  # meters, threshold for considering a face as the same
        self.marker_lifetime = 0  # 0 means markers persist until explicitly deleted
        self.max_detection_distance = 2.5  # meters, max distance for face detection

        # New variable for face display window
        self.current_face_display = None  # Will hold current face for zoomed display
        self.current_face_image = None  # Will hold current face for publishing
        self.rviz_photo = None

        # Create face images directory if it doesn't exist
        self.face_images_dir = "/tmp/face_images"
        os.makedirs(self.face_images_dir, exist_ok=True)

        # Setup TF2 for transformations
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # Create timer for publishing markers
        self.marker_timer = self.create_timer(0.5, self.publish_face_markers)

    def announce_hello(self):
        """Play the hello audio file"""
        hello = "hello"
        with self.audio_lock:
            try:
                if hello in self.audio_files:
                    self.get_logger().info(f"Announcing HELLO")
                    pygame.mixer.music.load(self.audio_files[hello])
                    pygame.mixer.music.play()
                    while pygame.mixer.music.get_busy():
                        pygame.time.delay(100)
            except Exception as e:
                self.get_logger().error(f"Error playing audio: {e}")

    def map_class_type(self, clss):
        if clss in [0]:  # Person class in YOLO
            return 0
        else:
            return 1  # Other objects

    def position_hash(self, position):
        """Create a simple hash from a position to use as a face identifier"""
        # Use coarser resolution (0.1m instead of 0.01m) to better group similar positions
        return f"{position[0]:.1f}_{position[1]:.1f}_{position[2]:.1f}"

    def find_matching_face(self, position):
        """Find if a face already exists near the given position"""
        for face_hash, face_position in self.face_positions.items():
            distance = np.linalg.norm(position - face_position)
            print(f"Distance to {face_hash}: {distance:.2f}m")
            if distance < self.face_position_threshold:
                return face_hash
        return None

    def update_face(self, position, face_class):
        """Update face data in storage, create new entry if needed"""
        # Check if this face is already in our dictionary
        matched_hash = self.find_matching_face(position)
        current_time = time.time()

        # Set color based on class (person vs other)
        if face_class == 0:  # Person
            color_name = "person"
            color_rgb = (255, 0, 255)  # Magenta in BGR
        else:  # Painting or other object
            color_name = "object"
            color_rgb = (255, 255, 0)  # Yellow in BGR
        

        robot_position = self.get_robot_position()

        # Calculate distance to ring if robot position is available
        distance_to_face = None
        if robot_position is not None:
            distance_to_face = np.linalg.norm(position - robot_position)
            #print(distance_to_ring)
            if distance_to_face  > self.max_detection_distance:
                # If the ring is too far, ignore it
                return None

        # If matching face found, update its data
        if matched_hash:
            if matched_hash in self.face_permanently_published and self.face_permanently_published[matched_hash]:
                # If it's permanently published, don't update anything
                return matched_hash

            # Update position with some smoothing
            smoothing = 0.2
            self.face_positions[matched_hash] = (1 - smoothing) * self.face_positions[matched_hash] + smoothing * position
            self.face_last_seen[matched_hash] = current_time

            # Increase confidence counter
            self.face_confidence[matched_hash] += 1

            # Publish permanently if we reach the threshold and haven't published yet
            if (self.face_confidence[matched_hash] >= self.min_confidence_threshold and
                not self.face_published[matched_hash]):
                print(self.face_published[matched_hash])
                self.face_published[matched_hash] = True
                
                #self.get_logger().info(f"PERMANENTLY publishing {color_name} face marker")

                # Announce hello only once
                if not self.face_permanently_published.get(matched_hash, False):
                    #Thread(target=self.announce_hello).start()
                    self.face_permanently_published[matched_hash] = True
                    Thread(target=self.wait_before_publish).start()

            return matched_hash
        else:
            # Create new face entry
            pos_hash = self.position_hash(position)
            self.face_positions[pos_hash] = position
            self.face_last_seen[pos_hash] = current_time
            self.face_confidence[pos_hash] = 1
            self.face_published[pos_hash] = False  # Don't publish immediately
            self.face_permanently_published[pos_hash] = False  # Not permanently published yet
            self.face_rgb[pos_hash] = color_rgb

            return pos_hash
    
    def wait_before_publish(self):
        time.sleep(2)
        self.rviz_image_pub.publish(self.rviz_photo)

    def get_robot_position(self):
        """Get the current position of the robot in the map frame"""
        try:
            # Get transform from base_link to map
            transform = self.tf_buffer.lookup_transform(
                "map",
                "base_link",
                rclpy.time.Time(),
                rclpy.duration.Duration(seconds=1.0)
            )

            return np.array([
                transform.transform.translation.x,
                transform.transform.translation.y,
                transform.transform.translation.z
            ])
        except TransformException as e:
            self.get_logger().warn(f"Could not get robot position: {e}")
            return None

    def transform_point_to_map(self, point_3d):
        """Transform a point from camera frame to map frame"""
        try:
            # Create PointStamped object
            point_stamped = PointStamped()
            point_stamped.header.frame_id = "base_link"
            point_stamped.header.stamp = self.get_clock().now().to_msg()
            point_stamped.point.x = float(point_3d[0])
            point_stamped.point.y = float(point_3d[1])
            point_stamped.point.z = float(point_3d[2])

            # Get latest transform
            transform = self.tf_buffer.lookup_transform(
                "map",
                "base_link",
                rclpy.time.Time(),  # Get latest transform
                rclpy.duration.Duration(seconds=1.0)
            )

            # Transform the point
            transformed_point = tfg.do_transform_point(point_stamped, transform)

            return np.array([
                transformed_point.point.x,
                transformed_point.point.y,
                transformed_point.point.z
            ])

        except TransformException as e:
            self.get_logger().warn(f"Could not transform point: {e}")
            return None

    def clean_old_faces(self):
        """Remove faces that haven't been seen for a while"""
        current_time = time.time()
        faces_to_remove = []

        for face_hash in self.face_positions.keys():
            # Only remove unpublished faces after 30 seconds
            if (not self.face_published[face_hash] and
                not (face_hash in self.face_permanently_published and self.face_permanently_published[face_hash]) and
                current_time - self.face_last_seen[face_hash] > 30.0):
                faces_to_remove.append(face_hash)

        for face_hash in faces_to_remove:
            self.face_positions.pop(face_hash)
            self.face_last_seen.pop(face_hash)
            self.face_confidence.pop(face_hash)
            self.face_published.pop(face_hash)
            if face_hash in self.face_permanently_published:
                self.face_permanently_published.pop(face_hash)
            if face_hash in self.face_rgb:
                self.face_rgb.pop(face_hash)

        if faces_to_remove:
            self.get_logger().info(f"Removed {len(faces_to_remove)} old unpublished faces")

    def get_face_position_from_pointcloud(self, x, y):
        """Get 3D position of face center from point cloud data"""
        if self.pc_data is None:
            return None

        try:
            # Convert point cloud to numpy array
            pc_array = pc2.read_points_numpy(
                self.pc_data,
                field_names=("x", "y", "z")
            ).reshape((self.pc_data.height, self.pc_data.width, 3))

            # Sample a region around the face center (5x5 pixels)
            region_size = 2  # This gives a 5x5 region
            region_points = []

            for dy in range(-region_size, region_size + 1):
                for dx in range(-region_size, region_size + 1):
                    px = x + dx
                    py = y + dy

                    # Check if point is within image bounds
                    if (0 <= px < self.pc_data.width and
                        0 <= py < self.pc_data.height):
                        point = pc_array[py, px]
                        # Filter out invalid points
                        if np.isfinite(point).all() and not np.isnan(point).any():
                            region_points.append(point)

            # If we have enough points, compute the median position
            if len(region_points) >= 5:  # Need enough valid points
                face_position = np.median(np.array(region_points), axis=0)
                return face_position

            return None

        except Exception as e:
            self.get_logger().error(f"Error extracting point cloud data: {e}")
            return None

    def publish_face_markers(self):
        """Publish markers for all tracked faces"""
        # First clean up old faces
        self.clean_old_faces()

        if not self.face_positions:
            return

        marker_array = MarkerArray()
        greeting_marker_array = MarkerArray()

        for face_hash in self.face_positions.keys():
            # Only publish markers for faces that have been confirmed
            if not self.face_published[face_hash]:
                continue

            # Get face data
            position = self.face_positions[face_hash]
            color_rgb = self.face_rgb.get(face_hash, (255, 0, 255))  # Default to magenta

            # Face position marker (cube)
            face_marker = Marker()
            face_marker.header.frame_id = "map"
            face_marker.header.stamp = self.get_clock().now().to_msg()
            face_marker.ns = "face_positions"
            face_marker.id = hash(face_hash) % 10000  # Use hash for ID
            face_marker.type = Marker.CUBE
            face_marker.action = Marker.ADD
            face_marker.pose.position.x = position[0]
            face_marker.pose.position.y = position[1]
            face_marker.pose.position.z = position[2]
            face_marker.pose.orientation.w = 1.0

            face_marker.scale.x = face_marker.scale.y = face_marker.scale.z = 0.25

            # Set color (BGR to RGB)
            b, g, r = color_rgb
            face_marker.color.r = 0.0
            face_marker.color.g = 0.0
            face_marker.color.b = 0.0
            face_marker.color.a = 1.0

            # Set lifetime (0 means persist indefinitely)
            face_marker.lifetime.sec = self.marker_lifetime

            marker_array.markers.append(face_marker)

            # Text marker for color label
            text_marker = Marker()
            text_marker.header.frame_id = "map"
            text_marker.header.stamp = self.get_clock().now().to_msg()
            text_marker.ns = "face_sign"
            text_marker.id = hash(face_hash) % 10000  # Use hash for ID
            text_marker.type = Marker.TEXT_VIEW_FACING
            text_marker.action = Marker.ADD
            text_marker.pose.position.x = position[0] + 0.25
            text_marker.pose.position.y = position[1]
            text_marker.pose.position.z = position[2] + 0.15  # Above the sphere
            text_marker.pose.orientation.w = 1.0
            text_marker.scale.z = 0.2  # Text size
            text_marker.color.r = 0.0
            text_marker.color.g = 0.0
            text_marker.color.b = 0.0
            text_marker.color.a = 1.0
            text_marker.text = "IMAGE"


            text_marker.lifetime.sec = 0
            #if self.marker_lifetime > 0:
            #    text_marker.lifetime.sec = int(self.marker_lifetime)
            #    text_marker.lifetime.nanosec = int((self.marker_lifetime % 1) * 1e9)

            marker_array.markers.append(text_marker)

            # Calculate greeting point (1m in front of the face)
            # First, we need robot position to get direction vector
            robot_pos = self.get_robot_position()
            if robot_pos is not None:
                # Vector from robot to face
                direction = position - robot_pos
                direction_xy = direction.copy()
                direction_xy[2] = 0  # Keep only x,y components

                # Normalize and scale to 1m
                if np.linalg.norm(direction_xy) > 0:
                    greeting_direction = direction_xy / np.linalg.norm(direction_xy)
                    greeting_point = position - greeting_direction * 1.0  # 1m in front of face

                    # Calculate orientation (angle facing the face)
                    angle = np.arctan2(direction_xy[1], direction_xy[0])
                    quat = quaternion_from_euler(0, 0, angle)

                    # Create greeting marker (arrow)
                    greeting_marker = Marker()
                    greeting_marker.header.frame_id = "map"
                    greeting_marker.header.stamp = self.get_clock().now().to_msg()
                    greeting_marker.ns = "greeting_positions"
                    greeting_marker.id = hash(face_hash) % 10000
                    greeting_marker.type = Marker.ARROW
                    greeting_marker.action = Marker.ADD
                    greeting_marker.pose.position.x = greeting_point[0]
                    greeting_marker.pose.position.y = greeting_point[1]
                    greeting_marker.pose.position.z = greeting_point[2]
                    greeting_marker.pose.orientation.x = quat[0]
                    greeting_marker.pose.orientation.y = quat[1]
                    greeting_marker.pose.orientation.z = quat[2]
                    greeting_marker.pose.orientation.w = quat[3]

                    greeting_marker.scale.x = 0.5  # Arrow length
                    greeting_marker.scale.y = 0.1  # Arrow width
                    greeting_marker.scale.z = 0.1  # Arrow height

                    greeting_marker.color.r = 0.0
                    greeting_marker.color.g = 1.0
                    greeting_marker.color.b = 1.0
                    greeting_marker.color.a = 1.0

                    greeting_marker.lifetime.sec = self.marker_lifetime

                    greeting_marker_array.markers.append(greeting_marker)
                    self.greeting_position.publish(greeting_marker)

        # Publish the marker arrays
        if marker_array.markers:
            self.face_marker_pub.publish(marker_array)

        if greeting_marker_array.markers:
            self.greeting_marker_pub.publish(greeting_marker_array)

    
    def rgb_callback(self, msg):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")
            results = self.validator.predict(
                cv_image, imgsz=(256, 320),
                show=False, verbose=False,
                classes=[0], device=self.device)

            current_frame_faces = []

            # Create black image for face display in case no faces are detected
            black_image = np.zeros((300, 300, 3), dtype=np.uint8)
            self.current_face_display = black_image  # Default to black if no face

            # Draw detections on the main camera view for debugging
            debug_image = cv_image.copy()
            cx = 0.0
            cy = 0.0

            for result in results:
                for box in result.boxes.xyxy:
                    if box.nelement() == 0:
                        continue

                    # Extract box coordinates
                    x1, y1, x2, y2 = box[0].item(), box[1].item(), box[2].item(), box[3].item()

                    # Calculate center of bounding box
                    cx = int((x1 + x2) / 2)
                    cy = int((y1 + y2) / 2)
                    current_frame_faces.append((cx, cy, (x1, y1, x2, y2)))

                    # Draw detection on debug image (not on the clean face view)
                    cv2.rectangle(debug_image,
                                (int(x1), int(y1)),
                                (int(x2), int(y2)),
                                (0, 0, 255), 2)
                    cv2.circle(debug_image, (cx, cy), 5, (0, 0, 255), -1)

                    # Extract face for zoomed window (use first detected face)
                    if self.current_face_display is black_image:  # Only use first face
                        # Extract face - clean with no markings
                        face_img = cv_image[int(y1):int(y2), int(x1):int(x2)].copy()

                        # Resize to standard size (300x300) for display
                        self.current_face_display = cv2.resize(face_img, (300, 300))

                    

                    self.process_face_position(cx, cy, 0)

            rviz_msg = self.bridge.cv2_to_imgmsg(self.current_face_display, "bgr8")
            rviz_msg.header = msg.header
            rviz_msg.header.frame_id = "map"  # Use map frame for RViz display
            self.rviz_photo = rviz_msg

            cv2.imshow("Face Detection", debug_image)
            cv2.waitKey(1)

        except CvBridgeError as e:
            self.get_logger().error(f"CV Bridge error: {e}")

    def pointcloud_callback(self, data):
        """Store the latest point cloud data"""
        self.pc_data = data

    def process_face_position(self, cx, cy, face_class):
        """Process face detection and update 3D position"""
        if self.pc_data is None:
            return

        # Get 3D position from point cloud
        position_3d = self.get_face_position_from_pointcloud(cx, cy)

        # If we got a valid 3D position, transform to map frame
        if position_3d is not None:
            map_position = self.transform_point_to_map(position_3d)

            if map_position is not None:
                # Update face tracking database
                face_hash = self.update_face(map_position, face_class)

                # Get confidence level
                confidence = self.face_confidence[face_hash]
                published = self.face_published[face_hash]
                is_permanent = face_hash in self.face_permanently_published and self.face_permanently_published[face_hash]

                # Log status
                if is_permanent:
                    status = f"PERMANENTLY PUBLISHED with hash {face_hash}"
                elif published:
                    status = f"PUBLISHED with hash {face_hash}"
                else:
                    status = f"CONFIDENCE {confidence}/{self.min_confidence_threshold} with hash {face_hash}"

                # Only log when confidence increases or status changes
                if confidence <= self.min_confidence_threshold or is_permanent != self.face_permanently_published.get(face_hash, False):
                    self.get_logger().info(
                        f"Face detected at ({cx}, {cy}), map position: "
                        f"({map_position[0]:.2f}, {map_position[1]:.2f}, {map_position[2]:.2f}) {status}"
                    )

def main():
    print('Face detection node starting with RViz markers.')

    rclpy.init(args=None)
    node = DetectFaces()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
