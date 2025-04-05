#!/usr/bin/python3

import rclpy
import time
from rclpy.node import Node
from sensor_msgs.msg import Image, PointCloud2
from rclpy.qos import qos_profile_sensor_data, QoSReliabilityPolicy
from std_msgs.msg import String, Empty
from geometry_msgs.msg import Twist
import cv2
from cv_bridge import CvBridge, CvBridgeError

from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import tf2_geometry_msgs as tfg

from sensor_msgs_py import point_cloud2 as pc2

from rclpy.duration import Duration
from geometry_msgs.msg import PointStamped, PoseWithCovarianceStamped

from rclpy.qos import QoSDurabilityPolicy, QoSHistoryPolicy
from rclpy.qos import QoSProfile, QoSReliabilityPolicy
from rclpy.qos import qos_profile_sensor_data

from tf_transformations import euler_from_quaternion

import traceback
import numpy as np

ANGLE_TOLERANCE = 5
DIST_TOLERANCE = 0.1


amcl_pose_qos = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)

# node responsible for parking
# when robot should park, control will be given to this node
class Parker(Node):
    def __init__(self):
        super().__init__("parker")

        self.declare_parameters(
            namespace='',
            parameters=[
                ('device', ''),
        ])

        # point transformation things
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        topdown_cam_topic = "/top_camera/rgb/preview/image_raw"
        topdown_depth_topic = "/top_camera/rgb/preview/depth/points"
        parking_finished_topic = "/parker_node/parking_finished"
        parking_found_topic = "/parker_node/parkplatz_found"
        parking_start_topic = "/parker_node/enable_parking"
        velocity_topic = "/cmd_vel"
        self.bridge = CvBridge()
        self.parking_finished_pub = self.create_publisher(Empty, parking_finished_topic, 1)
        self.parking_found_pub = self.create_publisher(Empty, parking_found_topic, 1)
        self.velocity_pub = self.create_publisher(Twist, velocity_topic, 1)
        self.vdata = None
        self.parking_finished = False
        self.parking_enabled = False
        self.center_point = None
        self.target_point = None
        self.robot_pos = None
        self.robot_ori = None
        self.rgb_image_sub = self.create_subscription(Image, topdown_cam_topic, self.rgb_callback, qos_profile_sensor_data)
        self.pointcloud_sub = self.create_subscription(PointCloud2, topdown_depth_topic, self.pointcloud_callback, qos_profile_sensor_data)
        self.park_start_sub = self.create_subscription(Empty, parking_start_topic, self.park_enabled_callback, 10)
        self.localization_pose_sub = self.create_subscription(PoseWithCovarianceStamped, 'amcl_pose', self._amcl_pose_callback, amcl_pose_qos)
    
    def transform_point(self, frame_id, point: np.ndarray) -> np.ndarray | None:
        point_in_robot_frame = PointStamped()
        point_in_robot_frame.header.frame_id = frame_id
        point_in_robot_frame.header.stamp = self.get_clock().now().to_msg()
        point_in_robot_frame.point.x = float(point[0])
        point_in_robot_frame.point.y = float(point[1])
        point_in_robot_frame.point.z = float(point[2])
        time_now = rclpy.time.Time()
        timeout = Duration(seconds=0.1)
        try:
            trans = self.tf_buffer.lookup_transform("map", frame_id, time_now, timeout)
            resultPoint = tfg.do_transform_point(point_in_robot_frame, trans)
            return np.array([resultPoint.point.x, resultPoint.point.y])
        except TransformException as te:
            self.get_logger().info(f"Cound not get the transform: {te}")
            return None

    def send_velocity(self, yaw: float, dist: float):
        #self.get_logger().info(f"YD {yaw}, {dist}")
        msg = Twist()
        if self.parking_finished or (dist <= DIST_TOLERANCE):
            #dist <= DIST_TOLERANCE:
            # parking finished!
            self.parking_finished = True
            self.parking_enabled = False
            self.parking_finished_pub.publish(Empty())
            self.velocity_pub.publish(msg)
            self.vdata = None
            self.center_point = None
            self.target_point = None
            self.get_logger().info("parking finished!")
            return
        
        if abs(yaw) > ANGLE_TOLERANCE:
            msg.angular.z = -0.5
            if yaw < 0:
                msg.angular.z = 0.5
        elif dist > DIST_TOLERANCE:
            msg.linear.x = 0.1
        #self.get_logger().info(f"{msg}")
        self.velocity_pub.publish(msg)

    def park_enabled_callback(self, _):
        self.get_logger().info("parking was enabled! now looking for parkplatzes!")
        self.parking_enabled = True
        self.parking_finished = False

    def pointcloud_callback(self, data: PointCloud2):
        if not self.center_point or self.target_point is not None or not self.parking_enabled:
            return
        height = data.height
        width = data.width
        # get 3-channel representation of the poitn cloud in numpy format
        dbuff = pc2.read_points_numpy(data, field_names= ("x", "y", "z"))
        dbuff = dbuff.reshape((height,width,3))
        x, y = self.center_point
        # get point in robot coordinate system
        d = dbuff[int(-y), int(x)]
        # convert point to map coordinate system and enable parking!
        point = self.transform_point(data.header.frame_id, d)
        self.target_point = point
        #self.update_move_to_parking()
        pass

    def update_move_to_parking(self):
        if self.target_point is None:
            return
        euler = euler_from_quaternion([self.robot_ori.x, self.robot_ori.y, self.robot_ori.z, self.robot_ori.w])
        yaw = np.rad2deg(euler[2])
        # calculate target yaw and difference
        diff = self.target_point - self.robot_pos
        target_yaw = np.rad2deg(np.arctan2(diff[1], diff[0]))
        ydiff1 = yaw - target_yaw
        ydiff2 = ydiff1
        if ydiff1 < 0:
            ydiff2 += 360
        else:
            ydiff2 -= 360
        if abs(ydiff2) < abs(ydiff1):
            ydiff1 = ydiff2
        #self.get_logger().info(f"YAWS {yaw} {target_yaw}")
        #self.get_logger().info(f"PTS {self.target_point} {self.robot_pos}")
        self.send_velocity(ydiff1, np.linalg.norm(diff))


    def _amcl_pose_callback(self, msg: PoseWithCovarianceStamped):
        self.robot_pos = np.array([msg.pose.pose.position.x, msg.pose.pose.position.y])
        self.robot_ori = msg.pose.pose.orientation
        if self.target_point is None or not self.parking_enabled:
            return
        #self.update_move_to_parking()

    def rgb_callback(self, im: Image):
        if not self.parking_enabled:
            return
        try:
            cv_image = self.bridge.imgmsg_to_cv2(im, "bgr8")

            h, w = cv_image.shape[:2]
            #target = np.array([w / 2, -h])
            # convert to grayscale
            cv_gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
            # apply median filter
            cv_med = cv2.medianBlur(cv_gray, 5)
            # hough transform
            circles = cv2.HoughCircles(cv_med, cv2.HOUGH_GRADIENT, 1, 20, param2=80)
            # draw circle detected
            centr = None
            if circles is not None:
                circles = np.uint16(np.around(circles))
                for i in circles[0,:]:
                    cv2.circle(cv_image,(i[0],i[1]),i[2],(0,255,0),2)
                    cv2.circle(cv_image,(i[0],i[1]),2,(0,0,255),3)
                    centr = [float(i[0]), float(i[1])]
                    #self.get_logger().info(f"CENTR {centr}")
                    centr[1] = -centr[1]


            self.update_move_to_parking()
            if centr is not None and self.center_point is None:
                self.center_point = centr
                self.parking_found_pub.publish(Empty())
                #dist = np.linalg.norm(target - centr)
                #yaw = np.arctan2(*(centr - target))
                #if self.vdata is None:
                #    # if parking data was not found before, publish that a parkplace was found
                #    # this will be then read by robot commander who will stop it's movement so that robot can park in peace
                #    self.parking_found_pub.publish(Empty())
                #self.vdata = (yaw, dist)
                # and here we have the calculated position
                #self.get_logger().info(f"|{target}, {centr}| calculated angle {np.rad2deg(yaw)} and dist {dist}")
            
            #if self.vdata is not None and not self.parking_finished:
            #    yaw, dist = self.vdata
            #    self.send_velocity(float(yaw), float(dist))

            cv2.imshow("topdown image", cv_image)
            key = cv2.waitKey(1)
            if key==27:
                print("exiting")
                exit()
        except Exception as e:
            print(traceback.format_exc())
        
    
def main():
    print("parker node starting ...")
    rclpy.init(args=None)
    node = Parker()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()