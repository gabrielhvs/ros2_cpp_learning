#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "ros2_cpp_learning/action/navigate.hpp"
#include "geometry_msgs/msg/point.hpp"

typedef ros2_cpp_learning::action::Navigate NavigateAction;
typedef rclcpp_action::ClientGoalHandle<NavigateAction> GoalHandle;
using geometry_msgs::msg::Point;


class NavigateActionClientNode : public rclcpp::Node
{
public:
  NavigateActionClientNode() : Node("navigate_action_client_node")
  {
    action_client_ = rclcpp_action::create_client<NavigateAction>(
      this,
      "navigate");

    prompt_user_for_goal();

    // this->timer_ = this->create_wall_timer(
    //   std::chrono::milliseconds(500),
    //   std::bind(&NavigateActionClientNode::send_goal, this));
  }

  // void send_goal()
  

private:
  rclcpp_action::Client<NavigateAction>::SharedPtr action_client_;
  // rclcpp::TimerBase::SharedPtr timer_;

  void prompt_user_for_goal()
  {
    using std::placeholders::_1; using std::placeholders::_2; 

    // this->timer_->cancel();

    // if (!this->action_client_->wait_for_action_server()) {
    //   RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
    //   rclcpp::shutdown();
    // }

    auto goal_msg = NavigateAction::Goal(); 
    // goal_msg.goal_point = Point();
    
    std::cout << "Enter a X-Coordinate to travel to: ";
    std::cin >> goal_msg.goal_point.x ;

    std::cout << "Enter a Y-Coordinate to travel to: ";
    std::cin >> goal_msg.goal_point.y ;

    std::cout << "Enter a Z-Coordinate to travel to: ";
    std::cin >> goal_msg.goal_point.z ;

    this->action_client_->wait_for_action_server();

    // RCLCPP_INFO(this->get_logger(), "Sending goal");
    std::cout << "Sending Goal" << std::endl;

    auto send_goal_options = rclcpp_action::Client<NavigateAction>::SendGoalOptions();
    send_goal_options.goal_response_callback = 
      std::bind(&NavigateActionClientNode::goal_response_callback, this, _1);
      // std::bind(&NavigateActionClientNode::goal_response_callback, this, _1);
    send_goal_options.feedback_callback =
      std::bind(&NavigateActionClientNode::feedback_callback, this, _1, _2);
    send_goal_options.result_callback =
      std::bind(&NavigateActionClientNode::result_callback, this, _1);

    this->action_client_->async_send_goal(goal_msg, send_goal_options);
  }

  void goal_response_callback(GoalHandle::SharedPtr future)
  {
    auto goal_handle = future.get();
    if (!goal_handle) {
      // RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
      std::cout << "Goal was rejected by the server" << std::endl;
    } else {
      // RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
      std::cout << "Goal accepted by server, waiting for result" << std::endl;
    }
  }

  void feedback_callback(
    GoalHandle::SharedPtr future,
    const std::shared_ptr<const NavigateAction::Feedback> feedback)
  {
    (void)future; // Not using right now
    std::cout << "Feedback: " << feedback->distance_to_point << std::endl;
  }

  void result_callback(const GoalHandle::WrappedResult & result)
  {
    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        std::cout << "Time elapsed: " << result.result->elapsed_time << std::endl;
        break;
      case rclcpp_action::ResultCode::ABORTED:
        // RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
         std::cout << "Goal was aborted" << std::endl;
        break;
      case rclcpp_action::ResultCode::CANCELED:
        // RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
        std::cout << "Goal was canceled" << std::endl;
        break;
      default:
        // RCLCPP_ERROR(this->get_logger(), "Unknown result code");
        std::cout << "Unknown result code" << std::endl;
        break;
    }

    rclcpp::shutdown();
  }
};  // class NavigateActionClientNode



int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NavigateActionClientNode>());
  rclcpp::shutdown();
  
  return 0;
}