#!/usr/bin/env python3

import rclpy
import time

from dis_tutorial1.srv import SumService

mynode = None

def SumService_callback(request, response):
    global mynode
    response.sum = sum(request.numbers)
    response.response_text = "Sum calculated successfully"
    mynode.get_logger().info(f"Received: {request.numbers}, Sum: {response.sum}")
    return response

def main(args=None):
    global mynode

    rclpy.init(args=args)

    mynode = rclpy.create_node("service_node") 
    server = mynode.create_service(SumService, 'SumService', SumService_callback)

    mynode.get_logger().info("Server is ready!")
    rclpy.spin(mynode)

    mynode.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
