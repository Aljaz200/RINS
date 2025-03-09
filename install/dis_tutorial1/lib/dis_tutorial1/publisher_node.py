#!/usr/bin/env python3

#print('I am alive!')
import rclpy
import time

from dis_tutorial1.msg import CustomMessage2

def main(args=None):
    rclpy.init(args=args)
    node = rclpy.create_node("publisher_node")
    
    publisher = node.create_publisher(CustomMessage, "custom_topic", 10)
    
    num = 0
    
    message = CustomMessage()
    message.text = "Hello from publisher"
    message.number = num
    message.flag = True

    while rclpy.ok():
        publisher.publish(message)
        num += 1
        message.number = num

        node.get_logger().info("Publisher: I performed one iteration!")
        time.sleep(1)

    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
