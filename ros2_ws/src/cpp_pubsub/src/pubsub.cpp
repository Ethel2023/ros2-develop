#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node {
public:
    PublisherNode() : Node("publisher_node") {
        pub_ = this->create_publisher<std_msgs::msg::String>("my_topic", 10);
        timer_ = this->create_wall_timer(1s, [this]() {
            auto msg = std_msgs::msg::String();
            msg.data = "Hello ROS2, this is simple!";
            pub_->publish(msg);
            RCLCPP_INFO(this->get_logger(), "发布: %s", msg.data.c_str());
        });
    }
private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

class SubscriberNode : public rclcpp::Node {
public:
    SubscriberNode() : Node("subscriber_node") {
        sub_ = this->create_subscription<std_msgs::msg::String>(
            "my_topic", 10, [this](const std_msgs::msg::String::SharedPtr msg) {
                RCLCPP_INFO(this->get_logger(), "收到: %s", msg->data.c_str());
            });
    }
private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    
    rclcpp::executors::MultiThreadedExecutor executor;
    auto pub_node = std::make_shared<PublisherNode>();
    auto sub_node = std::make_shared<SubscriberNode>();
    
    executor.add_node(pub_node);
    executor.add_node(sub_node);
    executor.spin(); 
    
    rclcpp::shutdown();
    return 0;
}