#!/usr/bin/env python3

#print('I am alive!')
import rclpy
import time
from geometry_msgs.msg import Twist
import random
import math

def main(args=None):
    rclpy.init(args=args)
    node = rclpy.create_node("py_move_turtle_triangle")
    
    publisher = node.create_publisher(Twist, "/turtle1/cmd_vel", 10)
    
    message = Twist()
    message_num = 0.0
    message.linear.x = 1.0/2
    message.linear.y = math.sqrt(3)/2
    g = 11
    first = True
    counter = 0
    while rclpy.ok():
        if(first):
            first = False
            time.sleep(1)
        else:
            if counter < 3:
                publisher.publish(message)

            if (g / 3) >= 1.0:
                message_num += 1.0

            node.get_logger().info(str((g / 3.0) - message_num))
        
            slp = 1
            if g / 3.0 - message_num == 0:
                #change direction
                if message.linear.y > 0.0:
                    message.linear.y *= -1
                elif message.linear.x > 0.0:
                    message.linear.x *= -2.0
                    message.linear.y = 0.0
                message_num = 0
                counter += 1
            elif g / 3.0 - message_num > 0.0 and g / 3.0 - message_num < 1.0:
                slp = g / 3 - message_num
                if (g / 3) >= 1.0:
                    message_num = (g / 3.0) -1
                else:
                    message_num = (g / 3.0)

            time.sleep(slp)

    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()