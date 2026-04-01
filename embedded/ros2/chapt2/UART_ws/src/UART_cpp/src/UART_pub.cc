#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "serial/serial.h"

#define BAUDRATE 115200

class tree_node:public rclcpp::Node
{
public:

	tree_node(const std::string &name):Node(name)
	{
		RCLCPP_INFO(this->get_logger(), "This is Tree's Test");

		serial_publisher_ = this->create_publisher<std_msgs::msg::String>("serial_msg", 10);
		timer_ = this->create_wall_timer(std::chrono::milliseconds(1000), std::bind(&tree_node::timer_callback, this));
		serial_Init();
	}

private:

	void timer_callback()
	{
		std_msgs::msg::String message;

        	message.data = "tree_test\r\n";

        	RCLCPP_INFO(this->get_logger(),"Publisher:'%s'",message.data.c_str());

        	// ros_ser.write(message.data.c_str());

        	serial_publisher_->publish(message);

        	size_t n = ros_ser.available();
        	if(n!=0)
        	{
			std_msgs::msg::String msg_s;
			msg_s.data = ros_ser.read(ros_ser.available());
			serial_publisher_->publish(msg_s);
		}
	}
	void serial_Init()
	{


		serial::Timeout to = serial::Timeout::simpleTimeout(1000);
		serial::parity_t pt = serial::parity_t::parity_none;
		serial::bytesize_t bt =  serial::bytesize_t::eightbits;
		serial::flowcontrol_t ft = serial::flowcontrol_t::flowcontrol_none;
		serial::stopbits_t st = serial::stopbits_t::stopbits_one;


		ros_ser.setPort("/dev/ttyS0");
		// ros_ser.setPort("/dev/pts/5"); //TEST
		ros_ser.setBaudrate(BAUDRATE);
		ros_ser.setTimeout(to);
		ros_ser.setParity(pt);
		ros_ser.setBytesize(bt);
		ros_ser.setFlowcontrol(ft);
		ros_ser.setStopbits(st);

		try
		{
			ros_ser.open();

		}
		catch(const std::exception &e)
		{
			RCLCPP_ERROR(this->get_logger(), "Failed to open the serial port.");
			// return -1;
		}

	}

	serial::Serial ros_ser;

	rclcpp::TimerBase::SharedPtr timer_;

	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr serial_publisher_;
};

int main(int argc, char **argv)
{
	/* 初始化rclcpp  */
	rclcpp::init(argc, argv);
	/*产生一个node_01的节点*/
	auto node = std::make_shared<rclcpp::Node>("tree_new_node");
	
	rclcpp::spin(node);
	/* 停止运行 */
	rclcpp::shutdown();
	return 0;
}
