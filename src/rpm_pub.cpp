#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

#include <chrono>

using namespace std::chrono_literals;

#define RPM_BASE 100.0

class RPMPubNode : public rclcpp::Node
{

    public:
        RPMPubNode() : Node("sensor_node"){
            this->declare_parameter<double>("rpm_val", RPM_BASE);
            publisher_ = this->create_publisher<std_msgs::msg::Float64>("rpm", 10);
            timer_ = this->create_wall_timer(1s, std::bind(&RPMPubNode::publish_rpm, this));

        }
    private:
        void publish_rpm(){
            auto message = std_msgs::msg::Float64();
            
            rclcpp::Parameter rpm_val_param_ = this->get_parameter("rpm_val");
            message.data = rpm_val_param_.as_double() + float(counter_);
            publisher_->publish(message);
            counter_++;
        }
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        size_t counter_ = 0;
};

int main(int argc, char * argv[]){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RPMPubNode>());
    return 0;


}

