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
    int roll_encoder_reading = analogRead(A5);
    if(roll_encoder_reading > 820 && speed > 0)
    {
      speed = 0;
    }
    else if(roll_encoder_reading < 650 && speed < 0)
    {
      speed = 0;
    }
    if(abs(speed) > 60)
    {
      if(speed > 0){
       speed = 50;
      }
      else if (speed < 0)
      {
        speed = -50;
      }
    }
    else if(abs(speed) < 30)
    {
      if(speed > 0){
       speed = 30;
      }
      else if (speed < 0)
      {
        speed = -30;
      }
    }
    md.setM1Speed(speed);
  }
}
