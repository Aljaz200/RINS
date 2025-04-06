#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data, QoSReliabilityPolicy

from sensor_msgs.msg import Image, PointCloud2
from sensor_msgs_py import point_cloud2 as pc2

from geometry_msgs.msg import PointStamped, Vector3, Pose, Quaternion
from turtle_tf2_py.turtle_tf2_broadcaster import quaternion_from_euler

from visualization_msgs.msg import Marker

import tf2_geometry_msgs as tfg
from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener

from cv_bridge import CvBridge, CvBridgeError
import cv2
import numpy as np

from ultralytics import YOLO
import numpy as np

import ring_unique as ru
from face_saver import FaceSaver

class DetectFaces(Node):

    def __init__(self, logimages = False):
        super().__init__('detect_faces')

        self.declare_parameters(
            namespace='',
            parameters=[
                ('device', ''),
            ]
        )

        self.logimages = logimages
        if self.logimages:
            self.saver = FaceSaver("/home/tau/Pictures/faces")

        self.detection_color = (0, 0, 255)
        self.device = self.get_parameter('device').get_parameter_value().string_value

        self.bridge = CvBridge()
        self.scan = None

        self.rgb_image_sub = self.create_subscription(Image, "/oakd/rgb/preview/image_raw", self.rgb_callback, qos_profile_sensor_data)
        self.pointcloud_sub = self.create_subscription(PointCloud2, "/oakd/rgb/preview/depth/points", self.pointcloud_callback, qos_profile_sensor_data)

        self.people_pub = self.create_publisher(Marker, "/people_marker", QoSReliabilityPolicy.BEST_EFFORT)
        self.painting_pub = self.create_publisher(Marker, "/painting_marker", QoSReliabilityPolicy.BEST_EFFORT)
        self.greet_ppl_pub = self.create_publisher(Marker, "/greet_ppl_marker", QoSReliabilityPolicy.BEST_EFFORT)
        self.greet_paint_pub = self.create_publisher(Marker, "/greet_paint_marker", QoSReliabilityPolicy.BEST_EFFORT)
        self.validator = YOLO("/home/tau/colcon_ws/yolov8n.pt")
        
        self.pc_data = None
        self.faces = []
        self.idx_save = 0
        self.ppl = ru.UniqueRings(safety_param=0.7)
        self.paints = ru.UniqueRings(safety_param=0.7)

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        cv2.namedWindow("Image", cv2.WINDOW_NORMAL)
        # cv2.namedWindow("Detected", cv2.WINDOW_NORMAL)


    def map_class_type(self, clss):
        if clss in [0,1,4,5,7,8,9,10,11,14]:
            return 0
        else:
            return 1

    def rgb_callback(self, data):
        self.faces = []

        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")

            # Run prediction using only the validator model
            results = self.validator.predict(cv_image, imgsz=(256, 320), show=False, verbose=False, device=self.device)

            for det in results:
                for box in det.boxes:
                    confidence = float(box.conf[0])
                    if confidence < 0.6:
                        continue

                    cls = int(box.cls[0])
                    clss = self.map_class_type(cls)

                    bbox = box.xyxy[0]
                    x1, y1, x2, y2 = map(int, bbox.tolist())
                    cx = int((x1 + x2) / 2)
                    cy = int((y1 + y2) / 2)

                    img_detected = cv_image.copy()
                    img_cut = cv_image[y1:y2, x1:x2].copy()

                    cv_image = cv2.rectangle(cv_image, (x1, y1), (x2, y2), self.detection_color, 3)
                    cv_image = cv2.circle(cv_image, (cx, cy), 5, self.detection_color, -1)

                    self.faces.append({'center': (cx, cy), 'img': img_detected, 'img_cut': img_cut, 'bbox': bbox, 'class': clss})
                    self.do_faces_logic()

            cv2.imshow("Image", cv_image)
            key = cv2.waitKey(1)
            if key == 27:
                print("Exiting")
                exit()

        except CvBridgeError as e:
            print(e)


    def pointcloud_callback(self, data):
        self.pc_data = data

    def do_faces_logic(self):
        if self.pc_data is None:
            return
        
        height = self.pc_data.height
        width = self.pc_data.width
        a = pc2.read_points_numpy(self.pc_data, field_names=("x", "y", "z"), skip_nans=True)
        a = a.reshape((height, width, 3))
        point = None

        for i, cand in enumerate(self.faces):
            (x, y) = cand['center']
            img_detected = cand['img']
            bbox = cand['bbox']
            img_cut = cand['img_cut']
            x1, y1, x2, y2 = cand['bbox']
            clss = cand['class']
            
            # marker color + logic
            color = (1.0, 0.0, 0.0)
            pub = None
            greet_pub = None
            storage = None
            mona = False
            if clss == 0: # painting
                color = (1.0, 1.0, 0.0)
                pub = self.painting_pub
                greet_pub = self.greet_paint_pub
                storage = self.paints
                mona = True
            else: # person
                color = (1.0, 0.0, 1.0)
                pub = self.people_pub
                greet_pub = self.greet_ppl_pub
                storage = self.ppl
                mona = False
            
            x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
            x1 = x1 + (x2 - x1) // 4
            y1 = y1 + (y2 - y1) // 4
            
            point = a[y, x, :]
            left_border_center = a[y, x1, :]
            bot_border_center = a[y1, x, :]

            center = PointStamped()
            center.header.frame_id = self.pc_data.header.frame_id
            center.header.stamp = rclpy.time.Time().to_msg()
            center.point.x = float(point[0])
            center.point.y = float(point[1])
            center.point.z = float(point[2])

            left = PointStamped()
            left.header.frame_id = self.pc_data.header.frame_id
            left.header.stamp = rclpy.time.Time().to_msg()
            left.point.x = float(left_border_center[0])
            left.point.y = float(left_border_center[1])
            left.point.z = float(left_border_center[2])

            top = PointStamped()
            top.header.frame_id = self.pc_data.header.frame_id
            top.header.stamp = rclpy.time.Time().to_msg()
            top.point.x = float(bot_border_center[0])
            top.point.y = float(bot_border_center[1])
            top.point.z = float(bot_border_center[2])

            try:
                transformed = self.tf_buffer.transform(center, "map", timeout=rclpy.time.Duration(seconds=1.0))
                transformed_x = float(transformed.point.x)
                transformed_y = float(transformed.point.y)
                transformed_z = float(transformed.point.z)

                tleft = self.tf_buffer.transform(left, "map", timeout=rclpy.time.Duration(seconds=1.0))
                tleft_x = float(tleft.point.x)
                tleft_y = float(tleft.point.y)
                tleft_z = float(tleft.point.z)

                ttop = self.tf_buffer.transform(top, "map", timeout=rclpy.time.Duration(seconds=1.0))
                ttop_x = float(ttop.point.x)
                ttop_y = float(ttop.point.y)
                ttop_z = float(ttop.point.z)

                tcenter = np.array([transformed_x, transformed_y, transformed_z])
                tleft = np.array([tleft_x, tleft_y, tleft_z])
                ttop = np.array([ttop_x, ttop_y, ttop_z])
                

                nparr = np.array([transformed_x, transformed_y])
                pbool, park_id = storage.store_ring(nparr)
                if pbool:
                    print(f'New face detected at: {transformed_x, transformed_y, transformed_z}')
                    greet_point = calc_greeting_point(tcenter, tleft, ttop)

                    angle = calc_greeting_angle(tcenter, greet_point)
                    quat_tf = quaternion_from_euler(0, 0, angle)
                    quat_msg = Quaternion(x=quat_tf[0], y=quat_tf[1], z=quat_tf[2], w=quat_tf[3])
                    
                    greet_marker = Marker()
                    greet_marker.header.frame_id = "map"
                    greet_marker.header.stamp = rclpy.time.Time().to_msg()
                    greet_marker.ns = "greet"
                    greet_marker.id = park_id
                    greet_marker.type = Marker.ARROW
                    greet_marker.action = Marker.ADD
                    greet_marker.pose.position.x = greet_point[0]
                    greet_marker.pose.position.y = greet_point[1]
                    greet_marker.pose.position.z = greet_point[2]
                    greet_marker.pose.orientation = quat_msg
                    greet_marker.scale.x = 0.15
                    greet_marker.scale.y = 0.15
                    greet_marker.scale.z = 0.15
                    greet_marker.color.a = 1.0
                    greet_marker.color.r = color[0]
                    greet_marker.color.g = color[1]
                    greet_marker.color.b = color[2]

                    if np.isfinite(nparr).all():
                        # save the detected face for debugging purposes
                        bbox 
                        x, y = int(bbox[0]), int(bbox[1])
                        w, h = int(bbox[2]) - int(bbox[0]), int(bbox[3]) - int(bbox[1])
                        prefix = ""
                        if mona:
                            prefix = "mona"
                        if self.logimages:
                            self.saver.save(img_detected, (x, y, w, h), prefix=prefix, id=greet_marker.id)
                        greet_pub.publish(greet_marker)
                    else:
                        print(f"completely ignoring the deformed coordinates {nparr}")

                center_marker = Marker()
                center_marker.header.frame_id = "map"
                center_marker.header.stamp = rclpy.time.Time().to_msg()
                center_marker.ns = "ppl"
                center_marker.id = park_id
                center_marker.type = Marker.CUBE
                center_marker.action = Marker.ADD
                center_marker.pose.position.x = transformed_x
                center_marker.pose.position.y = transformed_y
                center_marker.pose.position.z = transformed_z
                center_marker.pose.orientation.x = 0.0
                center_marker.pose.orientation.y = 0.0
                center_marker.pose.orientation.z = 0.0
                center_marker.pose.orientation.w = 1.0
                center_marker.scale.x = 0.25
                center_marker.scale.y = 0.25
                center_marker.scale.z = 0.25
                center_marker.color.a = 1.0
                center_marker.color.r = color[0]
                center_marker.color.g = color[1]
                center_marker.color.b = color[2]

                pub.publish(center_marker)

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

    

def main():
    print('Face detection node starting.')

    rclpy.init(args=None)
    node = DetectFaces()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()