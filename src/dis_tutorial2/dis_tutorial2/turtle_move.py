import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from dis_tutorial2.srv import MoveTurtle  # Uporaba pravega service message-a
import time
import random

class TurtleMover(Node):
    def __init__(self):
        super().__init__('turtle_mover_service')
        self.publisher = self.create_publisher(Twist, '/turtle1/cmd_vel', 10)
        self.service = self.create_service(MoveTurtle, 'move_turtle', self.handle_move_turtle)
        self.get_logger().info("Turtle Mover Service is ready.")
    
    def handle_move_turtle(self, request, response):
        movement_type = request.movement_type  # "circle", "rectangle", "triangle", "random"
        duration = request.duration
        
        self.get_logger().info(f"Received request: {movement_type} for {duration} seconds")
        twist = Twist()
        start_time = time.time()
        
        if movement_type == "circle":
            twist.linear.x = 1.0
            twist.angular.z = 1.0
        elif movement_type == "rectangle":
            for _ in range(2):
                self.move_straight(2)
                self.turn(90)
                self.move_straight(1)
                self.turn(90)
        elif movement_type == "triangle":
            for _ in range(3):
                self.move_straight(2)
                self.turn(120)
        elif movement_type == "random":
            twist.linear.x = random.random()
            twist.angular.z = random.random()
        
        while rclpy.ok() and time.time() - start_time < duration:
            self.publisher.publish(twist)
            time.sleep(0.1)
        
        twist.linear.x = 0.0
        twist.angular.z = 0.0
        self.publisher.publish(twist)
        
        response.previous_movement = movement_type
        return response
    
    def move_straight(self, duration):
        twist = Twist()
        twist.linear.x = 1.0
        start_time = time.time()
        while time.time() - start_time < duration:
            self.publisher.publish(twist)
            time.sleep(0.1)
        twist.linear.x = 0.0
        self.publisher.publish(twist)
    
    def turn(self, angle):
        twist = Twist()
        twist.angular.z = 1.0 
        time_needed = angle / 90  # I think, not sure
        start_time = time.time()
        while time.time() - start_time < time_needed:
            self.publisher.publish(twist)
            time.sleep(0.1)
        twist.angular.z = 0.0
        self.publisher.publish(twist)

def main(args=None):
    rclpy.init(args=args)
    node = TurtleMover()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
