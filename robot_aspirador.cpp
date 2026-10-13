#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

class RobotAspirador : public rclcpp::Node {
public:
  RobotAspirador() : Node("robot_aspirador"), obstacle_detected_(false) {
    publisher_ = this->create_publisher<geometry_msgs::msg::TwistStamped>("cmd_vel", 10);
    subscriber_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "scan", 10, std::bind(&RobotAspirador::scan_callback, this, std::placeholders::_1));
    timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&RobotAspirador::timer_callback, this));
    RCLCPP_INFO(this->get_logger(), "Aspirador Iniciado! A limpar a casa...");
  }

private:
  void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
    float min_dist = 100.0;
    for (int i = 0; i <= 30; i++) { 
      if (msg->ranges[i] > 0.01 && msg->ranges[i] < min_dist) min_dist = msg->ranges[i]; 
    }
    for (int i = 330; i < 360; i++) { 
      if (msg->ranges[i] > 0.01 && msg->ranges[i] < min_dist) min_dist = msg->ranges[i]; 
    }
    obstacle_detected_ = (min_dist < 0.6);
  }

  void timer_callback() {
    auto twist_msg = geometry_msgs::msg::TwistStamped();
    twist_msg.header.stamp = this->now();
    twist_msg.header.frame_id = "base_link";
    if (obstacle_detected_) { 
      twist_msg.twist.linear.x = 0.0; 
      twist_msg.twist.angular.z = -0.5; 
    } else { 
      twist_msg.twist.linear.x = 0.25; 
      twist_msg.twist.angular.z = 0.0; 
    }
    publisher_->publish(twist_msg);
  }

  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr publisher_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscriber_;
  rclcpp::TimerBase::SharedPtr timer_;
  bool obstacle_detected_;
};

int main(int argc, char * argv[]) { 
  rclcpp::init(argc, argv); 
  rclcpp::spin(std::make_shared<RobotAspirador>()); 
  rclcpp::shutdown(); 
  return 0; 
}
