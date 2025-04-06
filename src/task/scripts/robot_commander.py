#! /usr/bin/env python3
# Mofidied from Samsung Research America
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


from enum import Enum
import math
import time

import robot_mover
import autonomous_nav
import argparse

from std_msgs.msg import Empty, String, Bool

from action_msgs.msg import GoalStatus
from builtin_interfaces.msg import Duration
from geometry_msgs.msg import Quaternion, PoseStamped, PoseWithCovarianceStamped, Pose
from lifecycle_msgs.srv import GetState
from nav2_msgs.action import Spin, NavigateToPose
from turtle_tf2_py.turtle_tf2_broadcaster import quaternion_from_euler
from nav_msgs.msg import OccupancyGrid

from irobot_create_msgs.action import Dock, Undock
from irobot_create_msgs.msg import DockStatus

import rclpy
from rclpy.action import ActionClient
from rclpy.duration import Duration as rclpyDuration
from rclpy.node import Node
from rclpy.qos import QoSDurabilityPolicy, QoSHistoryPolicy
from rclpy.qos import QoSProfile, QoSReliabilityPolicy
from rclpy.qos import qos_profile_sensor_data

import tf_transformations

import numpy as np

from visualization_msgs.msg import Marker


# points
PTS = []


class TaskResult(Enum):
    UNKNOWN = 0
    SUCCEEDED = 1
    CANCELED = 2
    FAILED = 3

amcl_pose_qos = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)

qos_profile = QoSProfile(
          durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
          reliability=QoSReliabilityPolicy.RELIABLE,
          history=QoSHistoryPolicy.KEEP_LAST,
          depth=1)

class RobotCommander(Node):

    def __init__(self, node_name='robot_commander', namespace='', goals=[], move_only=False):
        super().__init__(node_name=node_name, namespace=namespace)
        
        self.pose_frame_id = 'map'
        
        # Flags and helper variables
        self.goal_handle = None
        self.result_future = None
        self.feedback = None
        self.status = None
        self.initial_pose_received = False
        self.is_docked = None
        self.mover = None
        self.is_face = False
        self.goals = goals
        self.goals_visited = []
        self.goal_coordinates = []
        self.current_pose = None
        self.goals_generated = False
        self.is_parking = False
        self.parking_node_disabled = False

        self.map_np = None
        self.map_data = {"map_load_time":None,
                         "resolution":None,
                         "width":None,
                         "height":None,
                         "origin":None} # origin will be in the format [x,y,theta]


        # ROS2 subscribers
        self.create_subscription(DockStatus,
                                 'dock_status',
                                 self._dockCallback,
                                 qos_profile_sensor_data)
        
        people_marker_topic = "/greet_ppl_marker"
        if not move_only:
            self.create_subscription(Marker, people_marker_topic, self._markerCallback, 10)
        
        mona_marker_topic = "/greet_paint_marker"
        if not move_only:
            self.create_subscription(Marker, mona_marker_topic, self._mona_marker_callback, 10)

        # anomaly detection
        begin_detecting_anomalies_topic = "/detect_anomalies"
        self.begin_detecting_anomalies_pub = self.create_publisher(Empty, begin_detecting_anomalies_topic, qos_profile)
        anomaly_detection_finished_topic = "/anomaly_detector/anomaly_detected"
        if not move_only:
            self.create_subscription(Bool, anomaly_detection_finished_topic, self.anomaly_detected_callback, 10)

        # arm shit
        self.arm_move_pub = self.create_publisher(String, "/arm_command", QoSReliabilityPolicy.BEST_EFFORT)
        if not move_only:
            self.arm_finish_sub = self.create_subscription(Empty, "/arm_finished", self._arm_task_callback, 10)

        # signaling ring color for finding
        self.ring_color_pub = self.create_publisher(String, "/searched_ring", QoSReliabilityPolicy.BEST_EFFORT)
        go_to_ring_topic = "/robot_commander/go_to_ring"
        self.ring_target_pub = self.create_publisher(Marker, go_to_ring_topic, QoSReliabilityPolicy.BEST_EFFORT)

        # cylinder stuff
        if not move_only:
            self.marker_pub = self.create_subscription(Marker, "/cylinder_marker", self._cyl_marker_callback, 10)

        # continue movement
        self.continue_moving_sub = self.create_subscription(Empty, "/robot_commander/continue_moving", self.continue_moving, 10)

        # qr code stuff
        look_qr_topic = "/look_for_qr"
        qr_found_topic = "/qr_scanner/found"
        self.look_qr_pub = self.create_publisher(Empty, look_qr_topic, QoSReliabilityPolicy.BEST_EFFORT)
        self.create_subscription(Bool, qr_found_topic, self.qr_code_found, 10)
        

        # parking related stuff
        self.arm_finished_callback = None
        self.park_search_enabled = False

        parking_found_topic = "/parker_node/parkplatz_found"
        parking_start_topic = "/parker_node/enable_parking"
        parking_detected_topic = "/parking_coordinates"
        parking_finished_topic = "/parker_node/parking_finished"
        green_ring_topic = "/green"

        self.park_enable_pub = self.create_publisher(Empty, parking_start_topic, QoSReliabilityPolicy.BEST_EFFORT)

        if not move_only:
            self.create_subscription(Empty, parking_found_topic, self._parking_found, 10)
            self.create_subscription(Marker, green_ring_topic, self._green_ring_detected, 10)
            self.create_subscription(Pose, parking_detected_topic, self._parking_place_detected, 10)
            self.create_subscription(Empty, parking_finished_topic, self._parking_finished, 10)

        map_topic = "/map"
        self.occupancy_grid_sub = self.create_subscription(OccupancyGrid, map_topic, self.map_callback, qos_profile)
        
        self.localization_pose_sub = self.create_subscription(PoseWithCovarianceStamped,
                                                              'amcl_pose',
                                                              self._amclPoseCallback,
                                                              amcl_pose_qos)
        
        # ROS2 publishers
        self.initial_pose_pub = self.create_publisher(PoseWithCovarianceStamped,
                                                      'initialpose',
                                                      10)
        
        # ROS2 Action clients
        self.nav_to_pose_client = ActionClient(self, NavigateToPose, 'navigate_to_pose')
        self.spin_client = ActionClient(self, Spin, 'spin')
        self.undock_action_client = ActionClient(self, Undock, 'undock')
        self.dock_action_client = ActionClient(self, Dock, 'dock')

        self.get_logger().info(f"Robot commander has been initialized!")
        
    def destroyNode(self):
        self.nav_to_pose_client.destroy()
        super().destroy_node()     

    def goToPose(self, pose: PoseStamped, behavior_tree='', callback = None):
        """Send a `NavToPose` action request."""
        self.debug("Waiting for 'NavigateToPose' action server")
        while not self.nav_to_pose_client.wait_for_server(timeout_sec=1.0):
            self.info("'NavigateToPose' action server not available, waiting...")

        goal_msg = NavigateToPose.Goal()
        goal_msg.pose = pose
        goal_msg.behavior_tree = behavior_tree

        self.info('Navigating to goal: ' + str(pose.pose.position.x) + ' ' +
                  str(pose.pose.position.y) + '...')
        send_goal_future = self.nav_to_pose_client.send_goal_async(goal_msg,
                                                                   self._feedbackCallback)

        if not callback is None:
            send_goal_future.add_done_callback(callback)
            return True
        rclpy.spin_until_future_complete(self, send_goal_future)
        self.goal_handle = send_goal_future.result()

        if not self.goal_handle.accepted:
            self.error('Goal to ' + str(pose.pose.position.x) + ' ' +
                       str(pose.pose.position.y) + ' was rejected!')
            return False

        self.result_future = self.goal_handle.get_result_async()
        return True

    def spin(self, spin_dist=1.57, time_allowance=10):
        self.debug("Waiting for 'Spin' action server")
        while not self.spin_client.wait_for_server(timeout_sec=1.0):
            self.info("'Spin' action server not available, waiting...")
        goal_msg = Spin.Goal()
        goal_msg.target_yaw = spin_dist
        goal_msg.time_allowance = Duration(sec=time_allowance)

        self.info(f'Spinning to angle {goal_msg.target_yaw}...')
        send_goal_future = self.spin_client.send_goal_async(goal_msg, self._feedbackCallback)
        rclpy.spin_until_future_complete(self, send_goal_future)
        self.goal_handle = send_goal_future.result()

        if not self.goal_handle.accepted:
            self.error('Spin request was rejected!')
            return False

        self.result_future = self.goal_handle.get_result_async()
        return True

    def spin_callback(self, spin_dist=1.57, time_allowance=10, callback=None):
        self.debug("Waiting for 'Spin' action server")
        while not self.spin_client.wait_for_server(timeout_sec=1.0):
            self.info("'Spin' action server not available, waiting...")
        goal_msg = Spin.Goal()
        goal_msg.target_yaw = spin_dist
        goal_msg.time_allowance = Duration(sec=time_allowance)

        self.info(f'Spinning to angle {goal_msg.target_yaw}...')
        send_goal_future = self.spin_client.send_goal_async(goal_msg, self._feedbackCallback)

        def future_result(fut):
            self.goal_handle = fut.result()
            if not self.goal_handle.accepted:
                self.error('Spin request was rejected!')
                return
            self.result_future = self.goal_handle.get_result_async()
            self.taskCompleteCallback(callback)

        send_goal_future.add_done_callback(future_result)
    
    def undock(self):
        """Perform Undock action."""
        self.info('Undocking...')
        self.undock_send_goal()

        while not self.isUndockComplete():
            time.sleep(0.1)

    def undock_send_goal(self):
        goal_msg = Undock.Goal()
        self.undock_action_client.wait_for_server()
        goal_future = self.undock_action_client.send_goal_async(goal_msg)

        rclpy.spin_until_future_complete(self, goal_future)

        self.undock_goal_handle = goal_future.result()

        if not self.undock_goal_handle.accepted:
            self.error('Undock goal rejected')
            return

        self.undock_result_future = self.undock_goal_handle.get_result_async()

    def isUndockComplete(self):
        """
        Get status of Undock action.

        :return: ``True`` if undocked, ``False`` otherwise.
        """
        if self.undock_result_future is None or not self.undock_result_future:
            return True

        rclpy.spin_until_future_complete(self, self.undock_result_future, timeout_sec=0.1)

        if self.undock_result_future.result():
            self.undock_status = self.undock_result_future.result().status
            if self.undock_status != GoalStatus.STATUS_SUCCEEDED:
                self.info(f'Goal with failed with status code: {self.status}')
                return True
        else:
            return False

        self.info('Undock succeeded')
        return True

    def cancelTask(self, callback=None):
        """Cancel pending task request of any type."""
        self.info('Canceling current task.')
        if self.result_future:
            future = self.goal_handle.cancel_goal_async()
            if not callback is None:
                future.add_done_callback(callback)
                return
            rclpy.spin_until_future_complete(self, future)
        if callback is not None:
            callback(None)
        return

    def isTaskComplete(self):
        """Check if the task request of any type is complete yet."""
        if not self.result_future:
            # task was cancelled or completed
            return True
        rclpy.spin_until_future_complete(self, self.result_future, timeout_sec=0.10)
        if self.result_future.result():
            self.status = self.result_future.result().status
            if self.status != GoalStatus.STATUS_SUCCEEDED:
                self.debug(f'Task with failed with status code: {self.status}')
                return True
        else:
            # Timed out, still processing, not complete yet
            return False

        self.debug('Task succeeded!')
        return True
    
    def taskCompleteCallback(self, callback):
        if not self.result_future:
            callback(self.result_future)
        else:
            self.result_future.add_done_callback(callback)

    def getFeedback(self):
        """Get the pending action feedback message."""
        return self.feedback

    def getResult(self):
        """Get the pending action result message."""
        if self.status == GoalStatus.STATUS_SUCCEEDED:
            return TaskResult.SUCCEEDED
        elif self.status == GoalStatus.STATUS_ABORTED:
            return TaskResult.FAILED
        elif self.status == GoalStatus.STATUS_CANCELED:
            return TaskResult.CANCELED
        else:
            return TaskResult.UNKNOWN

    def waitUntilNav2Active(self, navigator='bt_navigator', localizer='amcl'):
        """Block until the full navigation system is up and running."""
        self._waitForNodeToActivate(localizer)
        if not self.initial_pose_received:
            time.sleep(1)
        self._waitForNodeToActivate(navigator)
        self.info('Nav2 is ready for use!')
        return

    def _waitForNodeToActivate(self, node_name):
        # Waits for the node within the tester namespace to become active
        self.debug(f'Waiting for {node_name} to become active..')
        node_service = f'{node_name}/get_state'
        state_client = self.create_client(GetState, node_service)
        while not state_client.wait_for_service(timeout_sec=1.0):
            self.info(f'{node_service} service not available, waiting...')

        req = GetState.Request()
        state = 'unknown'
        while state != 'active':
            self.debug(f'Getting {node_name} state...')
            future = state_client.call_async(req)
            rclpy.spin_until_future_complete(self, future)
            if future.result() is not None:
                state = future.result().current_state.label
                self.debug(f'Result of get_state: {state}')
            time.sleep(2)
        return
    
    def YawToQuaternion(self, angle_z = 0.):
        quat_tf = quaternion_from_euler(0, 0, angle_z)

        # Convert a list to geometry_msgs.msg.Quaternion
        quat_msg = Quaternion(x=quat_tf[0], y=quat_tf[1], z=quat_tf[2], w=quat_tf[3])
        return quat_msg

    def _amclPoseCallback(self, msg):
        self.debug('Received amcl pose')
        self.initial_pose_received = True
        self.current_pose = msg.pose
        self.setVisitedGoals(0.25)
        #self.get_logger().info(f"goals {self.goals_visited}")
        #self.get_logger().info(f"{self.goals_generated}, {self.map_np is not None} and {self.mover}")
        #if not self.goals_generated and self.map_np is not None and self.mover is not None:
        #self.goals_generated = True
        #self.generate_and_set_goals()
        return
    
    def get_pose(self) -> Pose:
        return self.current_pose.pose

    def _feedbackCallback(self, msg):
        self.debug('Received action feedback message')
        self.feedback = msg.feedback
        return
    
    def _dockCallback(self, msg: DockStatus):
        self.is_docked = msg.is_docked

    def setInitialPose(self, pose):
        msg = PoseWithCovarianceStamped()
        msg.pose.pose = pose
        msg.header.frame_id = self.pose_frame_id
        msg.header.stamp = 0
        self.info('Publishing Initial Pose')
        self.initial_pose_pub.publish(msg)
        return

    def info(self, msg):
        self.get_logger().info(msg)
        return

    def warn(self, msg):
        self.get_logger().warn(msg)
        return

    def error(self, msg):
        self.get_logger().error(msg)
        return

    def debug(self, msg):
        self.get_logger().debug(msg)
        return
    
    def newPose(self, x, y, rot) -> PoseStamped:
        pose = PoseStamped()
        pose.header.frame_id = "map"
        pose.header.stamp = self.get_clock().now().to_msg()
        pose.pose.position.x = float(x)
        pose.pose.position.y = float(y)
        pose.pose.orientation = self.YawToQuaternion(float(rot))
        return pose
    
    def setMover(self, mover):
        self.mover = mover

    # people callback
    def _markerCallback(self, msg):
        if self.mover is None:
            return
        self.mover.newMarker(msg)
        #if self.is_face:
        #    return
        #self.is_face = True
        #self.info("test")
        #pose = PoseStamped()
        #pose.header.frame_id = "map"
        #pose.header.stamp = self.get_clock().now().to_msg()
        #pose.pose.position.x = msg.pose.position.x
        #pose.pose.position.y = msg.pose.position.y
        #pose.pose.orientation = self.YawToQuaternion(msg.pose.orientation.w)
        #self.cancelTask()
        #self.info("task cancelled.")
        #self.info(f"goToPose result: {self.goToPose(pose)}")
        #self.info("waiting for task to complete")
        #while not self.isTaskComplete():
        #    time.sleep(0.05)
        #self.info("task completed.")
        ##self.is_face = False

    def visitGoalCallback(self, goal, callback, rejected_callback = None):
        def cb(future):
            self.goal_handle = future.result()
            if not self.goal_handle.accepted:
                self.error('Goal to ' + str(goal.pose.position.x) + ' ' +
                           str(goal.pose.position.y) + ' was rejected!')
                if not rejected_callback is None:
                    rejected_callback()
                    return
            self.result_future = self.goal_handle.get_result_async()
            self.taskCompleteCallback(callback)
    
        self.goToPose(goal, callback=cb)

    def visitGoalID(self, goal_id, callback, rejected_callback = None):
        self.visitGoalCallback(self.goals[goal_id], callback, rejected_callback)
    
    def setGoals(self, goals):
        self.goals = goals
        self.goals_visited = np.array([False for g in self.goals])
        self.goal_coordinates = np.array([(g.pose.position.x, g.pose.position.y) for g in self.goals])
        self.get_logger().info(f"set goals! {self.goal_coordinates}")
    
    def getGoal(self, index):
        if index >= len(self.goals):
            return None
        for i, g in enumerate(self.goals):
            if not self.goals_visited[i]:
                if index == 0:
                    return g
                index -= 1
        return None

    def goalVisited(self, index):
        self.goals_visited[index] = True

    # pos is numpy array [x, y]!!
    def setVisitedGoals(self, tolerance = 0.0):
        if len(self.goals) == 0:
            return
        pos = np.array([self.current_pose.pose.position.x, self.current_pose.pose.position.y])
        arr = np.linalg.norm(self.goal_coordinates - pos, axis=1)
        self.goals_visited |= (arr < tolerance)

    def poseStampedPositionDifference(self, p1, p2):
        return np.array([p1.pose.position.x, p1.pose.position.y]) - np.array([p2.pose.position.x, p2.pose.position.y])

    def setGoalAngles(self):
        for i in range(len(self.goals) - 1):
            # get points and calculate yaw angle
            pt1 = self.goals[i]
            pt2 = self.goals[i+1]
            diff = self.poseStampedPositionDifference(pt2, pt1)
            yaw = np.arctan2(diff[1], diff[0])
            pt1.pose.orientation = self.YawToQuaternion(float(yaw))

    # visit all goals given in a list
    def visitGoals(self, goals):
        #while True:
        #    time.sleep(0.05)
        for goal in goals:
            self.info("processing next goal ...")
            while True:
                if not self.is_face:
                    self.goToPose(goal)
                while not self.isTaskComplete():
                    self.info("sleeping ...")
                    time.sleep(1.05)
                if not self.is_face:
                    break
                #else:
                #    return
                # prevent deadlock (doesn't work lmao)
                time.sleep(0.05)
    
    def process(self):
        rclpy.spin_once(self, timeout_sec=0.5)
    

    # map callback - called when a map is received
    def map_callback(self, msg):
        self.get_logger().info(f"Read a new Map (Occupancy grid) from the topic.")
        if self.map_np is not None:
            return
        # reshape the message vector back into a map
        self.map_np = np.asarray(msg.data, dtype=np.uint8).reshape(msg.info.height, msg.info.width)
        # fix the direction of Y (origin at top for OpenCV, origin at bottom for ROS2)
        self.map_np = np.flipud(self.map_np)
        # change the colors so they match with the .pgm image
        self.map_np = self.map_np.astype(np.uint8)
        self.map_np[self.map_np==0] = 255
        self.map_np[self.map_np==100] = 0
        # load the map parameters
        self.map_data["map_load_time"]=msg.info.map_load_time
        self.map_data["resolution"]=msg.info.resolution
        self.map_data["width"]=msg.info.width
        self.map_data["height"]=msg.info.height
        quat_list = [msg.info.origin.orientation.x,
                     msg.info.origin.orientation.y,
                     msg.info.origin.orientation.z,
                     msg.info.origin.orientation.w]
        self.map_data["origin"]=[msg.info.origin.position.x,
                                 msg.info.origin.position.y,
                                 tf_transformations.euler_from_quaternion(quat_list)[-1]]

    def pose_to_pose_stamped(self, pose: Pose) -> PoseStamped:
        p = PoseStamped()
        p.header.frame_id = "map"
        p.header.stamp = self.get_clock().now().to_msg()
        p.pose = pose
        return p

    def generate_and_set_goals(self):
        pts = self.generate_path()
        poses = []
        for p in pts:
            pose = PoseStamped()
            pose.header.frame_id = "map"
            pose.header.stamp = self.get_clock().now().to_msg()
            pose.pose.position.x = p[0]
            pose.pose.position.y = p[1]
            poses.append(pose)
        self.setGoals(poses)
        self.setGoalAngles()
        self.mover.set_n_goals(len(poses))
        self.mover.set_paused(False)

    def generate_path(self):
        pts = autonomous_nav.obtain_pixel_points_from_image() # self.map_np
        coor = [float(self.current_pose.pose.position.x), float(self.current_pose.pose.position.y)]
        pts = list(map(lambda x: self.map_pixel_to_world(x[0], x[1]), pts))
        return autonomous_nav.generate_path_greedy(coor, pts)


    # map map pixel into world coordinates
    def world_to_map_pixel(self, world_x, world_y, world_theta=0.2):
        assert self.map_data["resolution"] is not None
        x = int((world_x - self.map_data["origin"][0])/self.map_data["resolution"])
        y = int(self.map_data["height"] - (world_y - self.map_data["origin"][1])/self.map_data["resolution"] )
        return x, y
    
    def map_pixel_to_world(self, x, y, theta=0):
        assert not self.map_data["resolution"] is None
        world_x = x*self.map_data["resolution"] + self.map_data["origin"][0]
        world_y = (self.map_data["height"]-y)*self.map_data["resolution"] + self.map_data["origin"][1]
        return world_x, world_y
    
    def reset_camera_and_continue(self):
        smsg = String()
        smsg.data = "ring"
        def moving_finished():
            self.arm_finished_callback = None
            self.mover.run_deferred(lambda: self.mover.continueTask())
            self.is_parking = False

        self.arm_finished_callback = moving_finished
        self.arm_move_pub.publish(smsg)


    def _parking_finished(self, _: Empty):
        def cb(fut):
            fut = fut.result()
            self.get_logger().info(f"camera reset with status {fut.status}")
            #if fut.status == GoalStatus.STATUS_ACCEPTED:
            self.find_and_goto_nearest_cylinder()
        self.reset_camera_and_look_around(cb)

    # when parking place was found (by parker)
    def _parking_found(self, msg: Empty):
        if self.mover is None:
            self.info("mover is none. ignoring start_stop_callback")
            return
        self.info("parking was found. canceling current task.")
        self.mover.cancelTask()
    
    # when a green ring was detected.
    def _green_ring_detected(self, msg: Marker):
        self.mover.searched_ring_detected(msg)
        #if self.park_search_enabled or self.is_parking:
        #    return
        #self.is_parking = True
        #self.park_search_enabled = True
        #stamped = self.pose_to_pose_stamped(msg.pose)
        #def move_finished(r: bool):
        #    if r:
        #        self.mover.run_deferred(lambda: self.mover.continueTask())
        #self.mover.visit_point(stamped, defer = True, callback = move_finished)
        #return
    
    def _arm_task_callback(self, _: Empty):
        if self.arm_finished_callback is not None:
            cback = self.arm_finished_callback
            self.arm_finished_callback = None
            cback()

    # when a parking place was found (by ring detector)
    def _parking_place_detected(self, msg: Pose):
        self.park_search_enabled = False
        stamped = self.pose_to_pose_stamped(msg)
        def arm_moved():
            self.arm_finished_callback = None
            def move_finished(r: bool):
                if r:
                    # disable parker
                    if self.parking_node_disabled:
                        self.reset_camera_and_continue()
                    return
            self.park_enable_pub.publish(Empty())
            self.mover.visit_point(stamped, defer = True, override = True, callback = move_finished)
            pass

        def task_canceled():
            # set arm camera to search for parkplaces and wait
            self.arm_finished_callback = arm_moved
            smsg = String()
            smsg.data = "look_for_parking"
            self.arm_move_pub.publish(smsg)

        self.mover.cancelTask(task_canceled)
        return
    
    # ===================================================
    # Task 3 stuff
    # ===================================================
    def find_and_goto_nearest_cylinder(self):
        m = Marker()
        m.pose = self.current_pose.pose
        cyl = self.mover.closest_cylinder(m)
        self.cylinder_detected(cyl)
    
    def publish_color(self, color: str):
        msg = String()
        msg.data = color
        self.ring_color_pub.publish(msg)
    
    def _cyl_marker_callback(self, msg: Marker):
        if self.mover is None:
            return
        self.mover.cylinder_detected(msg)

    # continue moving
    def continue_moving(self, msg = None):
        self.mover.run_deferred(lambda: self.mover.visit_unvisited_face_or_next_goal())

    # called when cylinder is detected    
    def cylinder_detected(self, msg: Marker):
        stamped = self.pose_to_pose_stamped(msg.pose)
        def move_finished(r: bool):
            self.get_logger().info(f"finished moving to cylinder: {r}")
            if not r:
                self.continue_moving()
        qrmsg = String()
        qrmsg.data = "qr"
        self.arm_move_pub.publish(qrmsg)
        self.look_qr_pub.publish(Empty())
        self.mover.visit_point(stamped, defer = True, callback = move_finished, override = True)
    
    def qr_code_found(self, msg: Bool):
        self.is_parking = False
        self.mover.qr_found(msg.data)
    
    def reset_camera_and_look_around(self, callback):
        smsg = String()
        smsg.data = "ring"
        def moving_finished():
            self.arm_finished_callback = None
            #self.is_parking = False
            self.get_logger().info("arm is back up! rotating ...")
            self.mover.run_deferred(lambda: self.spin_callback(math.pi * 2, callback=callback))
        self.arm_finished_callback = moving_finished
        self.arm_move_pub.publish(smsg)
    
    def signal_ring_target(self, marker: Marker):
        self.ring_target_pub.publish(marker)
    
    # called when a new mona lisa is detected.
    def _mona_marker_callback(self, marker: Marker):
        self.mover.new_mona_marker(marker)
    
    def anomaly_detected_callback(self, msg: Bool):
        if msg.data:
            # found the REAL mona lisa. raise hand and finish
            self.mover.finish()
            strmsg = String()
            strmsg.data = "up"
            self.arm_move_pub.publish(strmsg)
        else:
            # fake monalisa, continue search
            self.mover.end_visit()
            self.continue_moving()
    
    # called when mona lisa is visited. signalize that to the anomaly detection node
    # which will then signalize back that program must continue
    def on_monalisa_visited(self):
        self.begin_detecting_anomalies_pub.publish(Empty())




def main(args=None):
    
    rclpy.init(args=args)
    parser = argparse.ArgumentParser(description="The robbot KOMMANDER!")
    parser.add_argument('--move-only', action='store_true', help='Enable move-only mode')
    parsed_args = parser.parse_args(args=args[1:])  # Skip the first argument which is the program name

    rc = RobotCommander(move_only=parsed_args.move_only)
    mover = robot_mover.RobotMover(rc, rc.get_logger(), 0, faces_needed=None)
    rc.setMover(mover)

    # Wait until Nav2 and Localizer are available
    rc.waitUntilNav2Active()

    # Check if the robot is docked, only continue when a message is recieved
    while rc.is_docked is None:
        rclpy.spin_once(rc, timeout_sec=0.5)

    # If it is docked, undock it first
    if rc.is_docked:
        rc.undock()

    rc.generate_and_set_goals()
    mover.run()

    # wait until 3. razvojna os is finished
    while True:
        time.sleep(1)

    #rc.visitGoals(poses)
    #rc.info("complete!")

    # Finally send it a goal to reach
    #goal_pose = PoseStamped()
    #goal_pose.header.frame_id = 'map'
    #goal_pose.header.stamp = rc.get_clock().now().to_msg()
#
    #goal_pose.pose.position.x = 2.6
    #goal_pose.pose.position.y = -1.3
    #goal_pose.pose.orientation = rc.YawToQuaternion(0.57)
#
    #rc.goToPose(goal_pose)
#
    #while not rc.isTaskComplete():
        #rc.info("Waiting for the task to complete...")
        #time.sleep(1)

    rc.spin(-0.57)

    rc.destroyNode()

    # And a simple example
if __name__=="__main__":
    import sys
    main(sys.argv)