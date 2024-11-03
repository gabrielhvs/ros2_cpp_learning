#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "ros2_cpp_learning/srv/get_image.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

typedef ros2_cpp_learning::srv::GetImage GetImageSrv;

int main(int argc, char * argv[]){

    rclcpp::init(argc, argv);

    auto service_client_node  = rclcpp::Node::make_shared("get_image_client_node");
    auto client = service_client_node->create_client<GetImageSrv>("get_image");

    auto request = std::make_shared<GetImageSrv::Request>();

    std::cout << "Angle image that you need:  ";
    std::cin >> request->angle;

    client->wait_for_service();

    auto result = client->async_send_request(request);


    if(rclcpp::spin_until_future_complete(service_client_node, result) == 
        rclcpp::FutureReturnCode::SUCCESS){


            auto cv_ptr = cv_bridge::toCvCopy(result.get()->image, "rgb8");

            cv::imshow("Image Response", cv_ptr->image);
            cv::waitKey(0);

        }
    else{
            std::cout << "there was an error processing the request... " << std::endl;
    }

    rclcpp::shutdown();
    return 0;
}