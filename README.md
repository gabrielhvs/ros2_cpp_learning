# Curse ROS2 and C++

## Debug in ros

sudo apt-get install gdbserver

ros2 run --prefix 'gdbserver loaclhast:3000' package app

## To no generate double files in build 

colcon build --symlink-install

## List interfaces

ros2 inteface list -> to list all messages, actions and services types

## Work with parameters

ros2 param list -> lista os parametros de cada nó do sistema
ros2 param get <Node> <Param>
ros2 param describe <Node> <Param>
ros2 param set <Node> <Param> <value>

ros2 node list -> list all nodes in system

ros2 launch <pkg_name> <launch_file> -> run project using launch.py

## Services

ros2 interface list
ros2 service list
ros2 service call <service_name> <srv_type> <req>

## Using OpenCV

### Include OpenCV

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/cv_bridge.hpp>

### Read In Image From File

auto image = cv::imread("/path/to/image.png);

### Display Image In OPenCV Window

cv::imshow("Robot Camera Image", image);
cv::waitKey(0);

### Converting OpenCV image to Ros Image Interface

auto image_msg_ptr = cv_bridge::CvImage(
    std_msgs::msg::Header(), "brg8", image).toImageMsg();
image_msg = *imate_ptr;

### Converting Ros Image Interface To OpenCV Image

auto cv_ptr = cv_bridge::toCvCopy(result.get()->response_attr_name, "brg8");
image = cv_ptr->image;

### Using INterfaces from other ROS Package in Custom Interface

sensor_msgs/Image request_attr_name

### Add Ros IDL Dependencies In CMakeLists.txt

rosidl_generate_interfaces(${PROJECT_NAME}
    "srv/YourSrvName.srv"
    DEPENDENCIES
    sensor_msgs
)


sudo apt install ros-$ROS_DISTRO-cv-brigde

## Instal Third Packages

sudo apt install ros-$ROS_DISTRO-usb-cam


## Log using Ros2

ros2 bag record \topic_name 

ros2 bag record -a 

ros2 bag record -o name_of_log

ros2 bag player name_of_log

## Using GAzebo

sudo apt install ros-$ROS_DISTRO-ros-ign-brigde

ign gazebo

ign gazebo name_of_model

ign topic -l 

ros2 run ros_ign_brigde paramter_brigde ...

export IGN_GAZEBO_RESOURCE_PATH = path_contens_constom_model