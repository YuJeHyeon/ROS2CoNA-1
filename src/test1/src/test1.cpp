//ROS
#include <ros/ros.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "test1");
	ROS_INFO("%s", ros::this_node::getName().c_str());

	ros::NodeHandle nh;
	
	ros::spin();
	return 0;
}