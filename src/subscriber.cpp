#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

class HelloWorldSubNode : public rclcpp::Node
{

    public:
        HelloWorldSubNode() : Node("hello_world_sub_node"){
            subscription_ = this->create_subscription<std_msgs::msg::String>("hello_world", 10, std::bind(&HelloWorldSubNode::sub_callback, this, std::placeholders::_1));

        }
    private:
        void sub_callback(const std_msgs::msg::String & msg) const{
            std::cout << msg.data << std::endl;
            RCLCPP_INFO(this->get_logger(), msg.data.c_str());
            //RCLCPP_ERROR(this->get_logger(), msg.data.c_str());
            //RCLCPP_WARN(this->get_logger(), msg.data.c_str());
        }
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
        rclcpp::TimerBase::SharedPtr timer_;
        size_t counter_ = 0;
};

int main(int argc, char * argv[]){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HelloWorldSubNode>());
    return 0;


}

