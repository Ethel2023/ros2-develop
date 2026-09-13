#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class Publisher : public rclcpp::Node
{
public:
    Publisher(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "我是%s,现在向你对话", name.c_str());
        commander = this->create_publisher<std_msgs::msg::String>("command", 10);
        timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&Publisher::timer_callback, this));
    }

private:
    void timer_callback()
    {
        std_msgs::msg::String message;
        message.data = "Move!";
        RCLCPP_INFO(this->get_logger(), "'%s'", message.data.c_str());
        commander ->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr commander;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Publisher>("publisher");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
