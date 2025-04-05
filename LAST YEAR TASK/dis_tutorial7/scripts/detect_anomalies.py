#!/usr/bin/python3

import rclpy
from rclpy.node import Node
import cv2
import numpy as np
import rclpy.time
import tf2_ros
import traceback
from scipy.optimize import least_squares
from collections import defaultdict

from std_msgs.msg import String, Empty
from sensor_msgs.msg import Image, PointCloud2
from geometry_msgs.msg import PointStamped, Vector3, Pose, Quaternion
from turtle_tf2_py.turtle_tf2_broadcaster import quaternion_from_euler

from cv_bridge import CvBridge, CvBridgeError
from visualization_msgs.msg import Marker, MarkerArray
from std_msgs.msg import ColorRGBA
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
# from RealtimeTTS import TextToAudioStream, CoquiEngine, SystemEngine


import padim_model

import ring_unique

BACKGROUND = [178,178,178]

qos_profile = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)


class CylinderDetector(Node):
    def __init__(self):
        super().__init__('transform_point')
        
        #self.voiceEngine = SystemEngine()
        #self.stream = TextToAudioStream(self.voiceEngine)
        self.engine = None# pyttsx3.init()  # Initialize the TTS engine


        # Basic ROS stuff
        timer_frequency = 2
        timer_period = 1/timer_frequency

        # An object we use for converting images between ROS format and OpenCV format
        self.bridge = CvBridge()

        # Subscribe to the image and/or depth topic
        self.sky_sub = self.create_subscription(Image, "/oakd/rgb/preview/image_raw", self.image_callback, 1)
        
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        
        self.unique_cylinders = ring_unique.UniqueRings(safety_param=0.4)
        self.cylinders = []
        
        self.detect_sub = self.create_subscription(Empty, "/detect_anomalies", self.detect_callback, qos_profile)
        self.cutout = None
        self.save_id = 0
        
        self.detector = padim_model.PADIMDetector()
        print('here')
        self.detector.setup_model('squished.pkl')
        
        cv2.namedWindow("Image", cv2.WINDOW_NORMAL)
        cv2.namedWindow("Detected", cv2.WINDOW_NORMAL)

             
    
    
    def image_callback(self, data):
        self.cylinders = []

        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)
            
            
        
        # Convert the image to grayscale
        gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)

        # Apply GaussianBlur to reduce noise and improve edge detection
        blurred = cv2.GaussianBlur(gray, (5, 5), 0)

        # Apply Canny edge detection
        edges = cv2.Canny(blurred, 50, 150)

        # Find contours in the edged image
        contours, _ = cv2.findContours(edges, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

        # Iterate over contours to find the bounding box
        rects = []
        for contour in contours:
            # Get the bounding box for each contour
            x, y, w, h = cv2.boundingRect(contour)
            # You can add conditions to filter out small or irrelevant contours
            if w > 75 and h > 75 and w < 300 and h < 300 and h/w > 1.2 and h/w < 1.75:  # Example condition to filter out small boxes
                center = (x + w//2, y + h//2)
                rects.append({'center': center, 'bbox': (x,y,w,h)})
        
        
        # find the most central rectangle
        if len(rects) > 0:
            center = cv_image.shape[1]//2, cv_image.shape[0]//2
            closest = min(rects, key=lambda x: abs(x['center'][0] - center[0]) + abs(x['center'][1] - center[1]))
            bbox = closest['bbox']
            
            # cut out the bounding box
            cutout = cv_image[bbox[1]:bbox[1]+bbox[3], bbox[0]:bbox[0]+bbox[2]]
            # clip 3 pixels around the edge
            cutout = cutout[4:-4, 3:-3]
            self.cutout = cv2.cvtColor(cutout, cv2.COLOR_BGR2RGB)
            cv2.imshow("Detected", cutout)
            cv2.waitKey(1)
            
            cv2.rectangle(cv_image, (bbox[0], bbox[1]), (bbox[0]+bbox[2], bbox[1]+bbox[3]), (0, 255, 0), 2)

                   
        cv2.imshow("Image", cv_image)
        cv2.waitKey(1)
                            
    
    def detect_callback(self, data):
        if self.cutout is None:
            return
        img = self.cutout
        cv2.imwrite(f'/home/omicron/colcon_ws/trainset/img_{self.save_id}.png', img)
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        print('Started inference')
        self.detector.infer_single_image(img) 
        
        
def main():

    rclpy.init(args=None)
    rd_node = CylinderDetector()
    

    rclpy.spin(rd_node)

    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()