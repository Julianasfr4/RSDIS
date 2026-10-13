#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

using namespace std::chrono_literals;

class AspiradorPublisher : public rclcpp::Node
{
public:
  AspiradorPublisher() : Node("robot_aspirador_publisher")
    
    publisher_ = this->create_publisher<geometry_msgs::msg::TwistStamped>("cmd_vel", 10);

    auto timer_callback = [this]() -> void {
      auto msg = geometry_msgs::msg::TwistStamped();
      
      // Preenchimento do cabeçalho
      msg.header.stamp = this->now();
      msg.header.frame_id = "base_link";  

      // Define a velocidade (0.2 m/s em frente)
      msg.twist.linear.x = 0.2;
      msg.twist.angular.z = 0.0;

      RCLCPP_INFO(this->get_logger(), "A aspirar: a andar para a frente!");
      
      // Envia o comando para os motores
      this->publisher_->publish(msg);
    };

    timer_ = this->create_wall_timer(1000ms, timer_callback);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AspiradorPublisher>());
  rclcpp::shutdown();
  return 0;
}