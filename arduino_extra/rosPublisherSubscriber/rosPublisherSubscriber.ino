/*

   Please note that this code
   will use a default baud rate
   of 57600

*/

#include <ros.h>
#include <std_msgs/Float64.h>

ros::NodeHandle  nh;

std_msgs::Float64 float_msg;
ros::Publisher chatter("chatter", &float_msg);


void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
  float_msg.data = 100.0;
  chatter.publish( &float_msg );
  nh.spinOnce();
  delay(1000);
}
