#!/usr/bin/python3

import rclpy
from rclpy.node import Node
import cv2
import numpy as np
import tf2_ros
import ast
import math
import time
from collections import deque

from sensor_msgs.msg import Image, PointCloud2
from geometry_msgs.msg import PointStamped, Vector3, Pose
from cv_bridge import CvBridge, CvBridgeError
from visualization_msgs.msg import Marker, MarkerArray
from std_msgs.msg import ColorRGBA, String
from rclpy.qos import QoSDurabilityPolicy, QoSHistoryPolicy
from rclpy.qos import QoSProfile, QoSReliabilityPolicy
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
from tf2_ros import TransformException
import tf2_geometry_msgs as tfg
from geometry_msgs.msg import PointStamped, Vector3Stamped
from sensor_msgs_py import point_cloud2 as pc2

import pygame
from gtts import gTTS
from threading import Thread, Lock
import os

qos_profile = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)

class RingDetector(Node):
    elps = []

    def setup_voice(self):
        # Initialize pygame mixer for audio playback
        pygame.mixer.init()

        # Create a dictionary to store pre-generated audio files
        self.audio_files = {}
        self.audio_lock = Lock()
        self.last_voice_announcement = {}  # Track when each color was last announced
        self.voice_cooldown_time = 5.0  # Seconds between repeated announcements

        # Define colors we'll announce
        self.voice_colors = ['red', 'green', 'blue', 'yellow']

        # Pre-generate audio files
        for color in self.voice_colors:
            audio_file = f"/tmp/{color}_ring.mp3"

            # Check if the file already exists
            if not os.path.exists(audio_file):
                self.get_logger().info(f"Generating audio file for {color} ring")
                tts = gTTS(f"{color} ring detected", lang='en')
                tts.save(audio_file)

            self.audio_files[color] = audio_file

    def announce_color(self, color):
        """Play the audio file for the specified color"""
        color = color.lower()
        if color not in self.voice_colors:
            return

        with self.audio_lock:
            try:
                # Play the audio file
                if color in self.audio_files:
                    self.get_logger().info(f"Announcing {color} ring")
                    pygame.mixer.music.load(self.audio_files[color])
                    pygame.mixer.music.play()
                    while pygame.mixer.music.get_busy():
                        pygame.time.delay(100)
            except Exception as e:
                self.get_logger().error(f"Error playing audio: {e}")

    def is_similar_ellipse(ellipse1, ellipse2, tolerance=5.0):
        """
        Compare two ellipses (cv2.fitEllipse format) represented as NumPy arrays.
        Returns True if all corresponding values are within the given `tolerance`.
        """
        # Convert the ellipses into NumPy arrays if they are not already

        # Convert the string into a tuple using ast.literal_eval (safer than eval)
        ellipse1 = ast.literal_eval(ellipse1)
        ellipse2 = ast.literal_eval(ellipse2)

        ellipse_str = f"{ellipse1[0][0]},{ellipse1[0][1]},{ellipse1[1][0]},{ellipse1[1][1]},{ellipse1[2]}"
        array1 = np.array([float(val) for val in ellipse_str.split(',')])

        ellipse_str = f"{ellipse2[0][0]},{ellipse2[0][1]},{ellipse2[1][0]},{ellipse2[1][1]},{ellipse2[2]}"
        array2 = np.array([float(val) for val in ellipse_str.split(',')])

        # Compare the two arrays using np.allclose with tolerance
        return np.allclose(array1, array2, atol=tolerance)

    def __init__(self):
        super().__init__('ring_detector')

        # Basic ROS stuff
        timer_frequency = 2
        timer_period = 1/timer_frequency

        # An object we use for converting images between ROS format and OpenCV format
        self.bridge = CvBridge()

        # Subscribe to the image and/or depth topic
        self.image_sub = self.create_subscription(Image, "/oakd/rgb/preview/image_raw", self.image_callback, 1)
        self.depth_sub = self.create_subscription(Image, "/oakd/rgb/preview/depth", self.depth_callback, 1)
        self.pointcloud_sub = self.create_subscription(PointCloud2, "/oakd/rgb/preview/depth/points", self.pointcloud_callback, 1)

        # Publisher for detected ring color
        self.color_pub = self.create_publisher(String, "/detected_ring_color", 10)

        # Marker publisher for RViz visualization
        self.marker_pub = self.create_publisher(MarkerArray, "/ring_markers", qos_profile)

        # Object we use for transforming between coordinate frames
        self.tf_buffer = Buffer(cache_time=rclpy.duration.Duration(seconds=10.0))
        self.tf_listener = TransformListener(self.tf_buffer, self)

        cv2.namedWindow("Binary Image", cv2.WINDOW_NORMAL)
        cv2.namedWindow("Detected contours", cv2.WINDOW_NORMAL)
        cv2.namedWindow("Detected rings", cv2.WINDOW_NORMAL)
        cv2.namedWindow("Depth window", cv2.WINDOW_NORMAL)
        cv2.namedWindow("Ring color mask", cv2.WINDOW_NORMAL)

        # Define color ranges in HSV (Hue, Saturation, Value)
        self.color_ranges = {
            'red': [(0, 100, 50), (10, 255, 255)],
            'red2': [(160, 100, 50), (180, 255, 255)],
            'green': [(40, 40, 40), (80, 255, 255)],
            'blue': [(90, 40, 40), (130, 255, 255)],
            'yellow': [(20, 100, 100), (40, 255, 255)]
        }

        # Data storage - Replace RingData class with dictionaries
        self.detected_rings = []
        self.ring_positions = {}    # Dictionary mapping position hash to position array
        self.ring_radii = {}        # Dictionary mapping position hash to radius
        self.ring_colors = {}       # Dictionary mapping position hash to color name
        self.ring_rgb = {}          # Dictionary mapping position hash to RGB color
        self.ring_last_seen = {}    # Dictionary mapping position hash to last seen timestamp
        self.ring_confidence = {}   # Dictionary mapping position hash to detection confidence
        self.ring_published = {}    # Dictionary mapping position hash to published status
        self.ring_announced = {}

        self.depth_data = None
        self.depth_width = 0
        self.depth_height = 0
        self.pointcloud_data = None

        # Parameters
        self.marker_lifetime = 420.0  # Marker lifetime in seconds (7 minutes)
        self.ring_position_threshold = 0.5  # meters, threshold for considering a ring as the same
        self.min_confidence_threshold = 2  # Number of detections needed before publishing
        self.max_detection_distance = 2.0  # Maximum distance to detect rings (meters)

        # Create timer for publishing markers (run more frequently)
        self.marker_timer = self.create_timer(0.5, self.publish_ring_markers)

        self.ring_permanently_published = {}

        self.print_counter = 0
        self.print_interval = 5

        # Create a color map for visualization
        self.color_map = {
            'red': (0, 0, 255),  # BGR
            'green': (0, 255, 0),
            'blue': (255, 0, 0),
            'yellow': (0, 255, 255)
        }

        self.get_logger().info("Ring detector node initialized. Publishing markers to /ring_markers")

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

    def position_hash(self, position):
        """Create a simple hash from a position to use as a ring identifier"""
        # Use coarser resolution (0.1m instead of 0.01m) to better group similar positions
        return f"{position[0]:.1f}_{position[1]:.1f}_{position[2]:.1f}"

    def get_point_cloud_position(self, x, y, r):
        """Get 3D position of ring center from point cloud data"""
        if self.pointcloud_data is None:
            return None

        try:
            # Convert point cloud to numpy array
            pc_array = pc2.read_points_numpy(
                self.pointcloud_data,
                field_names=("x", "y", "z")
            ).reshape((self.pointcloud_data.height, self.pointcloud_data.width, 3))

            # Sample points around the ring
            ring_points = []
            num_samples = 12  # Increased from 8 to 12 for better accuracy
            for angle in np.linspace(0, 2*np.pi, num_samples, endpoint=False):
                px = int(x + r * 0.8 * np.cos(angle))  # Sample at 80% of radius to get on the ring
                py = int(y + r * 0.8 * np.sin(angle))

                # Check if point is within image bounds
                if 0 <= px < self.pointcloud_data.width and 0 <= py < self.pointcloud_data.height:
                    point = pc_array[py, px]
                    if np.isfinite(point).all() and not np.isnan(point).any():
                        ring_points.append(point)

            # If we have enough points, compute the median position
            if len(ring_points) >= 4:  # Increased from 3 to 4 for better accuracy
                ring_position = np.median(np.array(ring_points), axis=0)
                return ring_position

            return None

        except Exception as e:
            self.get_logger().error(f"Error extracting point cloud data: {e}")
            return None

    def find_matching_ring(self, position):
        """Find if a ring already exists near the given position"""
        for ring_hash, ring_position in self.ring_positions.items():
            distance = np.linalg.norm(position - ring_position)
            if distance < self.ring_position_threshold:
                return ring_hash
        return None

    def update_ring(self, position, radius_px, color_name, color_rgb):
        """Update ring data in storage, create new entry if needed"""
        # Check if this ring is already in our dictionary by checking if it's near an existing ring
        matched_hash = self.find_matching_ring(position)
        current_time = time.time()

        # Get robot position
        robot_position = self.get_robot_position()

        # Calculate distance to ring if robot position is available
        distance_to_ring = None
        if robot_position is not None:
            distance_to_ring = np.linalg.norm(position - robot_position)

        # If matching ring found, update its data
        if matched_hash:

            if matched_hash in self.ring_permanently_published and self.ring_permanently_published[matched_hash]:
                # If it's permanently published, don't update anything
                return matched_hash

            # Update position with some smoothing
            smoothing = 0.2
            self.ring_positions[matched_hash] = (1 - smoothing) * self.ring_positions[matched_hash] + smoothing * position
            self.ring_last_seen[matched_hash] = current_time

            # Increase confidence counter
            self.ring_confidence[matched_hash] += 1

            # Update color if it changed
            if self.ring_colors[matched_hash] != color_name:
                self.ring_colors[matched_hash] = color_name
                self.ring_rgb[matched_hash] = color_rgb

            # Publish permanently if we reach the threshold and haven't published yet
            if (self.ring_confidence[matched_hash] >= self.min_confidence_threshold and not self.ring_published[matched_hash]):
                self.ring_published[matched_hash] = True
                self.ring_permanently_published[matched_hash] = True
                self.get_logger().info(f"PERMANENTLY publishing {color_name} ring marker")

                if matched_hash not in self.ring_announced or not self.ring_announced[matched_hash]:
                    # Announce the color only if we haven't announced it yet
                    Thread(target=self.announce_color, args=(color_name,)).start()
                    self.ring_announced[matched_hash] = True

            # Log distance information if available
            # if distance_to_ring is not None:
            #     self.get_logger().debug(f"Distance to {color_name} ring: {distance_to_ring:.2f}m")

                # If we're close enough and have enough confidence, mark ring for publishing
            #    if (distance_to_ring < self.max_detection_distance and
            #        self.ring_confidence[matched_hash] >= self.min_confidence_threshold and
            #        not self.ring_published[matched_hash]):
            #        self.ring_published[matched_hash] = True
            #        self.get_logger().info(f"Now publishing {color_name} ring marker")

            return matched_hash
        else:
            # Create new ring entry
            pos_hash = self.position_hash(position)
            self.ring_positions[pos_hash] = position
            self.ring_radii[pos_hash] = radius_px * 0.002  # Convert pixels to approximate meters
            self.ring_colors[pos_hash] = color_name
            self.ring_rgb[pos_hash] = color_rgb
            self.ring_last_seen[pos_hash] = current_time
            self.ring_confidence[pos_hash] = 1
            self.ring_published[pos_hash] = False  # Don't publish immediately
            self.ring_permanently_published[pos_hash] = False  # Not permanently published yet

            self.ring_announced[pos_hash] = False

            # If we're already very close and confident, mark for immediate publishing
            #if distance_to_ring is not None and distance_to_ring < 0.8:
            #    self.ring_confidence[pos_hash] = self.min_confidence_threshold
            #    self.ring_published[pos_hash] = True

            return pos_hash

    def clean_old_rings(self):
        """Remove rings that haven't been seen for a while"""
        current_time = time.time()
        rings_to_remove = []

        for ring_hash in self.ring_positions.keys():
            # Only remove unpublished rings after 30 seconds
            if (not self.ring_published[ring_hash] and not (ring_hash in self.ring_permanently_published and self.ring_permanently_published[ring_hash]) and current_time - self.ring_last_seen[ring_hash] > 30.0):
                rings_to_remove.append(ring_hash)

        for ring_hash in rings_to_remove:
            self.ring_positions.pop(ring_hash)
            self.ring_radii.pop(ring_hash)
            self.ring_colors.pop(ring_hash)
            self.ring_rgb.pop(ring_hash)
            self.ring_last_seen.pop(ring_hash)
            self.ring_confidence.pop(ring_hash)
            self.ring_published.pop(ring_hash)

            if ring_hash in self.ring_permanently_published:
                self.ring_permanently_published.pop(ring_hash)

        if rings_to_remove:
            self.get_logger().info(f"Removed {len(rings_to_remove)} old unpublished rings")

    def publish_ring_markers(self):
        """Publish markers for all tracked rings"""
        # First clean up old rings
        self.clean_old_rings()

        if not self.ring_positions:
            return

        marker_array = MarkerArray()

        for ring_hash in self.ring_positions.keys():
            # Only publish markers for rings that have been confirmed
            if not self.ring_published[ring_hash]:
                continue

            # Get ring data
            position = self.ring_positions[ring_hash]
            radius = self.ring_radii[ring_hash]
            color_name = self.ring_colors[ring_hash]
            color_rgb = self.ring_rgb[ring_hash]

            # Ring position marker (sphere)
            ring_marker = Marker()
            ring_marker.header.frame_id = "map"
            ring_marker.header.stamp = self.get_clock().now().to_msg()
            ring_marker.ns = "ring_positions"
            ring_marker.id = hash(ring_hash) % 10000  # Use hash for ID
            ring_marker.type = Marker.SPHERE
            ring_marker.action = Marker.ADD
            ring_marker.pose.position.x = position[0]
            ring_marker.pose.position.y = position[1]
            ring_marker.pose.position.z = position[2]
            ring_marker.pose.orientation.w = 1.0

            ring_marker.scale.x = ring_marker.scale.y = ring_marker.scale.z = 0.15

            # Set color (BGR to RGB)
            b, g, r = color_rgb
            ring_marker.color.r = float(r) / 255.0
            ring_marker.color.g = float(g) / 255.0
            ring_marker.color.b = float(b) / 255.0
            ring_marker.color.a = 0.8


            ring_marker.lifetime.sec = 0
            # Set lifetime
            #if self.marker_lifetime > 0:
            #    ring_marker.lifetime.sec = int(self.marker_lifetime)
            #    ring_marker.lifetime.nanosec = int((self.marker_lifetime % 1) * 1e9)

            marker_array.markers.append(ring_marker)

            # Text marker for color label
            text_marker = Marker()
            text_marker.header.frame_id = "map"
            text_marker.header.stamp = self.get_clock().now().to_msg()
            text_marker.ns = "ring_colors"
            text_marker.id = hash(ring_hash) % 10000  # Use hash for ID
            text_marker.type = Marker.TEXT_VIEW_FACING
            text_marker.action = Marker.ADD
            text_marker.pose.position.x = position[0]
            text_marker.pose.position.y = position[1]
            text_marker.pose.position.z = position[2] + 0.15  # Above the sphere
            text_marker.pose.orientation.w = 1.0
            text_marker.scale.z = 0.15  # Text size
            text_marker.color.r = 1.0
            text_marker.color.g = 1.0
            text_marker.color.b = 1.0
            text_marker.color.a = 1.0
            text_marker.text = color_name.upper()


            text_marker.lifetime.sec = 0
            #if self.marker_lifetime > 0:
            #    text_marker.lifetime.sec = int(self.marker_lifetime)
            #    text_marker.lifetime.nanosec = int((self.marker_lifetime % 1) * 1e9)

            marker_array.markers.append(text_marker)

        # Publish the marker array
        self.marker_pub.publish(marker_array)

    def pointcloud_callback(self, data):
        """Store the latest point cloud data"""
        self.pointcloud_data = data

    def image_callback(self, data):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)

        # Transform image to grayscale
        gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)

        # Binarize the image
        thresh = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 15, 30)
        cv2.imshow("Binary Image", thresh)
        cv2.waitKey(1)

        # Extract contours
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

        # Visualize contours
        contour_image = gray.copy()
        cv2.drawContours(contour_image, contours, -1, (255, 0, 0), 3)
        cv2.imshow("Detected contours", contour_image)
        cv2.waitKey(1)

        local_elps = []

        # Fit ellipses to all extracted contours
        for cnt in contours:
            if cnt.shape[0] >= 8:
                ellipse = cv2.fitEllipse(cnt)
                local_elps.append(ellipse)

        # Find two ellipses with same centers
        candidates = []
        for n in range(len(local_elps)):
            e1 = local_elps[n]

            for i in self.elps:
                array1 = [e1[0][0], e1[0][1]]
                array2 = [i[0][0], i[0][1]]
                arr3 = [e1[1][0], e1[1][1], e1[2]]
                arr4 = [i[1][0], i[1][1], i[2]]

                if (np.allclose(array1, array2, atol=10.0) and (np.allclose(arr3, arr4, atol=10.0))):
                    candidates.append(e1)
                    # Always print matched ellipses
                    print(f"Matched ellipse at ({e1[0][0]:.1f}, {e1[0][1]:.1f})")

        # Increment print counter
        self.print_counter += 1

        # Convert BGR to HSV for better color detection
        hsv_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2HSV)

        # Create a copy for visualization
        ring_color_image = cv_image.copy()

        # Clear previous detections for this frame
        current_frame_detections = []

        # Process each candidate ellipse
        for c in candidates:
            e1 = c

            # Draw the ellipse on the visualization image
            cv2.ellipse(ring_color_image, e1, (0, 255, 0), 2)

            # Calculate the size of the ellipse (the marker)
            size = (e1[1][0] + e1[1][1]) / 2
            center = (int(e1[0][0]), int(e1[0][1]))

            # Create a mask for the outer ring region (larger than the marker)
            # Scale up the marker ellipse to find the ring
            outer_mask = np.zeros(cv_image.shape[:2], dtype=np.uint8)
            outer_scale = 1.5  # Make outer mask 150% of the marker size
            cv2.ellipse(outer_mask, (center, (int(e1[1][0]*outer_scale), int(e1[1][1]*outer_scale)), e1[2]), (255), -1)

            # Create a mask for the inner region (the marker and any space inside)
            inner_mask = np.zeros(cv_image.shape[:2], dtype=np.uint8)
            inner_scale = 1.1  # Make inner mask 110% of the marker size to include the marker itself
            cv2.ellipse(inner_mask, (center, (int(e1[1][0]*inner_scale), int(e1[1][1]*inner_scale)), e1[2]), (255), -1)

            # Subtract the inner mask from the outer mask to get just the ring area
            ring_mask = cv2.subtract(outer_mask, inner_mask)

            # Apply the ring mask to get only the ring region
            ring_hsv = cv2.bitwise_and(hsv_image, hsv_image, mask=ring_mask)

            # Show the mask for debugging
            cv2.imshow("Ring color mask", ring_mask)
            cv2.waitKey(1)

            # Count pixels of each color in the masked region
            color_counts = {}
            for color_name, (lower, upper) in self.color_ranges.items():
                if color_name == 'red2':  # Skip the second red range for counting
                    continue

                # Create mask for this color
                color_mask = cv2.inRange(ring_hsv, np.array(lower), np.array(upper))

                # Special case for red (which wraps around in HSV)
                if color_name == 'red':
                    red2_lower, red2_upper = self.color_ranges['red2']
                    red2_mask = cv2.inRange(ring_hsv, np.array(red2_lower), np.array(red2_upper))
                    color_mask = cv2.bitwise_or(color_mask, red2_mask)

                # Count non-zero pixels
                color_count = cv2.countNonZero(color_mask)
                color_counts[color_name] = color_count

            # Find the dominant color
            total_pixels = sum(color_counts.values())
            if total_pixels > 10:  # Reduced threshold since we're looking at a smaller area
                dominant_color = max(color_counts, key=color_counts.get)
                color_percentage = (color_counts[dominant_color] / total_pixels) * 100

                # Reduced threshold for better detection
                if color_percentage > 15:  # Reduced from 20% to 15%
                    # Always print color detection
                    print(f"Ring detected with color: {dominant_color} ({color_percentage:.1f}%)")

                    # Draw the color name on the image
                    cv2.putText(ring_color_image, dominant_color,
                                (center[0] - 20, center[1]),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 2)

                    # Publish color information
                    color_msg = String()
                    color_msg.data = dominant_color
                    self.color_pub.publish(color_msg)

                    #OVDE SAM DODAO
                    # Thread(target=self.announce_color, args=(dominant_color,)).start()

                    # Get the RGB color for visualization
                    color_rgb = self.color_map.get(dominant_color, (128, 128, 128))

                    # Store the detected ring with its color and position
                    current_frame_detections.append((e1, dominant_color))

                    # Get 3D position if we have point cloud data
                    if self.pointcloud_data is not None:
                        position_3d = self.get_point_cloud_position(center[0], center[1], size/2)

                        # If we got a 3D position, transform to map frame and update ring database
                        if position_3d is not None:
                            map_position = self.transform_point_to_map(position_3d)

                            if map_position is not None:
                                # Check for existing rings and update with more stability
                                ring_hash = self.update_ring(map_position, size/2, dominant_color, color_rgb)

                                # Get confidence level
                                confidence = self.ring_confidence[ring_hash]
                                published = self.ring_published[ring_hash]
                                status = "PUBLISHED" if published else f"CONFIDENCE {confidence}/{self.min_confidence_threshold}"

                                self.get_logger().info(
                                    f"{dominant_color.upper()} ring detected at "
                                    f"({center[0]}, {center[1]}) with size {size}, map position: "
                                    f"({map_position[0]:.2f}, {map_position[1]:.2f}, {map_position[2]:.2f}) {status}"
                                )
                    else:
                        self.get_logger().warn("No point cloud data available for 3D positioning")

        self.detected_rings = current_frame_detections

        cv2.imshow("Detected rings", ring_color_image)
        cv2.waitKey(1)

        if self.detected_rings:
            print("\n===== Currently detected rings =====")
            for i, (ring_ellipse, ring_color) in enumerate(self.detected_rings):
                center_x, center_y = ring_ellipse[0]
                print(f"Ring {i+1}: Color {ring_color}, Position: ({center_x:.1f}, {center_y:.1f})")
            print("==================================\n")

    def depth_callback(self, data):
        self.elps = []

        try:
            depth_image = self.bridge.imgmsg_to_cv2(data, "32FC1")
            self.depth_data = depth_image  # Store for point cloud processing
            self.depth_height, self.depth_width = depth_image.shape
        except CvBridgeError as e:
            print(e)

        depth_image = np.nan_to_num(depth_image, nan=0.0, posinf=0.0, neginf=0.0)

        if np.max(depth_image) > 0:
            image_1 = depth_image / 65536.0 * 255
            image_1 = image_1/np.max(image_1)*255
        else:
            image_1 = depth_image * 0  # All zeros

        image_viz = np.array(image_1, dtype=np.uint8)

        cv2.imshow("Depth window", image_viz)
        cv2.waitKey(1)

        black_mask = image_viz == 0
        output = np.where(black_mask, 0, 255).astype(np.uint8)

        thresh = cv2.adaptiveThreshold(output, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 15, 30)
        cv2.imshow("Binary Image depth", thresh)
        cv2.waitKey(1)

        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

        for cnt in contours:
            if cnt.shape[0] >= 5:
                try:
                    ellipse = cv2.fitEllipse(cnt)

                    if any(np.isnan(np.array(ellipse[0]))) or any(np.isnan(np.array(ellipse[1]))) or np.isnan(ellipse[2]):
                        continue

                    center = tuple(map(int, ellipse[0]))

                    if not all(np.isfinite(np.array(center))):
                        continue

                    center0 = center[0]
                    center1 = center[1]

                    if center0 <= 0 or center1 <= 0 or center0 >= output.shape[1]-1 or center1 >= output.shape[0]-1:
                        continue

                    color_value = output[center1, center0]

                    if ellipse not in self.elps and color_value == 0:
                        self.elps.append(ellipse)

                except Exception as e:
                    print(f"Error processing ellipse: {e}")
                    continue

        cv2.imshow("Detected contours depth", output)
        cv2.waitKey(1)


def main():
    rclpy.init(args=None)
    rd_node = RingDetector()

    try:
        rclpy.spin(rd_node)
    except Exception as e:
        print(f"Error in main loop: {e}")
    finally:
        # Clean shutdown
        cv2.destroyAllWindows()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
