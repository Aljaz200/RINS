cmake_minimum_required(VERSION 3.5)
project(hwpub)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Always find ament_cmake
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

# Find all the packages that we are using
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)

# This is needed if we generate custom interfaces (messages, services or actions)
find_package(rosidl_default_generators REQUIRED)

# A macro, not to repeat the dependencies
set(dependencies rclcpp std_msgs std_srvs rosidl_default_generators)

# We list the interface files and their dependencies
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Hwmsg.msg"
  "srv/Customserv.srv"
  DEPENDENCIES std_msgs # Add packages that the listed interfaces depend on
)

# Install Python executables
install(PROGRAMS
  scripts/py_move_trajectory.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_export_dependencies(${dependencies} rosidl_default_runtime)
ament_package()
