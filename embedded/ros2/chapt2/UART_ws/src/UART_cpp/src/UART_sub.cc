class serial_sub_node : public rclcpp::Node
{
    public:
        serial_sub_node(std::string name) : Node(name)
        {
            serial_Init();
            serial_subscriber_ = this->create_subscription<std_msgs::msg::String>("serial_msg", 10, std::bind(&serial_sub_node::command_callback, this, std::placeholders::_1));
        }
    private:
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr serial_subscriber_;

        void command_callback(const std_msgs::msg::String::SharedPtr msg)
        {
            ros_ser.write(msg->data.c_str());
        }

    void serial_Init()
    {

        /**/

    } 

        serial::Serial ros_ser;
};

int main(int argc, char **argv)
{

    // auto logger = rclcpp::get_logger("my_logger");  

    rclcpp::init(argc,argv);
    auto node = std::make_shared<serial_sub_node>("tree_serial_sub_node");

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;

}
