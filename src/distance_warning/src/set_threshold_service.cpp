#include <rclcpp/rclcpp.hpp>
#include "distance_warning/srv/set_threshold.hpp"
#include <std_msgs/msg/float32.hpp>
#include <algorithm> // Để dùng std::clamp

using SetThreshold = distance_warning::srv::SetThreshold;

class SetThresholdService : public rclcpp::Node
{
public:
  SetThresholdService() : Node("set_threshold_service")
  {
    this->declare_parameter<double>("threshold", 0.5);

    // TODO: Tạo service server
    // This "saves" the last sent message for any node that joins later.
    auto qos = rclcpp::QoS(1).transient_local();
    threshold_pub_ = this->create_publisher<std_msgs::msg::Float32>("current_threshold", qos);

    // Service này sẽ lắng nghe trên topic '/set_threshold'
    service_ = this->create_service<SetThreshold>(
      "set_threshold",
      std::bind(&SetThresholdService::handleSetThreshold, this,
                std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(this->get_logger(), "Service [set_threshold] is ready.");
  }

private:
  void handleSetThreshold(
    const SetThreshold::Request::SharedPtr request,
    SetThreshold::Response::SharedPtr response)
  {
    double current = this->get_parameter("threshold").as_double();
    double new_threshold = current;

    // TODO: Tăng hoặc giảm new_threshold theo request->increase
    if (request->increase) {
      new_threshold += 0.1;
    } else {
      new_threshold -= 0.1;
    }

    // TODO: Clamp giá trị trong khoảng [0.1, 1.5]
    new_threshold = std::clamp(new_threshold, 0.1, 1.5);

    // TODO: Cập nhật parameter của chính node này
    this->set_parameter(rclcpp::Parameter("threshold", new_threshold));

    // Broadcast to everyone else
    auto msg = std_msgs::msg::Float32();
    msg.data = static_cast<float>(new_threshold);
    threshold_pub_->publish(msg);

    // TODO: Set response->success, new_threshold, message
    response->success = true;
    response->new_threshold = static_cast<float>(new_threshold);
    
    std::string action = request->increase ? "increased" : "decreased";
    response->message = "Threshold " + action + " to " + std::to_string(new_threshold) + " m";

    RCLCPP_INFO(this->get_logger(), "Request handled: %s", response->message.c_str());
  }

  rclcpp::Service<SetThreshold>::SharedPtr service_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr threshold_pub_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SetThresholdService>());
  rclcpp::shutdown();
  return 0;
}