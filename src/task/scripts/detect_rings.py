#!/usr/bin/python3

import rclpy
from rclpy.node import Node
import cv2
import numpy as np
import rclpy.time
import tf2_ros
import traceback

from std_msgs.msg import String
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
from RealtimeTTS import TextToAudioStream, CoquiEngine
import webcolors
import pyttsx3

import ring_unique

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

BACKGROUND = [178,178,178]

qos_profile = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)

def speak(engine, text):
    engine.setProperty('rate', 150)  # Speed of speech
    engine.setProperty('volume', 0.9)  # Volume level (0.0 to 1.0)
    engine.say(text)  # Add text to the speaking queue
    engine.runAndWait()  # Processes the speech request

class SingletonCoquiEngine:
    _instance = None

    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = CoquiEngine()
        return cls._instance

class RingDetector(Node):
    def __init__(self):
        super().__init__('transform_point')
        
        # self.voiceEngine = SingletonCoquiEngine.get_instance()
        # self.stream = TextToAudioStream(self.voiceEngine)

        # Basic ROS stuff
        timer_frequency = 2
        timer_period = 1/timer_frequency

        # An object we use for converting images between ROS format and OpenCV format
        self.bridge = CvBridge()

        # Marker array object used for visualizations
        self.marker_array = MarkerArray()
        self.marker_num = 1
        
        # store depth image
        self.depth_image = None
        self.pc_data = None

        # Subscribe to the image and/or depth topic
        self.sky_sub = self.create_subscription(Image, "/top_camera/rgb/preview/image_raw", self.sky_callback, 1)
        self.depth_sub = self.create_subscription(Image, "/top_camera/rgb/preview/depth", self.depth_callback, 1)
        self.pointcloud_sub_sky = self.create_subscription(PointCloud2, "/top_camera/rgb/preview/depth/points", self.pointcloud_callback, 1)
        self.ring_color_sub = self.create_subscription(String, "/searched_ring", self.set_ring_colors, 1)
        self.searched_colors = set()
        
        self.unique_rings = ring_unique.UniqueRings(safety_param=1.2)
        self.rings = []
        
        self.detected = []
        
        # marker publisher
        marker_topic = "/ring_marker"
        self.marker_pub = self.create_publisher(Marker, marker_topic, QoSReliabilityPolicy.BEST_EFFORT)
        
        # green ring detected publisher
        self.target_ring_pub = self.create_publisher(Marker, "/green", QoSReliabilityPolicy.BEST_EFFORT)
        
        # create arm_mover publisher
        arm_command_topic = "/arm_command"
        self.arm_command_pub = self.create_publisher(String, arm_command_topic, qos_profile)
    
        
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        
        self.engine = pyttsx3.init("dummy")  # Initialize the TTS engine


        # cv2.namedWindow("Depth window", cv2.WINDOW_NORMAL)   
        # cv2.namedWindow("Detected rings top", cv2.WINDOW_NORMAL)
        cv2.namedWindow("Image top", cv2.WINDOW_NORMAL)
        # cv2.namedWindow("Binary Image", cv2.WINDOW_NORMAL)
             
        
        
    def sky_callback(self, data):

        self.rings = []
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)
        cv2.imshow("Image top", cv_image)
        cv2.waitKey(1)

        blue = cv_image[:,:,0]
        green = cv_image[:,:,1]
        red = cv_image[:,:,2]

        # Tranform image to grayscale
        gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
        
        # extract the top half of the image
        # gray = gray[0:int(gray.shape[0]/2),:]
        
        # Threshold the image
        thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)[1]
        
        # open + close
        kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3))
        thresh = cv2.morphologyEx(thresh, cv2.MORPH_CLOSE, kernel, iterations=1)
        thresh1 = cv2.morphologyEx(thresh.copy(), cv2.MORPH_OPEN, kernel, iterations=1)
        kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))
        thresh2 = cv2.morphologyEx(thresh.copy(), cv2.MORPH_OPEN, kernel, iterations=2)
        
        # cv2.imshow("Binary Image", thresh)
        # cv2.waitKey(1)

        # Extract contours
        contours1, hierarchy = cv2.findContours(thresh1, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
        contours2, hierarchy = cv2.findContours(thresh2, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

        # Example of how to draw the contours, only for visualization purposes
        # cv2.drawContours(gray, contours1, -1, (255, 0, 0), 3)
        # cv2.imshow("Detected contours top", gray)
        # cv2.waitKey(1)

        # Fit elipses to all extracted contours
        elps = []
        for cnt in contours1:
            #     print cnt
            #     print cnt.shape
            if cnt.shape[0] >= 10:
                ellipse = cv2.fitEllipse(cnt)
                elps.append(ellipse)

        elps2 = []
        for cnt in contours2:
            if cnt.shape[0] >= 10:
                ellipse = cv2.fitEllipse(cnt)
                elps2.append(ellipse)


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
                if dist >= 7:
                    continue

                # The rotation of the elipses should be whitin 4 degrees of eachother
                if angle_diff>6:
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

                if border_diff>5:
                    continue
                    
                candidates.append((e1,e2))
        # if not candidates:
        #     for n in range(len(elps2)):
        #         for m in range(n + 1, len(elps2)):
        #             # e[0] is the center of the ellipse (x,y), e[1] are the lengths of major and minor axis (major, minor), e[2] is the rotation in degrees
# 
        #             e1 = elps2[n]
        #             e2 = elps2[m]
        #             dist = np.sqrt(((e1[0][0] - e2[0][0]) ** 2 + (e1[0][1] - e2[0][1]) ** 2))
        #             angle_diff = np.abs(e1[2] - e2[2])
# 
        #             # The centers of the two elipses should be within 5 pixels of each other (is there a better treshold?)
        #             if dist >= 7:
        #                 continue
# 
        #             # The rotation of the elipses should be whitin 4 degrees of eachother
        #             if angle_diff>6:
        #                 continue
# 
        #             e1_minor_axis = e1[1][0]
        #             e1_major_axis = e1[1][1]
# 
        #             e2_minor_axis = e2[1][0]
        #             e2_major_axis = e2[1][1]
# 
        #             if e1_major_axis>=e2_major_axis and e1_minor_axis>=e2_minor_axis: # the larger ellipse should have both axis larger
        #                 le = e1 # e1 is larger ellipse
        #                 se = e2 # e2 is smaller ellipse
        #             elif e2_major_axis>=e1_major_axis and e2_minor_axis>=e1_minor_axis:
        #                 le = e2 # e2 is larger ellipse
        #                 se = e1 # e1 is smaller ellipse
        #             else:
        #                 continue # if one ellipse does not contain the other, it is not a ring
        #             
        #             # The widths of the ring along the major and minor axis should be roughly the same
        #             border_major = (le[1][1]-se[1][1])/2
        #             border_minor = (le[1][0]-se[1][0])/2
        #             border_diff = np.abs(border_major - border_minor)
# 
        #             if border_diff>5:
        #                 continue
# 
        #             candidates.append((e1,e2))


        # Plot the rings on the image
        for c in candidates:
            if self.depth_image is None:
                return

            # the centers of the ellipses
            e1 = c[0]
            e2 = c[1]
            
            # Calculate the center of the ring
            center_x1, center_y1 = int(e1[0][0]), int(e1[0][1])
            center_x2, center_y2 = int(e2[0][0]), int(e2[0][1])
            
            # Check if the center coordinates are within the bounds of the depth image
            if (0 <= center_x1 < self.depth_image.shape[1] and 0 <= center_y1 < self.depth_image.shape[0]
                and 0 <= center_x2 < self.depth_image.shape[1] and 0 <= center_y2 < self.depth_image.shape[0]):
                if (self.depth_image[center_y2, center_x2] == 0 or self.depth_image[center_y1, center_x1] == 0):
                    
                    # get the color of the ring
                    mask_e1 = np.zeros_like(cv_image, dtype=np.uint8)
                    cv2.ellipse(mask_e1, e1, (255, 255, 255), -1)
                    
                    mask_e2 = np.zeros_like(cv_image, dtype=np.uint8)
                    cv2.ellipse(mask_e2, e2, (255, 255, 255), -1)
                    

                    # Combine the two masks to get the ring area (assuming e2 is inside e1)
                    mask_ring = cv2.subtract(mask_e2, mask_e1)
                    # check if the mask even has a white pixel
                    if np.any(mask_ring):
                    
                        #remove all that are black
                        slika = cv_image.copy()
                        # get only the ring part of the slika
                        slika = cv2.bitwise_and(slika, mask_ring)
                        slika = slika.reshape(-1, 3).tolist()
                        slika = [x for x in slika if (x != [0, 0, 0] and x != BACKGROUND)]
                        
                        # find the most common color in the ring
                        color_dict = {}
                        for color in slika:
                            color = tuple(color)
                            if color in color_dict:
                                color_dict[color] += 1
                            else:
                                color_dict[color] = 1
                        most_common_color = max(color_dict, key=color_dict.get)
                        
                        mean_color_ring = most_common_color # np.mean(slika, axis=0)
                    


                        # drawing the ellipses on the image
                        color = (mean_color_ring[0], mean_color_ring[1], mean_color_ring[2])
                        color = tuple([int(c) for c in color])
                        cv2.ellipse(cv_image, e1, color, 2)
                        cv2.ellipse(cv_image, e2, color, 2)

                        # Get a bounding box, around the first ellipse ('average' of both elipsis)
                        x_min = int(min(e1[0][0]-e1[1][0]/2, e2[0][0]-e2[1][0]/2))
                        x_max = int(max(e1[0][0]+e1[1][0]/2, e2[0][0]+e2[1][0]/2))
                        y_min = int(min(e1[0][1]-e1[1][1]/2, e2[0][1]-e2[1][1]/2))
                        y_max = int(max(e1[0][1]+e1[1][1]/2, e2[0][1]+e2[1][1]/2))
                        cv2.rectangle(cv_image, (x_min, y_min), (x_max, y_max), color, 2)
                        
                        # get a point with depth != 0 in the bbox
                        # ppoint = None
                        # for j in range(y_min, y_max):
                        #     for i in range(x_min, x_max):
                        #         if self.depth_image[j, i] != 0:
                        #             ppoint = (j,i)
                        #             break
                        #     if ppoint is not None:
                        #         break
                        
                        self.rings.append({'centre': (center_x2, center_y2), 'bbox': [x_min, x_max, y_min, y_max], 'color': color})
                        self.do_ring_logic()
                        
                        # if len(candidates)>0:
                        #     cv2.imshow("Detected rings top",cv_image)
                        #     cv2.waitKey(1)
                            
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
                
    

    def depth_callback(self,data):

        try:
            depth_image = self.bridge.imgmsg_to_cv2(data, "32FC1")
        except CvBridgeError as e:
            print(e)

        depth_image[depth_image==np.inf] = 0
        
        # Do the necessairy conversion so we can visuzalize it in OpenCV
        image_1 = depth_image / 65536.0 * 255
        image_1 = image_1/np.max(image_1)*255

        # image_viz = np.array(image_1, dtype= np.uint8)

        # Store the depth image
        self.depth_image = depth_image
        
        # cv2.imshow("Depth window", image_viz)
        # cv2.waitKey(1)
        
    def pointcloud_callback(self, data):
        self.pc_data = data

    def is_searched_ring(self, color: str) -> bool:
        for c in self.searched_colors:
            if c in color:
                return True
        return False

    def set_ring_colors(self, msg: String):
        self.get_logger().info(f"processing '{msg.data}', color set is {self.unique_rings.get_stored_colorstrings()}")
        for color in msg.data.split(";"):
            self.searched_colors.add(color)
            ring = self.unique_rings.get_ring_by_color(color)
            if ring is not None:
                self.get_logger().info(f"found the {color} ring!")
                marker = ring.marker()
                self.target_ring_pub.publish(marker)
        # log searched colors for debugging purposes
        self.get_logger().info(f"looking for ring colors: {self.searched_colors}")
        
    def do_ring_logic(self):
        
        height =self.pc_data.height
        width = self.pc_data.width
        a = pc2.read_points_numpy(self.pc_data, field_names= ("x", "y", "z"), skip_nans=True)
        a = a.reshape((height,width,3))
        
        point = None
        for i, candidate in enumerate(self.rings):
    
            x_min, x_max, y_min, y_max = candidate['bbox']
            
            
            accumulator = []
            for y in range(y_min, y_max):
                for x in range(x_min, x_max):
                    if not np.any(np.isnan(a[y, x, :])) and not np.any(np.isinf(a[y, x, :])):
                        accumulator.append(a[y, x, :])
            accumulator.sort(key=lambda x: np.linalg.norm(x))

            if not accumulator:
                return
            accumulator = np.array(accumulator)
            
            point = accumulator[accumulator.shape[0]//2]
            
                    
            ring = PointStamped()
            ring.header.frame_id = self.pc_data.header.frame_id
            ring.header.stamp = rclpy.time.Time().to_msg()
            ring.point.x = float(point[0])
            ring.point.y = float(point[1])
            ring.point.z = float(point[2])
            
            color = self.get_color_name(candidate['color'][::-1])
            if color in self.detected:
                continue
            
            try:
                # transformations
                transformed = self.tf_buffer.transform(ring, "map", timeout=rclpy.time.Duration(seconds=1.0))
                transformed_x = transformed.point.x
                transformed_y = transformed.point.y
                transformed_z = transformed.point.z
                
                # store the ring
                color_name = self.get_color_name(candidate['color'][::-1])
                rbool, ring_id, ring = self.unique_rings.store_ring(np.array([transformed_x, transformed_y, transformed_z]), color=candidate['color'], colorstring=color_name, gib_ring=True)
                
                if rbool:
                    #get color name from rgb
                    # print(f"RGB {color_name}")
                    self.detected.append(color_name)
                    speak(self.engine, f"found {color_name} ring.")
                    print(f"found ring with color {color_name}")
                    
                    # match searched ring in the string
                    if self.is_searched_ring(color_name):
                        print(f"detected the searched ring {color_name}")
                        # publish the marker
                        self.target_ring_pub.publish(ring.marker())

                    # self.stream.feed(f"Ring detected with color {color_name}")
                    # self.stream.play()
                
                # publish the marker
                ring_marker = Marker()
                ring_marker.header.frame_id = "map"
                ring_marker.header.stamp = rclpy.time.Time().to_msg()
                ring_marker.ns = "ring"
                ring_marker.id = ring_id
                ring_marker.type = Marker.SPHERE
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
                ring_marker.color.r = candidate['color'][2]/255.0
                ring_marker.color.g = candidate['color'][1]/255.0
                ring_marker.color.b = candidate['color'][0]/255.0
                self.marker_pub.publish(ring_marker)
                
            except Exception as e:
                print(e)
                    
        
def main():

    rclpy.init(args=None)
    rd_node = RingDetector()
    
    # publish ring command
    rd_node.arm_command_pub.publish(String(data="ring"))

    rclpy.spin(rd_node)

    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()