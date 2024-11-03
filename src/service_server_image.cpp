#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "ros2_cpp_learning/srv/get_image.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <string>

typedef ros2_cpp_learning::srv::GetImage GetImageSrv;

class GetImageServiceNode : public rclcpp::Node {

    public:
        GetImageServiceNode() : Node("get_image_service_node")
        {
            service_server_ = this->create_service<GetImageSrv>(
                "get_image",
                std::bind(&GetImageServiceNode::get_image_angle, this,
                std::placeholders::_1, std::placeholders::_2
                )
            );
        }
    private: 
        void get_image_angle(const GetImageSrv::Request::SharedPtr request,
        GetImageSrv::Response::SharedPtr response){

            cv::Mat image = cv::imread("src/ros2_cpp_learning/images/" + 
                                    std::to_string(request->angle) + 
                                    ".png");

            cv::imshow("Image Requested", image);
            cv::waitKey(0);
        
            sensor_msgs::msg::Image::SharedPtr image_msg_ptr = cv_bridge::CvImage(
                std_msgs::msg::Header(), "rgb8", image).toImageMsg();

            response->image = *image_msg_ptr;

        }
        rclcpp::Service<GetImageSrv>::SharedPtr service_server_;
};



int main(int argc, char * argv[]){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GetImageServiceNode>());
    return 0;
}