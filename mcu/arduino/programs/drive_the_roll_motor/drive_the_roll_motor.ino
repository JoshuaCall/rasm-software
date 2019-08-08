#include "DualMC33926MotorShield.h"

DualMC33926MotorShield md;
DualMC33926MotorShield md2(41, 44, A2, 42, 45, A3, 40, 43);
char buf[14];
const int width_angle = 4;
int roll_speed = 0;
int y_speed = 0;
int x_speed = 0;
bool elbow_speed_not_necessarily_zero = true;
unsigned long time_at_change_in_elbow_speed = millis();
unsigned long time_since_change_elbow_speed = 0;
unsigned long elbow_delay_millis = 150;




void setup()
{
  Serial.begin(9600);
  md.init();
  md2.init();
}

void loop()
{
  if (Serial.read() == '#')
  {
    Serial.readBytes(buf, width_angle);
    //Note that this will require a null terminated string!!!!!
    //The string required will be of the format "sign" "width_angle - 2 integers" "null"
    roll_speed = atoi(buf);
  }
  int roll_encoder_reading = analogRead(A5);
  if (abs(roll_speed) > 60)
  {
    if (roll_speed > 0) {
      roll_speed = 50;
    }
    else if (roll_speed < 0)
    {
      roll_speed = -50;
    }
  }
  else if (abs(roll_speed) < 30)
  {
    if (roll_speed > 0) {
      roll_speed = 30;
    }
    else if (roll_speed < 0)
    {
      roll_speed = -30;
    }
  }
  if (roll_encoder_reading > 820 && roll_speed > 0)
  {
    roll_speed = 0;
  }
  else if (roll_encoder_reading < 650 && roll_speed < 0)
  {
    roll_speed = 0;
  }
  md.setM1Speed(roll_speed);
  if (Serial.read() == '$')
  {
    Serial.readBytes(buf, width_angle);
    //Note that this will require a null terminated string!!!!!
    //The string required will be of the format "sign" "width_angle - 2 integers" "null"
    y_speed = atoi(buf);
  }
  if (y_speed > 0)
  {
    md.setM2Speed(-400);
  }
  else if (y_speed < 0) {
    md.setM2Speed(400);
  }
  else if (y_speed == 0)
  {
    md.setM2Speed(0);
  }
  if (Serial.read() == '^')
  {
    Serial.readBytes(buf, width_angle);
    //Note that this will require a null terminated string!!!!!
    //The string required will be of the format "sign" "width_angle - 2 integers" "null"
    x_speed = atoi(buf);
  }
  int elbow_encoder_reading = analogRead(A4);
    if (x_speed > 0)
    {
      x_speed = 120;
    }
    if (x_speed < 0)
    {
      x_speed = -90;
    }
  if (elbow_speed_not_necessarily_zero && time_since_change_elbow_speed < elbow_delay_millis)
  {
    time_since_change_elbow_speed = millis() - time_at_change_in_elbow_speed;
  }
  else if (elbow_speed_not_necessarily_zero && time_since_change_elbow_speed >= elbow_delay_millis)
  {
    elbow_speed_not_necessarily_zero = false;
    time_at_change_in_elbow_speed = millis();
    time_since_change_elbow_speed = 0;
  }
  else if (!elbow_speed_not_necessarily_zero && time_since_change_elbow_speed < elbow_delay_millis)
  {
    x_speed = 0;
    time_since_change_elbow_speed = millis() - time_at_change_in_elbow_speed;
  }
  else if (!elbow_speed_not_necessarily_zero && time_since_change_elbow_speed >= elbow_delay_millis)
  {
    elbow_speed_not_necessarily_zero = true;
    time_at_change_in_elbow_speed = millis();
    time_since_change_elbow_speed = 0;
  }
  if (elbow_encoder_reading > 910 && x_speed > 0)
  {
    x_speed = 0;
  }
  else if (elbow_encoder_reading < 400 && x_speed < 0)
  {
    x_speed = 0;
  }
  md2.setM1Speed(x_speed);
}
