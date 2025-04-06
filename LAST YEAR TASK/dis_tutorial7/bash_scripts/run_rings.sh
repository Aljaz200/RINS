#!/bin/bash

# run ring detection and parking detection and arm_mover
trap 'kill $(jobs -p)' EXIT
ros2 run dis_tutorial7 detect_rings.py &
ros2 run dis_tutorial7 arm_mover_actions.py &
ros2 run dis_tutorial7 detect_parkings.py &
ros2 run dis_tutorial7 detect_qr.py &
ros2 run dis_tutorial7 detect_faces.py &
ros2 run dis_tutorial7 parker.py &
#ros2 run dis_tutorial7 cylinder_segmentation &
ros2 run dis_tutorial7 detect_cylinders.py &
ros2 run dis_tutorial7 detect_anomalies.py &

wait