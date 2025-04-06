#!/usr/bin/python3

import rclpy
from rclpy.node import Node
import cv2
import numpy as np
import tf2_ros
import traceback

from sensor_msgs.msg import Image, PointCloud2
from geometry_msgs.msg import PointStamped, Vector3, Pose
from cv_bridge import CvBridge, CvBridgeError
from visualization_msgs.msg import Marker, MarkerArray
from std_msgs.msg import ColorRGBA, Empty, Bool
from rclpy.qos import QoSDurabilityPolicy, QoSHistoryPolicy
from rclpy.qos import QoSProfile, QoSReliabilityPolicy
from visualization_msgs.msg import Marker
from rclpy.qos import qos_profile_sensor_data, QoSReliabilityPolicy
from sensor_msgs_py import point_cloud2 as pc2
import tf2_geometry_msgs as tfg
from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
from rclpy.duration import Duration
from std_msgs.msg import String, Empty
import requests

# from RealtimeTTS import TextToAudioStream, CoquiEngine
# import webcolors
import ring_unique

qos_profile = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)

class QRDetector(Node):
    def __init__(self):
        super().__init__('detect_parkings')
        
        # Basic ROS stuff
        timer_frequency = 2
        timer_period = 1/timer_frequency

        # An object we use for converting images between ROS format and OpenCV format
        self.bridge = CvBridge()

        # Marker array object used for visualizations
        self.marker_array = MarkerArray()
        self.marker_num = 1
        
        # Subscribe to the image and/or depth topic
        self.image_sub = self.create_subscription(Image, "/top_camera/rgb/preview/image_raw", self.image_callback, 1)
        #self.pointcloud_sub = self.create_subscription(PointCloud2, "/top_camera/rgb/preview/depth/points", self.pointcloud_callback, 1)
        
        # commander
        continue_moving_topic = "/robot_commander/continue_moving"
        self.continue_pub = self.create_publisher(Empty, continue_moving_topic, qos_profile)
        qr_found_topic = "/qr_scanner/found"
        self.qr_found_pub = self.create_publisher(Bool, qr_found_topic, qos_profile)
        
        # publisher for arm
        self.arm_pub = self.create_publisher(String, "/arm_command", qos_profile)
        self.arm_finished_sub = self.create_subscription(Empty, "/arm_finished", self._arm_finished, 1)
        self.wait_for_arm_and_continue_moving = False
                
        self.qr_detector = cv2.QRCodeDetector()
        
        self.look_for_qr = False
        self.qr_reader_sub = self.create_subscription(Empty, "/look_for_qr", self.qr_reader_callback, 1)

        
        # Object we use for transforming between coordinate frames
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # cv2.namedWindow("Detected qr", cv2.WINDOW_NORMAL)
        # cv2.namedWindow("Image qr", cv2.WINDOW_NORMAL)
    
    def image_callback(self, data):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
            # cv2.imshow("Image qr", cv_image)
            # cv2.waitKey(1)
        except CvBridgeError as e:
            print(e)
            
        if not self.look_for_qr:
            return
        
        # Detect and decode the QR code
        data, bbox, _ = self.qr_detector.detectAndDecode(cv_image)

        # Check if a QR code has been detected
        if bbox is not None and data is not None and data != "":
            print(f"QR Code data: {data}")
            
            # check if data is a url
            if "http" in data:
                # download the image
                download_and_show_image(data)
            self.send_qr_code_found("http" in data)
            
            # Draw the bounding box around the QR code
            for i in range(len(bbox)):
                # Get the coordinates of the corners of the bounding box
                detected_img = cv_image.copy()
                
                # Get the center coordinates of the bounding box
                center_x = int((bbox[i][0][0] + bbox[i][2][0]) / 2)
                center_y = int((bbox[i][0][1] + bbox[i][2][1]) / 2)

                # Draw a circle at the center of the QR code
                cv2.circle(detected_img, (center_x, center_y), 5, (0, 255, 0), -1)
            
                # Display the image with the detected QR code
                # try:
                #     cv2.imshow("Detected qr", detected_img)
                #     cv2.waitKey(1)
                # except Exception as e:
                #     print(e)
            
            self.look_for_qr = False
            self.wait_for_arm_and_continue_moving = True
            ringmsg = String()
            ringmsg.data = "ring"
            self.arm_pub.publish(ringmsg)
            
    def qr_reader_callback(self, msg):
        self.look_for_qr = True 
    
    def send_qr_code_found(self, contains_link: bool):
        msg = Bool()
        msg.data = contains_link
        self.qr_found_pub.publish(msg)
    
    def _arm_finished(self, _):
        if self.wait_for_arm_and_continue_moving:
            self.wait_for_arm_and_continue_moving = False
            self.continue_pub.publish(Empty())
            

    
def download_and_show_image(image_url):
   
    try:
        # Download the image
        response = requests.get(image_url)
        response.raise_for_status()  # Check for HTTP request errors

        # Convert image data to numpy array
        image_array = np.frombuffer(response.content, np.uint8)

        # Decode the image
        image = cv2.imdecode(image_array, cv2.IMREAD_COLOR)

        # Display the image
        cv2.imshow('Downloaded Image', image)
        cv2.waitKey(1)  # Wait for a key press to close the window
    except requests.exceptions.RequestException as e:
        print(f'Failed to download image: {e}')
    
def main():

    rclpy.init(args=None)
    rd_node = QRDetector()
    
    rclpy.spin(rd_node)

    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()