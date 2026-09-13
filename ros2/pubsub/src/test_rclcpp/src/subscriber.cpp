#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class Subscriber : public rclcpp::Node
{
public:
    Subscriber(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "我是%s，随时待命", name.c_str());
        command_subscriber = this->create_subscription<std_msgs::msg::String>("command", 10, std::bind(&Subscriber::topic_callback, this, std::placeholders::_1));
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscriber;
    void topic_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "收到指令: '%s'", msg->data.c_str());
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Subscriber>("subscriber");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
