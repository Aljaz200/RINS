#!/usr/bin/env python3

import rclpy
import time
import random

from hwpub.srv import Customserv

mynode = None

def main(args=None):
    global mynode

    rclpy.init(args=args)

    mynode = rclpy.create_node("py_simple_client_node") 
    client = mynode.create_client(Customserv, 'customserv')

    request = Customserv.Request()
    
    while rclpy.ok():

        int_values = [random.randint(1, 100) for _ in range(10)]
        request.int_values = int_values
        request.s = "hi"
        
        mynode.get_logger().info("Sending a request!")
        while not client.wait_for_service(timeout_sec=1.0):
            mynode.get_logger().info('service not available, waiting again...')
        future = client.call_async(request)
        
        rclpy.spin_until_future_complete(mynode, future)
        response = future.result()
        mynode.get_logger().info('Result of customserv: = %d' %(response.a))
        
        time.sleep(1)

    mynode.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()