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
from std_msgs.msg import String, Empty

# from RealtimeTTS import TextToAudioStream, CoquiEngine
# import webcolors
import ring_unique

qos_profile = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)

SAFETY_PARAM = 1.3

class ParkingDetector(Node):
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
        self.ground_sub = self.create_subscription(Image, "/oakd/rgb/preview/image_raw", self.ground_callback, qos_profile_sensor_data)
        self.pointcloud_sub_ground = self.create_subscription(PointCloud2, "/oakd/rgb/preview/depth/points", self.pointcloud_callback, qos_profile_sensor_data)
        
        # subscribe to green parking spots
        self.green_sub = self.create_subscription(Marker, "/green", self.green_callback, qos_profile_sensor_data)
        
        # subscribe to parked
        self.parked_sub = self.create_subscription(Empty, "/parked", self.parked_callback, qos_profile_sensor_data)
        go_to_ring_topic = "/robot_commander/go_to_ring"
        self.create_subscription(Marker, go_to_ring_topic, self.go_to_ring_callback, 1)
        
        # publisher for arm
        self.arm_pub = self.create_publisher(String, "/arm_command", qos_profile)
        
        self.unique_parkings = ring_unique.UniqueRings(safety_param=0.55)
        
        self.parkings = []
        self.parking_boxes = []
        self.marker_id = 0
        self.look_for_parking = False
        self.pc_data = None
        self.parking_marker = None
        

        # Publiser for the visualization markers
        marker_topic = "/parking_marker"
        self.marker_pub = self.create_publisher(Marker, marker_topic, QoSReliabilityPolicy.BEST_EFFORT)

        # publisher for parking coordinates
        self.parking_pub = self.create_publisher(Pose, "/parking_coordinates", qos_profile)

        # Object we use for transforming between coordinate frames
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # cv2.namedWindow("Detected rings ground", cv2.WINDOW_NORMAL)
        # cv2.namedWindow("Image ground", cv2.WINDOW_NORMAL)
    
    def ground_callback(self, data):
        self.parkings = []
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
            # cv2.imshow("Image ground", cv_image)
            # cv2.waitKey(1)
        except CvBridgeError as e:
            print(e)

        # Tranform image to grayscale
        gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
        
        # extract the bottom half of the image
        gray = gray.copy()
        gray[:int(gray.shape[0]/2),:] = 0
        
        
        # Apply Gaussian Blur
        gray = cv2.GaussianBlur(gray,(3,3),0)

        thresh = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 15, 30)
        cv2.waitKey(1)

        # Extract contours
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

        # Example of how to draw the contours, only for visualization purposes
        cv2.drawContours(gray, contours, -1, (255, 0, 0), 3)
        # cv2.imshow("Detected contours ground", gray)
        cv2.waitKey(1)

        # Fit elipses to all extracted contours
        elps = []
        for cnt in contours:
            if cnt.shape[0] >= 20:
                ellipse = cv2.fitEllipse(cnt)
                elps.append(ellipse)


        # Find two elipses with same centers
        candidates = []
        for n in range(len(elps)):
            for m in range(n + 1, len(elps)):
                # e[0] is the center of the ellipse (x,y), e[1] are the lengths of major and minor axis (major, minor), e[2] is the rotation in degrees
                
                e1 = elps[n]
                e2 = elps[m]
                dist = np.sqrt(((e1[0][0] - e2[0][0]) ** 2 + (e1[0][1] - e2[0][1]) ** 2))
                angle_diff = np.abs(e1[2] - e2[2])

                # The centers of the two elipses should be within 5 pixels of each other (is there a better treshold?)
                if dist >= 5:
                    continue

                # The rotation of the elipses should be whitin 4 degrees of eachother
                if angle_diff>4:
                    continue

                e1_minor_axis = e1[1][0]
                e1_major_axis = e1[1][1]

                e2_minor_axis = e2[1][0]
                e2_major_axis = e2[1][1]

                if e1_major_axis>=e2_major_axis and e1_minor_axis>=e2_minor_axis: # the larger ellipse should have both axis larger
                    le = e1 # e1 is larger ellipse
                    se = e2 # e2 is smaller ellipse
                elif e2_major_axis>=e1_major_axis and e2_minor_axis>=e1_minor_axis:
                    le = e2 # e2 is larger ellipse
                    se = e1 # e1 is smaller ellipse
                else:
                    continue # if one ellipse does not contain the other, it is not a ring
                
                # The widths of the ring along the major and minor axis should be roughly the same
                border_major = (le[1][1]-se[1][1])/2
                border_minor = (le[1][0]-se[1][0])/2
                border_diff = np.abs(border_major - border_minor)

                if border_diff>6:
                    continue
                    
                candidates.append((e1,e2))

        # Plot the rings on the image
        for c in candidates:
           
            # the centers of the ellipses
            e1 = c[0]
            e2 = c[1]
            
            # Calculate the center of the ring
            center_x2, center_y2 = int(e2[0][0]), int(e2[0][1])
            
            # Draw the ellipses
            color = (0, 255, 0)
            cv2.ellipse(cv_image, e1, color, 2)
            cv2.ellipse(cv_image, e2, color, 2)

            self.parkings.append((center_x2, center_y2))
            self.do_parking_logic()
            
            # if len(candidates)>0:
            #         cv2.imshow("Detected rings ground",cv_image)
            #         cv2.waitKey(1)
            
            
    def pointcloud_callback(self, data):
        self.pc_data = data
                
                
    def green_callback(self, data):
        return
        try:
            # get the position of the green parking spot
            x = data.pose.position.x
            y = data.pose.position.y
            z = data.pose.position.z
            
            self.look_for_parking = True
            
        except Exception as e:
            print(e)
            
    def parked_callback(self, data):
        return
        try:
           self.arm_pub.publish(String(data="ring"))
        except Exception as e:
            print(e)
            
    def go_to_ring_callback(self, msg: Marker):
        self.get_logger().info(f"GOING TOWARDS THE RING AT {msg}")
        self.parking_marker = msg
        self.look_for_parking = True
    
    def is_close(self, x, y) -> bool:
        poz = np.array([x, y])
        target = np.array([self.parking_marker.pose.position.x, self.parking_marker.pose.position.y])

        return np.linalg.norm(poz - target) < SAFETY_PARAM
    
    def do_parking_logic(self):
        if self.pc_data is None:
            return
        height = self.pc_data.height
        width = self.pc_data.width
        a = pc2.read_points_numpy(self.pc_data, field_names= ("x", "y", "z"), skip_nans=True)
        a = a.reshape((height,width,3))
        point = None
        for i, (x,y) in enumerate(self.parkings):
            
            point = a[y, x, :]
                    
            ring = PointStamped()
            ring.header.frame_id = self.pc_data.header.frame_id
            ring.header.stamp = rclpy.time.Time().to_msg()
            ring.point.x = float(point[0])
            ring.point.y = float(point[1])
            ring.point.z = float(point[2])
            
            try:
                # transformations
                transformed = self.tf_buffer.transform(ring, "map", timeout=rclpy.time.Duration(seconds=1.0))
                transformed_x = transformed.point.x
                transformed_y = transformed.point.y
                transformed_z = transformed.point.z
                
                # store the spot
                pbool, park_id = self.unique_parkings.store_ring(np.array([transformed_x, transformed_y, transformed_z]))
                if pbool:
                    print(f'New parking spot detected at: {transformed_x, transformed_y, transformed_z}')
                
                # publush the marker
                ring_marker = Marker()
                ring_marker.header.frame_id = "map"
                ring_marker.header.stamp = rclpy.time.Time().to_msg()
                ring_marker.ns = "parking"
                ring_marker.id = park_id
                ring_marker.type = Marker.CUBE
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
                ring_marker.color.r = 1.0
                ring_marker.color.g = 1.0
                ring_marker.color.b = 0.1
                
                if self.look_for_parking:
                    ring_marker.color.r = 0.0
                    ring_marker.color.g = 1.0
                    ring_marker.color.b = 0.0
                    
                    # publish the parking coordinates
                    # poz = np.array([transformed_x, transformed_y])
                    if self.is_close(transformed_x, transformed_y):
                        self.look_for_parking = False
                        parking_coordinates = Pose()
                        parking_coordinates.position.x = transformed_x
                        parking_coordinates.position.y = transformed_y
                        parking_coordinates.position.z = transformed_z
                        print(f'Searched parking detected, coordinates: {transformed_x, transformed_y, transformed_z}')
                        # publish the parking coordinates
                        self.parking_pub.publish(parking_coordinates)
                    else:
                        print("detected parking, however, the parking is not close to the goal")
                    
                    # ready the camera for parking
                    #self.arm_pub.publish(String(data="look_for_parking"))
                    
                    
                self.marker_pub.publish(ring_marker)
                
            except Exception as e:
                print(e)

def main():

    rclpy.init(args=None)
    rd_node = ParkingDetector()

    rclpy.spin(rd_node)

    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()