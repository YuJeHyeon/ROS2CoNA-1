#include "ros/ros.h"
#include <iostream>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

ros::Publisher robot_pub_;
float linear_vel = 0.0f;
float angular_vel = 0.0f;

void JoyWingCallback(const sensor_msgs::Joy::ConstPtr &joy)
{
    float axes_hori_left = joy->axes[0];
    float axes_verti_left = joy->axes[1];
    int buttons_left_down = joy->buttons[6];
    bool check_moving = false;
    if(buttons_left_down)
        check_moving = true;
    if(check_moving)
    {
        linear_vel = axes_verti_left;
        angular_vel = axes_hori_left;
    }
    else
    {
        linear_vel = 0.0f;
        angular_vel = 0.0f;
    }


}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "joywing_node");
  ros::NodeHandle n;
  ros::Subscriber joy_sub_;
  
  robot_pub_ = n.advertise<geometry_msgs::Twist>("RosAria/cmd_vel", 10);
  joy_sub_ = n.subscribe("/joy", 10, JoyWingCallback);

  ros::Rate loop_rate(10);
  while(ros::ok())
  {

    geometry_msgs::Twist vel_pub;
	//linear
    vel_pub.linear.x = linear_vel * 0.5;   // +: front, -: rear
    vel_pub.linear.y = 0.0; 		
    vel_pub.linear.z = 0.0;
	//rotation 		
    vel_pub.angular.x = 0.0; 		
    vel_pub.angular.y = 0.0; 		
    vel_pub.angular.z = angular_vel * 0.5; 	// +: left, -: right
	
    //printf("linear_x: %f, angular_z: %f\n", vel_pub.linear.x, vel_pub.angular.z);

    robot_pub_.publish(vel_pub);
    
    ros::spinOnce();
    loop_rate.sleep();
  }  

  return 0;
}
