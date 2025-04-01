#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
import json
import os
import time
from geometry_msgs.msg import Quaternion, PoseStamped, PoseWithCovarianceStamped
from rclpy.qos import QoSDurabilityPolicy, QoSHistoryPolicy
from rclpy.qos import QoSProfile, QoSReliabilityPolicy


amcl_pose_qos = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)

class FacePositionRecorder(Node):
    def __init__(self):
        super().__init__('face_position_recorder')

        self.face_positions = []
        self.output_file = os.path.expanduser('src/dis_tutorial3/scripts/face_positions.json')
        self.orientation_w = 0.0
        self.orientation_z = 0.0
        self.pose_x = 0.0
        self.pose_y = 0.0
        self.pose_z = 0.0

        # Subscribe to face markers
        self.subscription = self.create_subscription(
            Marker,
            '/people_marker',
            self.marker_callback,
            10)

        self.localization_pose_sub = self.create_subscription(PoseWithCovarianceStamped,
                                                              'amcl_pose',
                                                              self._amclPoseCallback,
                                                              amcl_pose_qos)



        self.get_logger().info("Face position recorder ready. Start moving the robot to detect faces.")

    def _amclPoseCallback(self, msg):
        #print(msg.pose.pose.position)
        #print(msg.pose.pose.orientation)
        self.orientation_w = msg.pose.pose.orientation.w
        self.orientation_z = msg.pose.pose.orientation.z
        self.pose_x = msg.pose.pose.position.x
        self.pose_y = msg.pose.pose.position.y
        self.pose_z = msg.pose.pose.position.z
        return


    def marker_callback(self, marker):
        #print (marker)
        new_position = {
            'x': float(self.pose_x),
            'y': float(self.pose_y),
            'z': float(self.pose_z),
            'z1': float(self.orientation_z),
            'w': float(self.orientation_w)
        }
        #print("nova")

        if not self.is_duplicate_position(new_position):
            self.face_positions.append(new_position)
            self.save_positions()
            self.get_logger().info(f"New face position saved: {new_position}")

    def is_duplicate_position(self, new_pos, threshold=0.5):
        for existing in self.face_positions:
            distance = ((new_pos['x'] - existing['x'])**2 +
                       (new_pos['y'] - existing['y'])**2 +
                       (new_pos['z'] - existing['z'])**2)**0.5
            if distance < threshold:
                return True
        return False

    def save_positions(self):
        with open(self.output_file, 'w') as f:
            json.dump(self.face_positions, f, indent=2)

def main(args=None):
    rclpy.init(args=args)
    recorder = FacePositionRecorder()

    try:
        rclpy.spin(recorder)
    except KeyboardInterrupt:
        recorder.get_logger().info(f"Shutting down. Saved {len(recorder.face_positions)} face positions.")
    finally:
        recorder.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
