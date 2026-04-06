#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <string>

#include "distance_warning/action/check_distance.hpp"

using CheckDistance = distance_warning::action::CheckDistance;
using GoalHandle = rclcpp_action::ClientGoalHandle<CheckDistance>;

class DistanceActionClient : public rclcpp::Node
{
public:
  DistanceActionClient() : Node("distance_action_client")
  {
    client_ = rclcpp_action::create_client<CheckDistance>(this, "check_distance");
  }

  void sendGoal(float distance)
  {
    if (!client_->wait_for_action_server(std::chrono::seconds(5))) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
      return;
    }

    auto goal_msg = CheckDistance::Goal();
    goal_msg.distance_to_check = distance;
    
    RCLCPP_INFO(this->get_logger(), "Sending goal: check %.2f m", distance);

    auto send_goal_options = rclcpp_action::Client<CheckDistance>::SendGoalOptions();
    
    // Feedback Callback
    send_goal_options.feedback_callback =
      [this](GoalHandle::SharedPtr, const std::shared_ptr<const CheckDistance::Feedback> feedback) {
        RCLCPP_INFO(this->get_logger(), "Feedback [%d/%d]: %s",
                    feedback->step, feedback->total_steps, feedback->feedback_msg.c_str());
      };

    // Result Callback
    send_goal_options.result_callback =
      [this](const GoalHandle::WrappedResult & result) {
        switch (result.code) {
          case rclcpp_action::ResultCode::SUCCEEDED:
            if (result.result->is_safe) {
              RCLCPP_INFO(this->get_logger(), "RESULT: %s", result.result->result_message.c_str());
            } else {
              RCLCPP_WARN(this->get_logger(), "RESULT: %s", result.result->result_message.c_str());
            }
            break;
          case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
            break;
          case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
            break;
          default:
            RCLCPP_ERROR(this->get_logger(), "Unknown result code");
            break;
        }
        // Shutdown node after the result is printed
        rclcpp::shutdown();
      };

    client_->async_send_goal(goal_msg, send_goal_options);
  }

private:
  rclcpp_action::Client<CheckDistance>::SharedPtr client_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  
  // Create node
  auto node = std::make_shared<DistanceActionClient>();
  
  // Use argv if passed, otherwise default to 0.30m
  float distance_to_check = 0.3f;
  if (argc > 1) {
    distance_to_check = std::stof(argv[1]);
  }
  
  node->sendGoal(distance_to_check);
  
  // Spin until shutdown is called in the result_callback
  rclcpp::spin(node);
  
  return 0;
}