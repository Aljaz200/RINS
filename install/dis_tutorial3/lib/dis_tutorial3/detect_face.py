#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data, QoSReliabilityPolicy
from geometry_msgs.msg import Point, PoseStamped, Twist, PointStamped, PoseWithCovarianceStamped
from sensor_msgs.msg import Image, PointCloud2
from sensor_msgs_py import point_cloud2 as pc2
from visualization_msgs.msg import Marker
from cv_bridge import CvBridge, CvBridgeError
import cv2
import numpy as np
from ultralytics import YOLO
import math
from tf2_ros import Buffer, TransformListener, TransformException  # Added TransformException here
from tf2_geometry_msgs import do_transform_point
from rclpy.time import Time
from rclpy.duration import Duration
from rclpy.qos import QoSDurabilityPolicy, QoSHistoryPolicy
from rclpy.qos import QoSProfile

amcl_pose_qos = QoSProfile(
		  durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
		  reliability=QoSReliabilityPolicy.RELIABLE,
		  history=QoSHistoryPolicy.KEEP_LAST,
		  depth=1)

class FaceDetector(Node):
	def __init__(self):
		super().__init__('face_detector')
		
		# Parameters
		self.declare_parameter('device', '')
		self.declare_parameter('max_faces', 3)
		self.declare_parameter('greeting_distance', 0.5)  # meters
		self.declare_parameter('cluster_tolerance', 0.5)  # meters
		
		# Variables
		self.device = self.get_parameter('device').value
		self.max_faces = self.get_parameter('max_faces').value
		self.greeting_distance = self.get_parameter('greeting_distance').value
		self.cluster_tolerance = self.get_parameter('cluster_tolerance').value
		self.detected_faces = []  # Stores face positions in map frame
		self.current_target = None
		self.current_pose = None  # Store current robot pose
		
		# TF2 setup
		self.tf_buffer = Buffer()
		self.tf_listener = TransformListener(self.tf_buffer, self)
		
		# Subscribers
		self.rgb_sub = self.create_subscription(
			Image, "/oakd/rgb/preview/image_raw", 
			self.rgb_callback, qos_profile_sensor_data)
		self.pc_sub = self.create_subscription(
			PointCloud2, "/oakd/rgb/preview/depth/points", 
			self.pc_callback, qos_profile_sensor_data)
		self.amcl_pose_sub = self.create_subscription(
			PoseWithCovarianceStamped, 'amcl_pose',
			self.amcl_pose_callback, amcl_pose_qos)
		
		# Publishers
		self.marker_pub = self.create_publisher(
			Marker, "/face_markers", QoSReliabilityPolicy.BEST_EFFORT)
		self.cmd_vel_pub = self.create_publisher(Twist, "/cmd_vel", 10)
		self.goal_pub = self.create_publisher(
			PoseStamped, "/move_base_simple/goal", 10)
		
		# Face detection model
		self.model = YOLO("yolov8n.pt")
		self.bridge = CvBridge()
		
		self.get_logger().info("Face detector initialized")

	def amcl_pose_callback(self, msg):
		"""Store the current robot pose from AMCL"""
		self.current_pose = msg.pose.pose

	def rgb_callback(self, msg):
		try:
			cv_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")
			results = self.model.predict(
				cv_image, imgsz=(256, 320), 
				show=False, verbose=False, 
				classes=[0], device=self.device)
			
			current_frame_faces = []
			
			for result in results:
				for box in result.boxes.xyxy:
					if box.nelement() == 0:
						continue
						
					# Calculate center of bounding box
					cx = int((box[0] + box[2]) / 2)
					cy = int((box[1] + box[3]) / 2)
					current_frame_faces.append((cx, cy))
					
					# Draw detection
					cv2.rectangle(cv_image, 
								(int(box[0]), int(box[1])), 
								(int(box[2]), int(box[3])), 
								(0, 0, 255), 2)
					cv2.circle(cv_image, (cx, cy), 5, (0, 0, 255), -1)
			
			self.faces_pixel_coords = current_frame_faces
			self.image_header = msg.header  # Store header for transform timing
			
			cv2.imshow("Face Detection", cv_image)
			cv2.waitKey(1)
			
		except CvBridgeError as e:
			self.get_logger().error(f"CV Bridge error: {e}")

	def pc_callback(self, msg):
		if not hasattr(self, 'faces_pixel_coords') or not self.faces_pixel_coords:
			return
			
		try:
			# Read point cloud data more efficiently
			pc_array = pc2.read_points_numpy(msg, field_names=("x", "y", "z"))
			pc_array = pc_array.reshape((msg.height, msg.width, 3))
			
			# Clean data
			valid_mask = ~(np.isnan(pc_array).any(axis=2) | np.isinf(pc_array).any(axis=2))
			
			for x, y in self.faces_pixel_coords:
				# Ensure coordinates are within bounds
				x = np.clip(int(x), 0, msg.width - 1)
				y = np.clip(int(y), 0, msg.height - 1)
				
				# Skip invalid points
				if not valid_mask[y, x]:
					continue
				
				position = pc_array[y, x, :]
				
				try:
					# Create timestamp once for all transforms
					transform_time = self.get_clock().now()
					
					# Create camera point
					camera_point = PointStamped()
					camera_point.header.frame_id = msg.header.frame_id
					camera_point.header.stamp = transform_time.to_msg()
					camera_point.point.x = float(position[0])
					camera_point.point.y = float(position[1])
					camera_point.point.z = float(position[2])
					
					# Chain transforms: camera -> base_link -> map
					try:
						# Get both transforms at the same time
						tf_cam_to_base = self.tf_buffer.lookup_transform(
							'base_link',
							camera_point.header.frame_id,
							transform_time,
							timeout=Duration(seconds=0.1))
						
						tf_base_to_map = self.tf_buffer.lookup_transform(
							'map',
							'base_link',
							transform_time,
							timeout=Duration(seconds=0.1))
						
						# Transform points
						base_point = tfg.do_transform_point(camera_point, tf_cam_to_base)
						map_point = tfg.do_transform_point(base_point, tf_base_to_map)
						face_pos = map_point.point
						
						# Check if this is a new face
						is_new = all(
							math.hypot(face_pos.x - existing.x, face_pos.y - existing.y) >= self.cluster_tolerance
							for existing in self.detected_faces
						)
						
						if is_new and len(self.detected_faces) < self.max_faces:
							self.detected_faces.append(face_pos)
							self.get_logger().info(
								f"New face at ({face_pos.x:.2f}, {face_pos.y:.2f}) - {len(self.detected_faces)}/{self.max_faces}",
								throttle_duration_sec=1.0)
							
							self.current_target = face_pos
							self.publish_markers()
							
							if self.current_pose:
								self.approach_face(face_pos)
					
					except TransformException as te:
						self.get_logger().warn(
							f"TF error: {str(te)}",
							throttle_duration_sec=1.0)
						continue
					
				except Exception as e:
					self.get_logger().error(
						f"Unexpected error processing point: {str(e)}",
						throttle_duration_sec=1.0)
					continue
			
			if len(self.detected_faces) >= self.max_faces:
				self.get_logger().info("All faces detected! Stopping navigation.")
				self.stop_robot()
				
		except Exception as e:
			self.get_logger().error(
				f"Point cloud processing failed: {str(e)}",
				throttle_duration_sec=1.0)
		finally:
			self.faces_pixel_coords = []

	def approach_face(self, face_pos):
		if not self.current_pose:
			self.get_logger().warn("Cannot approach - no current pose available")
			return
			
		try:
			goal = PoseStamped()
			goal.header.frame_id = "map"
			goal.header.stamp = self.get_clock().now().to_msg()
			
			# Calculate vector from robot to face
			dx = face_pos.x - self.current_pose.position.x
			dy = face_pos.y - self.current_pose.position.y
			distance = math.sqrt(dx**2 + dy**2)
			
			if distance > self.greeting_distance:
				# Calculate position 0.5m from face along line to robot
				ratio = (distance - self.greeting_distance) / distance
				goal.pose.position.x = face_pos.x - dx * ratio
				goal.pose.position.y = face_pos.y - dy * ratio
			else:
				# Already close enough
				goal.pose.position.x = self.current_pose.position.x
				goal.pose.position.y = self.current_pose.position.y
			
			# Face towards the detected face
			yaw = math.atan2(dy, dx)
			goal.pose.orientation.z = math.sin(yaw / 2)
			goal.pose.orientation.w = math.cos(yaw / 2)
			
			self.goal_pub.publish(goal)
			self.get_logger().info(
				f"Approaching face at ({face_pos.x:.2f}, {face_pos.y:.2f})")
			
		except Exception as e:
			self.get_logger().error(f"Approach error: {str(e)}")

	def stop_robot(self):
		cmd = Twist()
		self.cmd_vel_pub.publish(cmd)
		self.current_target = None

	def publish_markers(self):
		try:
			# First clear all existing markers
			clear_marker = Marker()
			clear_marker.header.frame_id = "map"
			clear_marker.header.stamp = self.get_clock().now().to_msg()
			clear_marker.action = Marker.DELETEALL
			self.marker_pub.publish(clear_marker)
			
			# Then publish each face marker
			for i, face in enumerate(self.detected_faces):
				marker = Marker()
				marker.header.frame_id = "map"
				marker.header.stamp = self.get_clock().now().to_msg()
				marker.id = i
				marker.type = Marker.SPHERE
				marker.action = Marker.ADD
				marker.pose.position = face
				
				# Size of the marker (0.2m diameter sphere)
				marker.scale.x = 0.2
				marker.scale.y = 0.2
				marker.scale.z = 0.2
				
				# Red color with full opacity
				marker.color.r = 1.0
				marker.color.g = 0.0
				marker.color.b = 0.0
				marker.color.a = 1.0
				
				# Marker will disappear after 5 seconds
				marker.lifetime = Duration(seconds=5.0).to_msg()
				
				self.marker_pub.publish(marker)
				
			self.get_logger().debug(f"Published markers for {len(self.detected_faces)} faces",
								throttle_duration_sec=1.0)
			
			for i, face in enumerate(self.detected_faces):
				self.get_logger().info(f"Marker {i} position: x={face.x:.2f}, y={face.y:.2f}, z={face.z:.2f}")
			
		except Exception as e:
			self.get_logger().error(f"Failed to publish markers: {str(e)}")

def main():
	rclpy.init()
	node = FaceDetector()
	try:
		rclpy.spin(node)
	except KeyboardInterrupt:
		pass
	finally:
		node.destroy_node()
		rclpy.shutdown()

if __name__ == '__main__':
	main()