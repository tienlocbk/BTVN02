#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <random> // For generating random distances

using namespace std::chrono_literals;

class DistancePublisher : public rclcpp::Node
{
public:
  DistancePublisher() : Node("distance_publisher")
  {
    // 1. Create a publisher on "distance_topic"
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("distance_topic", 10);

    // 2. Create a Timer that triggers every 1 second (1Hz)
    timer_ = this->create_wall_timer(1000ms, std::bind(&DistancePublisher::timerCallback, this));
    
    RCLCPP_INFO(this->get_logger(), "Distance Publisher has started.");
  }

private:
  void timerCallback()
  {
    auto msg = std_msgs::msg::Float32();
    
    // Generate a random number between 0.1 and 1.5
    static std::default_random_engine e;
    static std::uniform_real_distribution<float> dist(0.1, 1.5);
    
    msg.data = dist(e);

    RCLCPP_INFO(this->get_logger(), "Publishing Distance: %.2f m", msg.data);
    publisher_->publish(msg);
  }

  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DistancePublisher>());
  rclcpp::shutdown();
  return 0;
}