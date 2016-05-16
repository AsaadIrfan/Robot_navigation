#include "ros/ros.h"ff

#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <sstream>
#include <std_msgs/String.h>
std_msgs::String a;
std_msgs::Float64 b;
bool data_recieved=false;
void voiceCallback(std_msgs::String s){
  ROS_INFO("command from speech recieved");
  if(s.data=="forward"){
  	a.data="f";
  	b.data=9.0;
  	data_recieved=true;
  }
  else if(s.data=="turn back"){
  	a.data="r";
  	b.data=1.1;
  	data_recieved=true;
  }
  else if(s.data=="turn right"){
  	a.data="l";
  	b.data=0.6;
  	data_recieved=true;
  }
  else if(s.data=="turn left"){
  	a.data="r";
  	b.data=0.6;
  	data_recieved=true;
  }
  else if(s.data=="backward"){
  	a.data="b";
  	b.data=2.0;
  }
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "routine");
  ros::NodeHandle n;  
  ros::Publisher pub_dir = n.advertise<std_msgs::String>("movement_direction", 100);
  ros::Publisher pub_time = n.advertise<std_msgs::Float64>("movement_time", 100);
  ros::Subscriber sub_voice = n.subscribe("firebase_to_ros", 1000, voiceCallback);  
  //ros::Rate loop_rate(10);
  //stop=false;
  while (ros::ok())
  {
  	if(data_recieved){
  		pub_dir.publish(a);
  		pub_time.publish(b);
  		data_recieved=false;
  	}
    ros::spinOnce();
    //loop_rate.sleep();
  }
  return 0;
}