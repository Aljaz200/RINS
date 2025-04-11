#!/bin/bash

# run ring detection and face detection
trap 'kill $(jobs -p)' EXIT
ros2 run task detect_faces.py &
ros2 run task temp.py

wait
