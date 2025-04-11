#!/usr/bin/python3
import os
import pygame
from gtts import gTTS
from threading import Thread, Lock
import rclpy
from rclpy.node import Node
from visualization_msgs.msg import MarkerArray
import numpy as np
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy, QoSDurabilityPolicy

class RingVoiceNode(Node):
    def __init__(self):
        super().__init__('ring_voice_node')

        # Initialize pygame mixer for audio playback
        pygame.mixer.init()

        # Create a dictionary to store pre-generated audio files
        self.audio_files = {}
        self.audio_lock = Lock()

        # Data structures to track announced rings
        self.announced_positions = {}  # Dictionary mapping position hash -> color
        self.position_threshold = 0.5  # Distance threshold in meters

        # Define colors we'll announce
        self.colors = ['red', 'green', 'blue', 'yellow']

        # Pre-generate audio files
        self.pre_generate_audio()

        # Create QoS profile for reliable marker subscription
        qos_profile = QoSProfile(
            reliability=QoSReliabilityPolicy.RELIABLE,
            durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
            history=QoSHistoryPolicy.KEEP_LAST,
            depth=10
        )

        # Subscribe to the ring markers topic
        self.markers_subscription = self.create_subscription(
            MarkerArray,
            '/ring_markers',
            self.markers_callback,
            qos_profile
        )

        self.get_logger().info('Ring Voice Node initialized and ready to announce colors')

    def pre_generate_audio(self):
        """Pre-generate audio files for all colors"""
        for color in self.colors:
            audio_file = f"/tmp/{color}_ring.mp3"
            # Check if the file already exists
            if not os.path.exists(audio_file):
                self.get_logger().info(f"Generating audio file for {color} ring")
                tts = gTTS(f"{color} ring detected", lang='en')
                tts.save(audio_file)
            self.audio_files[color] = audio_file

    def play_audio(self, color):
        """Play the audio file for the specified color"""
        with self.audio_lock:
            try:
                # Play the audio file
                if color in self.audio_files:
                    #self.get_logger().info(f"Announcing {color} ring")
                    pygame.mixer.music.load(self.audio_files[color])
                    pygame.mixer.music.play()
                    while pygame.mixer.music.get_busy():
                        pygame.time.delay(100)
                else:
                    self.get_logger().warn(f"No audio file for {color}")
            except Exception as e:
                self.get_logger().error(f"Error playing audio: {e}")

    def position_hash(self, position):
        """Create a simple hash from a position rounded to the nearest 0.1m"""
        return f"{position[0]:.1f}_{position[1]:.1f}_{position[2]:.1f}"

    def markers_callback(self, msg):
        """Process the markers array to detect rings and their positions"""
        # Extract rings from markers
        detected_rings = []

        # Process each marker
        for marker in msg.markers:
            # Only process sphere markers (the ring positions)
            if marker.type == 2 and marker.ns == "ring_positions":  # SPHERE type
                position = np.array([
                    marker.pose.position.x,
                    marker.pose.position.y,
                    marker.pose.position.z
                ])

                # Extract color from the marker
                r, g, b = marker.color.r, marker.color.g, marker.color.b
                color = self.classify_color(r, g, b)

                if color:
                    detected_rings.append((color, position))

        # Process each detected ring
        for color, position in detected_rings:
            # Check if this ring is a new one that needs announcing
            if not self.is_position_announced(position):
                # This is a new ring we haven't announced yet
                Thread(target=self.play_audio, args=(color,)).start()

                # Mark this position as announced
                position_key = self.find_matching_position(position)
                if not position_key:
                    position_key = self.position_hash(position)

                self.announced_positions[position_key] = color
                self.get_logger().info(f"Announced {color} ring at position: ({position[0]:.2f}, {position[1]:.2f}, {position[2]:.2f})")

    def classify_color(self, r, g, b):
        """Convert RGB values to one of our recognized colors"""
        # Simple classification based on which channel is dominant
        if r > 0.5 and g < 0.3 and b < 0.3:
            return 'red'
        elif g > 0.5 and r < 0.3 and b < 0.3:
            return 'green'
        elif b > 0.5 and r < 0.3 and g < 0.3:
            return 'blue'
        elif r > 0.5 and g > 0.5 and b < 0.3:
            return 'yellow'
        return None

    def find_matching_position(self, position):
        """Find if a position is close to any previously announced position"""
        for pos_hash in self.announced_positions:
            # Convert the hash back to a position
            x, y, z = map(float, pos_hash.split('_'))
            stored_position = np.array([x, y, z])

            # Check if the current position is within threshold of this stored position
            distance = np.linalg.norm(position - stored_position)
            if distance < self.position_threshold:
                return pos_hash

        return None

    def is_position_announced(self, position):
        """Check if a position has already been announced"""
        return self.find_matching_position(position) is not None

def main(args=None):
    rclpy.init(args=args)
    voice_node = RingVoiceNode()

    try:
        rclpy.spin(voice_node)
    except KeyboardInterrupt:
        pass
    finally:
        voice_node.get_logger().info('Shutting down Ring Voice Node')
        voice_node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
