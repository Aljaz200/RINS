#! /usr/bin/env python3

# faces { index: {visited : bool, markers : array }}

from geometry_msgs.msg import Quaternion, PoseStamped, PoseWithCovarianceStamped
import numpy as np
import time
from visualization_msgs.msg import Marker
import detect_faces

STATUS_SUCCEEDED = 4

class RobotMover:

    def __init__(self, commander, logger, n_goals = 0, faces_needed = None):
        self.faces = {}
        self.running = False
        self.commander = commander
        self.goals_done = False
        self.logger = logger
        self.faces_needed = faces_needed
        self.is_visiting = False
        self.visited_faces = 0
        self.current_goal = 0
        self.paused = True
        self.n_goals = n_goals
        self.deferred = []
        self.finished = False
        # key is ring color, value is ring marker and visited pair
        self.ring_markers = {}
        
    
    #===========================================================
    # task 3 stuff here
    #===========================================================
    def finish(self):
        self.finished = True
    
    def end_visit(self):
        self.is_visiting = False


    def searched_ring_detected(self, msg: Marker):
        
        self.ring_markers[msg.text] = {"marker": msg, "visited": False}
        self.visit_ring(msg, deferred=True)
                
    # gets an unvisited ring in queue if any
    def get_unvisited_ring(self) -> Marker | None:
        for val in self.ring_markers.values():
            if not val["visited"]:
                return val["marker"]
        return None
    
    # visit ring
    def visit_ring(self, ring: Marker, deferred = False):
        if self.is_visiting or not self.running:
            return
        if deferred:
            self.run_deferred(lambda: self.visit_ring(ring, deferred=False))
            return
        self.is_visiting = True
        #self.commander.signal_ring_target(ring)
        stamped = self.commander.pose_to_pose_stamped(ring.pose)
        def move_finished(r: bool):
            self.ring_markers[ring.text]["visited"] = True
            if r:
                self.continueTask()
        print("NENEN")
        self.visit_point(stamped, defer = True, callback = move_finished, override=True)
   
    # process next ring in line
    def process_next_ring(self) -> bool:
        ring = self.get_unvisited_ring()
        if ring is None:
            return False
        self.visit_ring(ring)
        return True
    


    # visits a ring inside internal buffer if there is any unvisited ring there
    # otherwise it continues searching the map. this function runs deferred by default
    def visit_ring_or_next_goal(self, deferred = True):
        if deferred:
            self.run_deferred(lambda: self.visit_ring_or_next_goal(deferred=False))
            return
        if self.process_next_ring():
            return
        self.visit_goals()

    def set_n_goals(self, n_goals: int):
        self.n_goals = n_goals

    def set_paused(self, paused: bool):
        self.paused = paused

    def average_marker(self, face) -> PoseStamped:
        return self.commander.pose_to_pose_stamped(face["markers"][-1].pose)
        values = [(m.pose.position.x, m.pose.position.y, m.pose.orientation.w) for m in face["markers"]]
        av = np.average(values, axis=0)
        return self.commander.newPose(av[0], av[1], av[2])

    def playSound(self):
        pass

    def cancelTask(self, cancelCallback = None):
        def cancel_cb(_):
            if cancelCallback is None:
                return
            cancelCallback()

        def deferred_call():
            self.commander.cancelTask(callback=cancel_cb)
        self.run_deferred(deferred_call)

    def continueTask(self):
        self.run_deferred(lambda: self.visit_goals())

    def visit_goals(self):
        self.logger.info(f"visiting goal {self.current_goal}")
        goal = self.commander.getGoal(0)
        if goal is None:
            self.goals_done = True
            self.logger.info(f"Visited all goals! Finished, detected {len(self.faces)} faces.")
            return
        def visit_next_goal(future):
            future = future.result()
            self.logger.info(f"goal result {future}")
            if future.status != STATUS_SUCCEEDED:
                return
            self.commander.goalVisited(self.current_goal)
            self.current_goal += 1
            # TODO maybe check here if any stored rings
            self.visit_goals()
        self.commander.visitGoalCallback(goal, callback=visit_next_goal)

    def visit_unvisited_face_or_next_goal(self):
        for i in self.faces:
            if not self.faces[i]["visited"]:
                try:
                    self.logger.info(f"visiting unvisited face {i}")
                    self.visit_face(i)
                except Exception as e:
                    print(e)
                return
        self.logger.info("no saved unvisited faces, visiting unvisited rings (if any)")
        self.visit_ring_or_next_goal()

    # use this for deferred calls
    def run(self):
        self.running = True
        while self.paused:
            time.sleep(0.05)
        self.logger.info("running ...")
        self.run_deferred(lambda: self.visit_unvisited_face_or_next_goal())
        self.logger.info("loop start ...")
        while not self.finished:
            if self.paused:
                time.sleep(0.05)
                continue
            self.commander.process()
            if len(self.deferred) > 0:
                self.logger.info(f"processing {len(self.deferred)} calls.")
                for d in self.deferred:
                    d()
                self.deferred = []
            time.sleep(0.05)
        while True:
            self.commander.process()
            time.sleep(0.05)

    def run_deferred(self, callback):
        self.logger.info("accepted a deferred call.")
        self.deferred.append(callback)

    def should_continue(self):
        if self.finished:
            return False
        return self.faces_needed is None or self.visited_faces < self.faces_needed

    def visit_point(self, point, defer = False, override = False, callback = None):
        if not self.should_continue():
            return
        if defer:
            self.run_deferred(lambda: self.visit_point(point, override=override, callback=callback))
            return
        if self.is_visiting and not override:
            return
        self.is_visiting = True

        # when point is visited, trigger the callback to process it, only if the visit was successful
        def point_visited(future):
            future = future.result()
            if callback is None:
                return
            self.is_visiting = False
            self.logger.info(f"finished moving to point {future.status}")
            callback(future.status == STATUS_SUCCEEDED)

        def oncancel(_):
            self.logger.info("moving cancelled!")
            self.commander.visitGoalCallback(point, callback=point_visited)
        self.commander.cancelTask(callback=oncancel)

    # this function runs after the robot moves in front of the face and looks towards it
    def process_face_after_visited(self):
        self.detect_faces.announce_hello()
        

    def visit_face(self, id, defer = False) -> bool:
        if not self.should_continue():
            self.logger.info("no longer continuing so faces will not be visited.")
            return False
        if defer:
            self.run_deferred(lambda: self.visit_face(id))
            return True
        if self.is_visiting:
            self.logger.info("already visiting, cannot visit another face")
            return False
        self.is_visiting = True
        if not id in self.faces:
            self.logger.info(f"cannot visit face with id {id} because it doesn't exist")
            self.is_visiting = False
            return False
        pose = self.average_marker(self.faces[id])

        def face_visited(future):
            # TODO check if the distance is too large and visit the face again
            self.logger.info(f"Face {id} visited! {future.result()}")
            self.visited_faces += 1
            self.faces[id]["visited"] = True
            self.process_face_after_visited()
            self.is_visiting = False
            if self.should_continue():
                self.visit_unvisited_face_or_next_goal()
            else:
                self.logger.info("Visited all required faces!")

        # on cancel
        def oncancel(future):
            self.logger.info("moving canceled!")
            self.commander.visitGoalCallback(pose, callback=face_visited)
        
        self.logger.info("cancelling current task ...")
        self.commander.cancelTask(callback=oncancel)
        return True


    
    # called from RobotCommander which subscribes to face detector
    def newMarker(self, marker):
        self.logger.info(f"new marker-face: {marker.id} : {self.is_visiting}")
        if not self.should_continue():
            return
        if marker.id in self.faces:
            face = self.faces[marker.id]
            if face["visited"]:
                return
            if self.is_visiting or not self.running:
                face["markers"].append(marker)
            else:
                self.visit_face(marker.id, defer = True)
        else:
            self.faces[marker.id] = {"visited": False, "markers": [marker]}
            if not self.is_visiting and self.running:
                try:
                    self.logger.info(f"visiting face {marker.id}...")
                    self.visit_face(marker.id, defer = True)
                except Exception as e:
                    self.logger.info(f"could not visit: {e}")

    def newMarkerCircle(self, marker):
        self.logger.info(f"new marker-ring: {marker.id} : {self.is_visiting}")
        if not self.should_continue():
            return
        if marker.id in self.ring_markers:
            ring = self.ring_markers[marker.id]
            if ring["visited"]:
                return
            if self.is_visiting or not self.running:
                ring["markers"].append(marker)
            else:
                self.visit_ring(marker.id, deferred = True)
        else:
            self.ring_markers[marker.id] = {"visited": False, "markers": [marker]}
            if not self.is_visiting and self.running:
                try:
                    self.logger.info(f"visiting circle {marker.id}...")
                    self.visit_ring(marker.id, deferred = True)
                except Exception as e:
                    self.logger.info(f"could not visit: {e}")
        
            
        
    
