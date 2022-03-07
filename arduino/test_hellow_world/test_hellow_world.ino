/*
  Reference : http://wiki.ros.org/ja/rosserial_arduino/Tutorials/Hello%20World
*/


#undef ESP32
#include <ros.h> //USB serial mode
#define ESP32
#include <std_msgs/String.h>

//ros setting
ros::NodeHandle nh;

//message
std_msgs::String str_msg;
ros::Publisher pub("chatter", &str_msg);
char hello[13] = "hello world!";

void setup() {
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(pub);
}

void loop() {
  //publish message
  str_msg.data = hello;
  pub.publish( &hello );
  
  nh.spinOnce();
  delay(1000);
}
