cmake_minimum_required(VERSION 3.8)
project(ros2_cpp_learning)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()




# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(cv_bridge REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#Generate custom interfaces

rosidl_generate_interfaces(${PROJECT_NAME}
    "srv/OddEventCheck.srv"
    "srv/GetImage.srv"
    DEPENDENCIES
    sensor_msgs
    ADD_LINTER_TESTS
)

# Set support for a custom mensages

rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(publisher src/publisher.cpp)
ament_target_dependencies(publisher rclcpp std_msgs)

add_executable(subscriber src/subscriber.cpp)
ament_target_dependencies(subscriber rclcpp std_msgs sensor_msgs)


add_executable(rpm_pub src/rpm_pub.cpp)
ament_target_dependencies(rpm_pub rclcpp std_msgs)

add_executable(converter_rpm2speed src/converter_rpm2speed.cpp)
ament_target_dependencies(converter_rpm2speed rclcpp std_msgs)

add_executable(service_server src/service_server.cpp)
ament_target_dependencies(service_server rclcpp std_msgs)


add_executable(service_client src/service_client.cpp)
ament_target_dependencies(service_client rclcpp std_msgs)

add_executable(service_server_image src/service_server_image.cpp)
ament_target_dependencies(service_server_image rclcpp std_msgs sensor_msgs OpenCV cv_bridge)


add_executable(service_client_image src/service_client_image.cpp)
ament_target_dependencies(service_client_image rclcpp std_msgs sensor_msgs OpenCV cv_bridge)

target_link_libraries(service_client "${cpp_typesupport_target}")
target_link_libraries(service_server "${cpp_typesupport_target}")

target_link_libraries(service_client_image "${cpp_typesupport_target}" ${OpenCV_LIBS})
target_link_libraries(service_server_image "${cpp_typesupport_target}" ${OpenCV_LIBS})


install(TARGETS
  publisher
  subscriber
  rpm_pub
  converter_rpm2speed
  service_server
  service_client
  service_server_image
  service_client_image
  DESTINATION lib/${PROJECT_NAME}
  )

install(DIRECTORY
    launch
    DESTINATION share/${PROJECT_NAME}/
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

ament_package()
