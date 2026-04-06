cmake_minimum_required(VERSION 3.8)
project(distance_warning)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/SetThreshold.srv"
  "action/CheckDistance.action"
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(rosidl_default_runtime)
ament_package()

# TODO: Thêm executable cho từng node  

# DISTANCE LISTENER
add_executable(distance_listener src/distance_listener.cpp) 
ament_target_dependencies(distance_listener rclcpp std_msgs)


# DISTANCE PUBLISHER
add_executable(distance_publisher src/distance_publisher.cpp)
ament_target_dependencies(distance_publisher rclcpp std_msgs)

# Set Threshold Service
add_executable(set_threshold_service src/set_threshold_service.cpp)
ament_target_dependencies(set_threshold_service rclcpp std_msgs)
rosidl_target_interfaces(set_threshold_service
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

#Distance Action Server
add_executable(distance_action_server src/distance_action_server.cpp)
ament_target_dependencies(distance_action_server rclcpp std_msgs rclcpp_action)
rosidl_target_interfaces(distance_action_server
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

# Distance Action Client
add_executable(distance_action_client src/distance_action_client.cpp)
ament_target_dependencies(distance_action_client rclcpp std_msgs rclcpp_action)
rosidl_target_interfaces(distance_action_client
  ${PROJECT_NAME} "rosidl_typesupport_cpp")
# INSTALL
install(TARGETS
  distance_listener
  distance_publisher
  set_threshold_service
  distance_action_server
  distance_action_client
  DESTINATION lib/${PROJECT_NAME}
)

install (DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)
