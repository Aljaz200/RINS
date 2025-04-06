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
import webcolors
import struct
import pyttsx3

import ring_unique

BACKGROUND = [178,178,178]

qos_profile = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)

def css2_name_to_color(name: str):
    name = name.lower()
    if name in ['maroon', 'red', 'orange']:
        return 'red'
    elif name in ['yellow', 'olive']: 
        return 'yellow'
    elif name in ['green', 'lime']:
        return 'green'
    elif name in ['teal', 'blue', 'navy', 'aqua']:
        return 'blue'
    elif name in ['white', 'silver', 'gray']:
        return 'gray'
    else:
        return 'black'


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
        self.pointcloud_sub_sky = self.create_subscription(PointCloud2, "/oakd/rgb/preview/depth/points", self.pointcloud_callback, 1)
        
        self.marker_pub = self.create_publisher(Marker, "/cylinder_marker", qos_profile)
        self.qr_pub = self.create_publisher(Marker, "/qr_marker", qos_profile)
        
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        self.pc_data = None
        
        self.unique_cylinders = ring_unique.UniqueRings(safety_param=0.4)
        self.cylinders = []
        
        self.detected = []
        
        
        cv2.namedWindow("Image", cv2.WINDOW_NORMAL)
        # cv2.namedWindow("Segmented", cv2.WINDOW_NORMAL)

             
    
    def segment_color(self, image, lower_bound, upper_bound):
        # Convert the image to HSV color space
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

        # Create a binary mask where the colors within the range are white
        mask = cv2.inRange(hsv, lower_bound, upper_bound)
        
        # apply closing to the mask
        kernel = np.ones((9,9),np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=3)
        # mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel, iterations=3)
        
        # check connected components and make sure that the largest one is the one we want
        # it also has to be in both halves of the image
        _, labels, stats, centroids = cv2.connectedComponentsWithStats(mask)
        if len(stats) > 1:
            largest = np.argmax(stats[1:, cv2.CC_STAT_AREA]) + 1
            mask = np.zeros(mask.shape, dtype=np.uint8)
            mask[labels == largest] = 255
            
        if not np.any(mask[:mask.shape[0]//2, :]) or not np.any(mask[mask.shape[0]//2:, :]):
            mask = np.zeros(mask.shape, dtype=np.uint8)

        return mask
        
    def image_callback(self, data):
        self.cylinders = []

        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)
            
            
        color_ranges = {
            'red': ([0, 120, 70], [10, 255, 255]),
            'green': ([35, 100, 100], [85, 255, 255]),
            'yellow': ([25, 100, 100], [35, 255, 255]),
            'blue': ([100, 100, 50], [110, 200, 150]),
            'black': ([0, 0, 0], [180, 255, 30]),
        }
        
        combo_mask = np.zeros(cv_image.shape[:2], dtype=np.uint8)
        for color, (lower, upper) in color_ranges.items():
            mask = self.segment_color(cv_image.copy(), np.array(lower), np.array(upper))
            combo_mask = cv2.bitwise_or(combo_mask, mask)
            
        if not np.any(combo_mask[:combo_mask.shape[0]//2, :]):
            combo_mask = np.zeros(cv_image.shape[:2], dtype=np.uint8)
        
        # segment_img = self.segment_colors(cv_image.copy())
        cv_image2 = cv_image.copy()
        cv_image2 = cv2.bitwise_not(cv_image2)
        segment_img = cv2.bitwise_and(cv_image2, cv_image2, mask=combo_mask)
        if np.any(segment_img):
            
            # fit a rectangle to the segmented image
            gray = cv2.cvtColor(segment_img, cv2.COLOR_BGR2GRAY)
            _, thresh = cv2.threshold(gray, 1, 255, cv2.THRESH_BINARY)
            contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
            for contour in contours:
                x, y, w, h = cv2.boundingRect(contour)
                
                if h/w < 1.5 or h/w > 2.5 or h*w < 1500:
                    segment_img = np.zeros(segment_img.shape, dtype=np.uint8)
                    continue
                
                # extract the color from the center of the rectangle
                color = tuple([int(x) for x in (cv_image[y+h//2, x+w//2])])
                # print(self.get_color_name(color), color)
                cv2.rectangle(cv_image, (x, y), (x+w, y+h), color, 4)
                
                self.cylinders.append({'center': (y+h//2, x+w//2), 'color': color, 'bbox': (x, y, x+w, y+h)})
                self.do_cylinder_logic()
        
        # cv2.imshow("Segmented", segment_img)
        # cv2.waitKey(1)
        
        cv2.imshow("Image", cv_image)
        cv2.waitKey(1)
                            
                            
    def closest_color(self, requested_color):
        min_colors = {}
        for key, name in webcolors.CSS2_HEX_TO_NAMES.items():
            r_c, g_c, b_c = webcolors.hex_to_rgb(key)
            rd = (r_c - requested_color[0]) ** 2
            gd = (g_c - requested_color[1]) ** 2
            bd = (b_c - requested_color[2]) ** 2
            min_colors[(rd + gd + bd)] = name
        return min_colors[min(min_colors.keys())]

    def get_color_name(self, rgb_triplet):
        color_name = css2_name_to_color(self.closest_color(rgb_triplet))
        return color_name
                
    

    
    def pointcloud_callback(self, data):
        self.pc_data = data
        return
    
    
    
    def do_cylinder_logic(self):
        if self.pc_data == None:
            return
        
        height = self.pc_data.height
        width = self.pc_data.width
        a = pc2.read_points_numpy(self.pc_data, field_names= ("x", "y", "z"), skip_nans=True)
        a = a.reshape((height,width,3))
        point = None
        for i, candidate in enumerate(self.cylinders):
            y,x = candidate['center']
            
            point = a[y, x]
            
            ring = PointStamped()
            ring.header.frame_id = self.pc_data.header.frame_id
            ring.header.stamp = rclpy.time.Time().to_msg()
            ring.point.x = float(point[0])
            ring.point.y = float(point[1])
            ring.point.z = .0
            
            color = self.get_color_name(candidate['color'][::-1])
            if color in self.detected:
                continue
                
                
            
            try:
                
                # transformations
                transformed = self.tf_buffer.transform(ring, "map", timeout=rclpy.time.Duration(seconds=1.0))
                transformed_x = float(transformed.point.x)
                transformed_y = float(transformed.point.y)
                transformed_z = float(transformed.point.z)
                cyl = np.array([transformed_x, transformed_y, transformed_z])
                
                # current position of the robot
                robot_transformed = self.tf_buffer.lookup_transform("map", "base_link", rclpy.time.Time(), timeout=rclpy.time.Duration(seconds=1.0))
                robot_x = float(robot_transformed.transform.translation.x)
                robot_y = float(robot_transformed.transform.translation.y)
                robot_z = float(robot_transformed.transform.translation.z)
                rob = np.array([robot_x, robot_y, robot_z])
                
                # normal
                normal = (cyl - rob) / np.linalg.norm(cyl - rob)
                qr_point = cyl - 0.4 * normal
                angle = calc_greeting_angle(cyl, qr_point)
                quat_tf = quaternion_from_euler(0, 0, angle)
                quat_msg = Quaternion(x=quat_tf[0], y=quat_tf[1], z=quat_tf[2], w=quat_tf[3])
                     
                
                # store the spot
                pbool, park_id = self.unique_cylinders.store_ring(np.array([transformed_x, transformed_y, transformed_z]))
                if pbool:
                    print(f"{color} cylinder detected.")
                    self.detected.append(color)
                
                    # publish qr marker
                    qr_marker = Marker()
                    qr_marker.header.frame_id = "map"
                    qr_marker.header.stamp = rclpy.time.Time().to_msg()
                    qr_marker.ns = "qr"
                    qr_marker.id = park_id
                    qr_marker.type = Marker.ARROW
                    qr_marker.action = Marker.ADD
                    qr_marker.pose.position.x = qr_point[0]
                    qr_marker.pose.position.y = qr_point[1]
                    qr_marker.pose.position.z = qr_point[2]
                    qr_marker.pose.orientation = quat_msg
                    qr_marker.scale.x = 0.15
                    qr_marker.scale.y = 0.15
                    qr_marker.scale.z = 0.15
                    qr_marker.color.a = 1.0
                    qr_marker.color.r = float(candidate['color'][2]/255)
                    qr_marker.color.g = float(candidate['color'][1]/255)
                    qr_marker.color.b = float(candidate['color'][0]/255)
                
                    self.qr_pub.publish(qr_marker)
                
                # publush the marker
                ring_marker = Marker()
                ring_marker.header.frame_id = "map"
                ring_marker.header.stamp = rclpy.time.Time().to_msg()
                ring_marker.ns = "cylinder"
                ring_marker.id = park_id
                ring_marker.type = Marker.CYLINDER
                ring_marker.action = Marker.ADD
                ring_marker.pose.position.x = transformed_x
                ring_marker.pose.position.y = transformed_y
                ring_marker.pose.position.z = transformed_z
                ring_marker.pose.orientation.x = 0.0
                ring_marker.pose.orientation.y = 0.0
                ring_marker.pose.orientation.z = 0.0
                ring_marker.pose.orientation.w = 1.0
                ring_marker.scale.x = 0.25
                ring_marker.scale.y = 0.25
                ring_marker.scale.z = 0.25
                ring_marker.color.a = 1.0
                ring_marker.color.r = float(candidate['color'][2]/255)
                ring_marker.color.g = float(candidate['color'][1]/255)
                ring_marker.color.b = float(candidate['color'][0]/255)
                
                self.marker_pub.publish(ring_marker)
                
            except Exception as e:
                print(e)
    
    
def calc_greeting_point(cent, p1, p2):
    vec1 = p1 - cent
    vec2 = p2 - cent
    normal = np.cross(vec1, vec2) / np.linalg.norm(np.cross(vec1, vec2)) * 0.5
    return cent - normal

def calc_greeting_angle(cent, rpoint):
    vec = cent - rpoint
    angle = np.arctan2(vec[1], vec[0])
    return angle

def calc_greeting_normal(cent, p1, p2):
    vec1 = p1 - cent
    vec2 = p2 - cent
    normal = np.cross(vec1, vec2) / np.linalg.norm(np.cross(vec1, vec2)) * 0.5
    return normal

    
            
def speak(engine, text):
    return
    engine.setProperty('rate', 150)  # Speed of speech
    engine.setProperty('volume', 0.9)  # Volume level (0.0 to 1.0)
    engine.say(text)  # Add text to the speaking queue
    engine.runAndWait()  # Processes the speech request
        
        
        
def main():

    rclpy.init(args=None)
    rd_node = CylinderDetector()
    

    rclpy.spin(rd_node)

    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()