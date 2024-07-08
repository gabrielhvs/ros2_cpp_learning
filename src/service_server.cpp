#include "rclcpp/rclcpp.hpp"
#include "ros2_cpp_learning/srv/odd_event_check.hpp"

typedef ros2_cpp_learning::srv::OddEventCheck OddEventCheckSrv;

class OddEventCheckServiceNode : public rclcpp::Node {

    public:
        OddEventCheckServiceNode() : Node("odd_event_check_service_node")
        {
            service_server_ = this->create_service<OddEventCheckSrv>(
                "odd_event_check",
                std::bind(&OddEventCheckServiceNode::check_num_odd_event, this,
                std::placeholders::_1, std::placeholders::_2
                )
            );
        }
    private: 
        void check_num_odd_event(const OddEventCheckSrv::Request::SharedPtr request,
        OddEventCheckSrv::Response::SharedPtr response){

            bool remainder = request->number % 2;
            response->decision = remainder ? "Odd" : "Even"; 

        }
        rclcpp::Service<OddEventCheckSrv>::SharedPtr service_server_;
};



int main(int argc, char * argv[]){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OddEventCheckServiceNode>());
    return 0;
}