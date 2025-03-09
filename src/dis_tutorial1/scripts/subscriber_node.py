#!/usr/bin/env python3

import rclpy

from dis_tutorial1.msg import CustomMessage2

mynode = None

def topic_callback(msg):
    global mynode
    mynode.get_logger().info(f"Received: {msg.text}, {msg.number}, {msg.flag}")

def main(args=None):
    global mynode
    rclpy.init(args=args)
    mynode = rclpy.create_node("subscriber_node")
    
    subscription = mynode.create_subscription(CustomMessage, "custom_topic", topic_callback, 10)

    while rclpy.ok():
        rclpy.spin_once(mynode)

    mynode.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
