#include "DualMC33926MotorShield.h"

DualMC33926MotorShield md;
DualMC33926MotorShield md2(41,44,A2,42,45,A3,40,43);
char buf[14];
const int width_angle = 4;
int roll_speed = 0;
int y_speed = 0;



void setup()
{
  Serial.begin(9600);
  md.init();
  md2.init();
}

void loop()
{
  if(Serial.read() == '#')
  {
    Serial.readBytes(buf, width_angle);
    //Note that this will require a null terminated string!!!!!
    //The string required will be of the format "sign" "width_angle - 2 integers" "null"
    roll_speed = atoi(buf);
  }
    int roll_encoder_reading = analogRead(A5);
    if(abs(roll_speed) > 60)
    {
      if(roll_speed > 0){
       roll_speed = 50;
      }
      else if (roll_speed < 0)
      {
        roll_speed = -50;
      }
    }
    else if(abs(roll_speed) < 30)
    {
      if(roll_speed > 0){
       roll_speed = 30;
      }
      else if (roll_speed < 0)
      {
        roll_speed = -30;
      }
    }
    if(roll_encoder_reading > 820 && roll_speed > 0)
    {
      roll_speed = 0;
    }
    else if(roll_encoder_reading < 650 && roll_speed < 0)
    {
      roll_speed = 0;
    }
  if(Serial.read() == '$')
  {
    Serial.readBytes(buf, width_angle);
    //Note that this will require a null terminated string!!!!!
    //The string required will be of the format "sign" "width_angle - 2 integers" "null"
    y_speed = atoi(buf);
  }
    md.setM1Speed(roll_speed);
    if(y_speed > 0)
    {
      md.setM2Speed(-400);
    }
    else if(y_speed < 0){
      md.setM2Speed(400);
    }
    else if(y_speed == 0)
    {
      md.setM2Speed(0);
    }
}
