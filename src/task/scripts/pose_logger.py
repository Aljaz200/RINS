#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseWithCovarianceStamped
import json
import time
from atexit import register
from rclpy.qos import QoSDurabilityPolicy, QoSHistoryPolicy
from rclpy.qos import QoSProfile, QoSReliabilityPolicy

amcl_pose_qos = QoSProfile(
    durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
    reliability=QoSReliabilityPolicy.RELIABLE,
    history=QoSHistoryPolicy.KEEP_LAST,
    depth=1)

class PoseLogger(Node):
    def __init__(self):
        super().__init__('pose_logger')

        self.latest_pose = None
        self.logged_poses = []
        self.timee = 10.0

        self.localization_pose_sub = self.create_subscription(
            PoseWithCovarianceStamped,
            'amcl_pose',
            self.pose_callback,
            amcl_pose_qos)
        
        # Create timer to log pose every 10 seconds
        self.create_timer(self.timee, self.timer_callback)

        self.get_logger().info("🚀 Pose logger started. Saving every 10 seconds.")

    def pose_callback(self, msg):
        self.latest_pose = msg
        self.get_logger().info("📡 Pose callback received.")

    def timer_callback(self):
        if self.latest_pose is None:
            self.get_logger().warn("⚠️ No pose received yet.")
            return

        current_time = time.time()
        pose = self.latest_pose.pose.pose
        position = {
            'x': pose.position.x,
            'y': pose.position.y,
            'z': pose.position.z
        }
        orientation = {
            'x': pose.orientation.x,
            'y': pose.orientation.y,
            'z': pose.orientation.z,
            'w': pose.orientation.w
        }

        self.logged_poses.append({
            'timestamp': current_time,
            'position': position,
            'orientation': orientation
        })

        self.get_logger().info(
            f"📍 Saved pose at x={position['x']:.2f}, y={position['y']:.2f}"
        )

    def save_to_file(self):
        map_path = "/home/aljaz/Desktop/colcon_ws/src/task/maps/logged_poses.json"
        with open(map_path, 'w') as f:
            print("STARTING")
            json.dump(self.logged_poses, f, indent=4)
        self.get_logger().info("✅ Saved poses to logged_poses.json")


def main(args=None):
    print("A")
    rclpy.init(args=args)
    print("B")
    node = PoseLogger()
    print("C")

    register(node.save_to_file)
    print("D")

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("Shutting down...")
    finally:
        print("F")
        node.save_to_file()
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
