#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"


#include <chrono>
#include <iostream>
#include <math.h>

using namespace std::chrono_literals;

#define RAIO 0.5

class ConverterNode : public rclcpp::Node
{

    public:
        ConverterNode() : Node("converter_node"){
            this->declare_parameter<double>("wheel_radios", RAIO);
            subscription_ = this->create_subscription<std_msgs::msg::Float64>("rpm", 10, std::bind(&ConverterNode::sub_callback, this, std::placeholders::_1));
            publisher_ = this->create_publisher<std_msgs::msg::Float64>("speed", 10);
        }
    private:
        void sub_callback(const std_msgs::msg::Float64 & rpm) const{
            auto message = std_msgs::msg::Float64();
            rclcpp::Parameter wheel_radios_param_ = this->get_parameter("wheel_radios");
            message.data = rpm.data * (2 * wheel_radios_param_.as_double() * M_PI)/60.0;
            publisher_->publish(message);
        }
        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
};

int main(int argc, char * argv[]){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ConverterNode>());
    return 0;


}

