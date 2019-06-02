#include "DualMC33926MotorShield.h"

DualMC33926MotorShield md;
char buf[14];
const int width_angle = 4;


void setup()
{
  Serial.begin(9600);
  md.init();
}

void loop()
{
  if(Serial.read() == '#')
  {
    Serial.readBytes(buf, width_angle);
    //Note that this will require a null terminated string!!!!!
    //The string required will be of the format "sign" "width_angle - 2 integers" "null"
    int speed = atoi(buf);
    md.setM1Speed(speed);
  }
}
