#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <sstream>
#include <std_msgs/String.h>
bool stop=true;
float t=3.0;
geometry_msgs::Twist velocity;
void timerCallback(const ros::TimerEvent&){
  ROS_INFO("timer ended");
  stop=true;
}
void callback(std_msgs::Float64 val){
  ROS_INFO("time recieved");
  t=val.data;
  stop=false;
  ROS_INFO("%f",t);
}
void dirCallback(std_msgs::String s){
  ROS_INFO("direction recieved");
  if(s.data=="f"){
    velocity.linear.x=0.5;
    velocity.angular.z=0;
  }
  else if(s.data=="r"){
    velocity.linear.x=0;
    velocity.angular.z=1;
  }
  else if(s.data=="l"){
    velocity.linear.x=0;
    velocity.angular.z=-1;
  }
  else if(s.data=="b"){
    velocity.linear.x=-0.5;
    velocity.angular.z=0;
  }
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "movement");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("movement_time", 1000, callback);
  ros::Subscriber sub_dir = n.subscribe("movement_direction", 1000, dirCallback);  
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 100);
  //ros::Rate loop_rate(10);
  //stop=false;
  while (ros::ok())
  {
    ros::Timer timer=n.createTimer(ros::Duration(t),timerCallback);
    //ROS_INFO("asdf");
    while(!stop){
      ROS_INFO("publishing velocity");
      pub.publish(velocity);
      ros::spinOnce();
      //stop=true;
    }
    ros::spinOnce();
    //loop_rate.sleep();
  }
  return 0;
}