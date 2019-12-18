/*

   Please note that this code
   will use a default baud rate
   of 57600

*/

#include <ros.h>
#include <std_msgs/Float64.h>
#include <common.h>




ros::NodeHandle  nh;

std_msgs::Float64 shoulder_angle;
ros::Publisher shoulder("shoulder", &shoulder_angle);

std_msgs::Float64 elbow_angle;
ros::Publisher elbow("elbow", &elbow_angle);


void setup()
{
  nh.initNode();
  nh.advertise(shoulder);
  nh.advertise(elbow);
}

void loop()
{
  shoulder_angle.data = shoulderAngle();
  shoulder.publish(&shoulder_angle);
  elbow_angle.data = elbowAngle();
  elbow.publish(&elbow_angle);
  nh.spinOnce();
  delay(1000);
}
