#!/bin/bash

# run ring detection and face detection
trap 'kill $(jobs -p)' EXIT
ros2 run task detect_rings.py &
ros2 run task detect_parkings.py &
ros2 run task detect_faces.py &
ros2 run task parker.py &

wait