cmake_minimum_required(VERSION 3.8)
project(distance_warning)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. Tìm các package phụ thuộc
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# 2. Tạo các interface tùy chỉnh (srv, action)
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/SetThreshold.srv"
  "action/CheckDistance.action"
)

# 3. Các node từ BTVN_01
add_executable(distance_listener src/distance_listener.cpp) 
ament_target_dependencies(distance_listener rclcpp std_msgs)

add_executable(distance_publisher src/distance_publisher.cpp)
ament_target_dependencies(distance_publisher rclcpp std_msgs)

add_executable(set_threshold_service src/set_threshold_service.cpp)
ament_target_dependencies(set_threshold_service rclcpp std_msgs)
rosidl_target_interfaces(set_threshold_service ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(distance_action_server src/distance_action_server.cpp)
ament_target_dependencies(distance_action_server rclcpp std_msgs rclcpp_action)
rosidl_target_interfaces(distance_action_server ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(distance_action_client src/distance_action_client.cpp)
ament_target_dependencies(distance_action_client rclcpp std_msgs rclcpp_action)
rosidl_target_interfaces(distance_action_client ${PROJECT_NAME} "rosidl_typesupport_cpp")

# 4. Các node mới BTVN_02
add_executable(distance_tf_broadcaster src/distance_tf_broadcaster.cpp)
ament_target_dependencies(distance_tf_broadcaster rclcpp std_msgs geometry_msgs tf2 tf2_ros)

add_executable(distance_tf_listener src/distance_tf_listener.cpp)
ament_target_dependencies(distance_tf_listener rclcpp tf2 tf2_ros tf2_geometry_msgs)  
rosidl_target_interfaces(distance_tf_listener ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(distance_publisher_qos src/distance_publisher_qos.cpp)
ament_target_dependencies(distance_publisher_qos rclcpp std_msgs)

add_executable(distance_listener_qos src/distance_listener_qos.cpp)
ament_target_dependencies(distance_listener_qos rclcpp std_msgs)

# 5. Cài đặt (Install) - Để ros2 run có thể tìm thấy
install(TARGETS
  distance_listener
  distance_publisher
  set_threshold_service
  distance_action_server
  distance_action_client
  distance_tf_broadcaster
  distance_tf_listener
  distance_publisher_qos
  distance_listener_qos
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

# 6. Export dependencies và kết thúc 
ament_export_dependencies(rosidl_default_runtime)
ament_package()