#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <thread>
#include <vector>
#include <string>

#include "distance_warning/action/check_distance.hpp"

using CheckDistance = distance_warning::action::CheckDistance;
using GoalHandle = rclcpp_action::ServerGoalHandle<CheckDistance>;

class DistanceActionServer : public rclcpp::Node
{
public:
  DistanceActionServer() : Node("distance_action_server")
  {
    this->declare_parameter<double>("threshold", 0.5);

    // Initialize the action server
    action_server_ = rclcpp_action::create_server<CheckDistance>(
      this, 
      "check_distance",
      std::bind(&DistanceActionServer::handleGoal, this, std::placeholders::_1, std::placeholders::_2),
      std::bind(&DistanceActionServer::handleCancel, this, std::placeholders::_1),
      std::bind(&DistanceActionServer::handleAccepted, this, std::placeholders::_1)
    );
    
    RCLCPP_INFO(this->get_logger(), "Action server [check_distance] is ready.");
  }

private:
  rclcpp_action::GoalResponse handleGoal(
    const rclcpp_action::GoalUUID &,
    std::shared_ptr<const CheckDistance::Goal> goal)
  {
    RCLCPP_INFO(this->get_logger(), "Received goal: check %.2f m", goal->distance_to_check);
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse handleCancel(const std::shared_ptr<GoalHandle>)
  {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void handleAccepted(const std::shared_ptr<GoalHandle> goal_handle)
  {
    // Execute in a detached thread so we don't block the executor
    std::thread{std::bind(&DistanceActionServer::execute, this, goal_handle)}.detach();
  }

  void execute(const std::shared_ptr<GoalHandle> goal_handle)
  {
    float distance = goal_handle->get_goal()->distance_to_check;
    auto feedback = std::make_shared<CheckDistance::Feedback>();
    auto result = std::make_shared<CheckDistance::Result>();
    
    std::vector<std::string> steps = {
      "Receiving distance value...",
      "Fetching threshold parameter...",
      "Comparing values...",
      "Generating result...",
      "Done."
    };

    feedback->total_steps = steps.size();

    // Loop through the 5 steps
    for (size_t i = 0; i < steps.size(); ++i) {
      // Check if client requested cancellation
      if (goal_handle->is_canceling()) {
        result->result_message = "Goal canceled by client.";
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal canceled.");
        return;
      }

      feedback->step = i + 1;
      feedback->feedback_msg = steps[i];
      
      // Publish the feedback
      goal_handle->publish_feedback(feedback);
      
      // Delay for 500ms
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Fetch threshold and compare
    double threshold = this->get_parameter("threshold").as_double();
    result->is_safe = (distance >= threshold);

    // Format the result message
    char buffer[100];
    if (result->is_safe) {
      snprintf(buffer, sizeof(buffer), "SAFE \u2014 %.2f m >= threshold %.2f m", distance, threshold);
    } else {
      snprintf(buffer, sizeof(buffer), "NOT SAFE \u2014 %.2f m < threshold %.2f m", distance, threshold);
    }
    result->result_message = std::string(buffer);

    // Mark goal as succeeded
    if (rclcpp::ok()) {
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal finished successfully.");
    }
  }

  rclcpp_action::Server<CheckDistance>::SharedPtr action_server_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DistanceActionServer>());
  rclcpp::shutdown();
  return 0;
}