#!/usr/bin/python3

import rclpy
from rclpy.node import Node
import cv2
import numpy as np
import tf2_ros
import ast
import math

from sensor_msgs.msg import Image
from geometry_msgs.msg import PointStamped, Vector3, Pose
from cv_bridge import CvBridge, CvBridgeError
from visualization_msgs.msg import Marker, MarkerArray
from std_msgs.msg import ColorRGBA
from rclpy.qos import QoSDurabilityPolicy, QoSHistoryPolicy
from rclpy.qos import QoSProfile, QoSReliabilityPolicy

qos_profile = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)

class RingDetector(Node):
    elps = []

    def is_similar_ellipse(ellipse1, ellipse2, tolerance=5.0):
        """
        Compare two ellipses (cv2.fitEllipse format) represented as NumPy arrays.
        Returns True if all corresponding values are within the given `tolerance`.
        """
        # Convert the ellipses into NumPy arrays if they are not alread

        # Convert the string into a tuple using ast.literal_eval (safer than eval)
        ellipse1 = ast.literal_eval(ellipse1)
        ellipse2 = ast.literal_eval(ellipse2)

        ellipse_str = f"{ellipse1[0][0]},{ellipse1[0][1]},{ellipse1[1][0]},{ellipse1[1][1]},{ellipse1[2]}"
        array1 = np.array([float(val) for val in ellipse_str.split(',')])

        ellipse_str = f"{ellipse2[0][0]},{ellipse2[0][1]},{ellipse2[1][0]},{ellipse2[1][1]},{ellipse2[2]}"
        array2 = np.array([float(val) for val in ellipse_str.split(',')])

        # Compare the two arrays using np.allclose with tolerance
        return np.allclose(array1, array2, atol=tolerance)

    def __init__(self):
        super().__init__('transform_point')

        # Basic ROS stuff
        timer_frequency = 2
        timer_period = 1/timer_frequency

        # An object we use for converting images between ROS format and OpenCV format
        self.bridge = CvBridge()

        # Marker array object used for visualizations
        self.marker_array = MarkerArray()
        self.marker_num = 1

        # Subscribe to the image and/or depth topic
        self.image_sub = self.create_subscription(Image, "/oakd/rgb/preview/image_raw", self.image_callback, 1)
        self.depth_sub = self.create_subscription(Image, "/oakd/rgb/preview/depth", self.depth_callback, 1)

        # Publiser for the visualization markers
        # self.marker_pub = self.create_publisher(Marker, "/ring", QoSReliabilityPolicy.BEST_EFFORT)

        # Object we use for transforming between coordinate frames
        # self.tf_buf = tf2_ros.Buffer()
        # self.tf_listener = tf2_ros.TransformListener(self.tf_buf)

        cv2.namedWindow("Binary Image", cv2.WINDOW_NORMAL)
        cv2.namedWindow("Detected contours", cv2.WINDOW_NORMAL)
        cv2.namedWindow("Detected rings", cv2.WINDOW_NORMAL)
        cv2.namedWindow("Depth window", cv2.WINDOW_NORMAL)        

    def image_callback(self, data):

        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)

        blue = cv_image[:,:,0]
        green = cv_image[:,:,1]
        red = cv_image[:,:,2]

        # Tranform image to grayscale
        gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
        # gray = red

        # Apply Gaussian Blur
        # gray = cv2.GaussianBlur(gray,(3,3),0)

        # Do histogram equalization
        # gray = cv2.equalizeHist(gray)

        # Binarize the image, there are different ways to do it
        #ret, thresh = cv2.threshold(img, 50, 255, 0)
        #ret, thresh = cv2.threshold(img, 70, 255, cv2.THRESH_BINARY)
        thresh = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 15, 30)
        cv2.imshow("Binary Image", thresh)
        cv2.waitKey(1)

        # Extract contours
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

        # Example of how to draw the contours, only for visualization purposes
        cv2.drawContours(gray, contours, -1, (255, 0, 0), 3)
        cv2.imshow("Detected contours", gray)
        cv2.waitKey(1)

        local_elps = []


        # Fit elipses to all extracted contours
        for cnt in contours:
            #     print cnt
            #     print cnt.shape
            if cnt.shape[0] >= 8:
                ellipse = cv2.fitEllipse(cnt)
                local_elps.append(ellipse)


        # Find two elipses with same centers
        candidates = []
        for n in range(len(local_elps)):
                # e[0] is the center of the ellipse (x,y), e[1] are the lengths of major and minor axis (major, minor), e[2] is the rotation in degrees

                e1 = local_elps[n]

                for i in self.elps:
                    array1 = [e1[0][0], e1[0][1]]
                    array2 = [i[0][0], i[0][1]]
                    arr3 = [e1[1][0], e1[1][1], e1[2]]
                    arr4 = [i[1][0], i[1][1], i[2]]

                    if (np.allclose(array1, array2, atol=10.0) and (np.allclose(arr3, arr4, atol=10.0))):
                        candidates.append(e1)
                        print(e1)
                        print(i)


        for c in candidates:
            # print("motherfucker")

            e1 = c

            # drawing the ellipses on the image
            cv2.ellipse(cv_image, e1, (0, 255, 0), 2)

            # Get a bounding box, around the first ellipse ('average' of both elipsis)
            size = (e1[1][0]+e1[1][1])/2
            center = (e1[0][1], e1[0][0])

            x1 = int(center[0] - size / 2)
            x2 = int(center[0] + size / 2)
            x_min = x1 if x1>0 else 0
            x_max = x2 if x2<cv_image.shape[0] else cv_image.shape[0]

            y1 = int(center[1] - size / 2)
            y2 = int(center[1] + size / 2)
            y_min = y1 if y1 > 0 else 0
            y_max = y2 if y2 < cv_image.shape[1] else cv_image.shape[1]

        cv2.imshow("Detected rings",cv_image)
        cv2.waitKey(1)

    def depth_callback(self,data):

        self.elps = []

        try:
            depth_image = self.bridge.imgmsg_to_cv2(data, "32FC1")
        except CvBridgeError as e:
            print(e)

        depth_image[depth_image==np.inf] = 0
        
        # Do the necessairy conversion so we can visuzalize it in OpenCV
        image_1 = depth_image / 65536.0 * 255
        image_1 = image_1/np.max(image_1)*255

        image_viz = np.array(image_1, dtype= np.uint8)

        cv2.imshow("Depth window", image_viz)
        cv2.waitKey(1)

        # Fit elipses to all extracted contours

        black_mask = image_viz == 0

        # Create the output array: black where the mask is True, white otherwise
        output = np.where(black_mask, 0, 255).astype(np.uint8)

        thresh = cv2.adaptiveThreshold(output, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 15, 30)
        cv2.imshow("Binary Image depth", thresh)
        cv2.waitKey(1)

        # Extract contours
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

        # Example of how to draw the contours, only for visualization purposes

         # Fit elipses to all extracted contours
        for cnt in contours:
            #     print cnt
            #     print cnt.shape
            if cnt.shape[0] >= 5:
                ellipse = cv2.fitEllipse(cnt)

                center = tuple(map(int, ellipse[0]))
                print(center)
                center0 = center[0]
                center1 = center[1]

                if center0 == 0:
                    center0 += 1

                if center1 == 0:
                    center1 += 1

                if center0 == 320:
                    center0 -= 1

                if center1 == 240:
                    center1 -= 1

                if center0 <= 320 and center1 <= 240 and center1 >= 0 and center0 >= 0:
                    color_value = output[center1, center0]
                    print(color_value)
                else:
                    color_value = 0
                print("Barva",color_value)
                print("hund")
                cv2.imshow("Detected contours depth", output)
                cv2.waitKey(1)
                if ellipse not in self.elps and color_value == 0:
                    self.elps.append(ellipse)

def main():

    rclpy.init(args=None)
    rd_node = RingDetector()

    rclpy.spin(rd_node)

    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
