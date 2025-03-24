#!/usr/bin/env python3

import rclpy
import time
import random

from dis_tutorial1.srv import SumService

mynode = None

def main(args=None):
    global mynode

    rclpy.init(args=args)

    mynode = rclpy.create_node("client_node") 
    client = mynode.create_client(SumService, 'SumService')

    request = SumService.Request()
    
    while rclpy.ok():
        request.numbers = [random.randint(1, 10) for _ in range(10)]
        
        mynode.get_logger().info("Sending a request!")
        future = client.call_async(request)
        
        rclpy.spin_until_future_complete(mynode, future)
        response = future.result()
        mynode.get_logger().info(f"Response: {response.response_text}, Sum: {response.sum}")
        
        time.sleep(1)

    mynode.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
