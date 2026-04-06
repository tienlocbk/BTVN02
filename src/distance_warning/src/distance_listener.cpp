#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>

class DistanceListener : public rclcpp::Node
{
public:
  DistanceListener() : Node("distance_listener")
  {
    // 1. Declare the threshold parameter (Default: 0.5)
    this->declare_parameter<double>("threshold", 0.5);

    // 2. Initialize the Subscriber
    // Syntax: create_subscription<MessageType>(TopicName, QueueSize, CallbackFunction)
    subscription_ = this->create_subscription<std_msgs::msg::Float32>(
      "distance_topic", 
      10, 
      std::bind(&DistanceListener::listenerCallback, this, std::placeholders::_1)
    );
    // Inside DistanceListener constructor
    threshold_subscription_ = this->create_subscription<std_msgs::msg::Float32>(
      "current_threshold", 
      rclcpp::QoS(1).transient_local(), 
      [this](const std_msgs::msg::Float32::SharedPtr msg) {
        this->set_parameter(rclcpp::Parameter("threshold", static_cast<double>(msg->data)));
        RCLCPP_INFO(this->get_logger(), "Syncing local threshold to: %.2f", msg->data);
      }
    );

    RCLCPP_INFO(this->get_logger(), "Distance Listener node has started.");
  }

private:
  void listenerCallback(const std_msgs::msg::Float32::SharedPtr msg)
  {
    double distance = msg->data;
    double threshold = this->get_parameter("threshold").as_double();

    // TODO: In khoảng cách nhận được (Print received distance)
    RCLCPP_INFO(this->get_logger(), "Distance received: %.2f m", distance);

    // TODO: Nếu distance < threshold, in cảnh báo bằng RCLCPP_WARN
    if (distance < threshold) {
      RCLCPP_WARN(this->get_logger(), 
        "Warning: Object too close! (%.2f m < threshold: %.2f m)", 
        distance, threshold);
    }
  }

  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr threshold_subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DistanceListener>());
  rclcpp::shutdown();
  return 0;
}