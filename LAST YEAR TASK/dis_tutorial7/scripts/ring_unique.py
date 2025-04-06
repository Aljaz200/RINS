import cv2
import rclpy
import numpy as np
from visualization_msgs.msg import Marker


class Ring:
    def __init__(self, location, color=None, colorstring=None):
        self.id = -1
        self.location = location
        self.color = color
        self.colorstring = colorstring
    
    def marker(self) -> Marker:
        mark = Marker()
        mark.header.frame_id = "map"
        mark.header.stamp = rclpy.time.Time().to_msg()
        mark.ns = "green"
        mark.id = 0
        if self.colorstring is not None:
            mark.text = self.colorstring
        mark.pose.position.x = self.location[0]
        mark.pose.position.y = self.location[1]
        mark.pose.position.z = self.location[2]
        mark.color.a = 1.0
        mark.color.r = 0.0
        mark.color.g = 1.0
        mark.color.b = 0.0
        mark.scale.x = 0.25
        mark.scale.y = 0.25
        mark.scale.z = 0.25
        return mark
        
class UniqueRings:
    
    def __init__(self, safety_param=0.1):
        self.safety_param = safety_param
        self.rings = set()
        self.ring_color_map = {}
        self._availible_id = 0
        
    def _add_ring(self, ring: Ring) -> tuple[bool, int]:
        len_before = len(self.rings)
        ring.id = self._availible_id
        location = ring.location
        for x in self.rings:
            if self._is_match(location, x.location):
                return False, x.id
        self.rings.add(ring)
        if len(self.rings) > len_before:
            self._availible_id += 1
            return True, self._availible_id - 1
        
    def get_unique_rings(self) -> list[Ring]:
        return list(self.rings)
    
    def _is_match(self, location1, location2) -> bool:
        dif = location1 - location2
        # print(f'dif: {np.linalg.norm(dif)}')
        return np.linalg.norm(dif) < self.safety_param
    
    def get_ring_by_color(self, colorstring: str) -> Ring | None:
        if colorstring in self.ring_color_map:
            return self.ring_color_map[colorstring]
        return None

    def get_stored_colorstrings(self) -> list[str]:
        return list(self.ring_color_map.keys())

    def store_ring(self, location, color=None, colorstring=None, gib_ring=False) -> tuple[bool, int] | tuple[bool, int, Ring]:
        # print(f'Adding ring {location}')
        ring = Ring(location, color=color, colorstring=colorstring)
        tf, idd = self._add_ring(ring)
        if tf and colorstring is not None:
            self.ring_color_map[colorstring] = ring
        if gib_ring:
            return tf, idd, ring
        return tf, idd
