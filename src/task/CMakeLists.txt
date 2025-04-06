cmake_minimum_required(VERSION 3.5)
project(task)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)

find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)

find_package(visualization_msgs REQUIRED)

find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL 1.10 REQUIRED)

set(dependencies rclcpp std_msgs geometry_msgs sensor_msgs visualization_msgs tf2 tf2_geometry_msgs pcl_conversions)


install(DIRECTORY
  launch
  meshes
  urdf
  config
  DESTINATION share/${PROJECT_NAME}/
)

install(PROGRAMS
  scripts/arm_mover_actions.py
  scripts/robot_commander.py
  scripts/autonomous_nav.py
  scripts/detect_parkings.py
  scripts/detect_rings.py
  scripts/parker.py
  scripts/ring_unique.py
  scripts/robot_mover.py
  scripts/detect_cylinders.py
  scripts/detect_qr.py
  scripts/detect_faces.py
  scripts/speech.py
  scripts/detect_anomalies.py
  scripts/padim_model.py
  scripts/face_saver.py

  scripts/detector_utils.py
  scripts/image_utils.py
  scripts/padim_utils.py
  DESTINATION lib/${PROJECT_NAME})

ament_package()

