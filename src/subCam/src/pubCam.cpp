#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream>

int main(int argc, char **argv)
{
  printf("projec \n");

  ros::init(argc, argv, "pubCam"); // create pubCam Node,// argc,argv -> rosrun packageName cppName (argc, argv) 
  ros::NodeHandle nh;              
  image_transport::ImageTransport it(nh);                               
  image_transport::Publisher pub = it.advertise("camera/image", 1);   //topic name

  cv::VideoCapture cap(0);    // num 0 camera capture

  if (!cap.isOpened())
  {
    printf("can't open!");
    return 1;
  }
  cv::Mat frame;              // cv camera frame Matrix
  sensor_msgs::ImagePtr msg;  

  ros::Rate loop_rate(5);     // 5 times per second while loop
  while (nh.ok())
  {
    cap >> frame;
    cv::Mat camdata = frame.clone();

    if (!camdata.empty())
    {
      msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", camdata).toImageMsg();
      printf("camdata!\n");
      pub.publish(msg);
      cv::waitKey(1);
    }
    else
    {
      printf("can't open!");
    }

    ros::spinOnce();
    loop_rate.sleep();
  }
}
