#!/usr/bin/env python3

import rclpy

from hwpub.msg import Hwmsg

mynode = None

def topic_callback(msg):
    global mynode
    mynode.get_logger().info('I heard: "%s"' % msg.s)

def main(args=None):
    global mynode
    rclpy.init(args=args)
    mynode = rclpy.create_node("py_simple_subscriber_node")
    
    subscription = mynode.create_subscription(Hwmsg, "/mytop", topic_callback, 10)

    while rclpy.ok():
        rclpy.spin(mynode)

    mynode.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()