#include "DualMC33926MotorShield.h"

#define setRollSpeed(speed) md.setM1Speed(speed)
#define setBaseSpeed(speed) md.setM2Speed(speed)
#define setElbowSpeed(speed) md2.setM1Speed(speed)
#define setShoulderSpeed(speed) md2.setM2Speed(speed)
#define setPitchSpeed(speed) md3.setM1Speed(speed)
#define setYawSpeed(speed) md3.setM2Speed(speed)
#define SerialSend(message) do{Serial.println(message);Serial.flush();}while(0)  //swallow the semi-colon

DualMC33926MotorShield md;
DualMC33926MotorShield md2(41, 44, A2, 42, 45, A3, 40, 43); //M1DIR, M1PWM, M1FB, M2DIR, M2PWM, M2FB, nD2, nSF
DualMC33926MotorShield md3(53, 13, A14, 52, 46, A15, 51, 50);
String serial_input;
const int width_angle = 4;
int roll_speed = 0;
int pitch_speed = 0;
int yaw_speed = 0;
int base_speed = 0;
int y_speed = 0;
int x_speed = 0;
bool elbow_speed_not_necessarily_zero = true;
unsigned long time_at_change_in_elbow_speed = millis();
unsigned long time_since_change_elbow_speed = 0;
unsigned long elbow_delay_millis = 150;
int roll_encoder_pin = A5;
int elbow_encoder_pin = A8;
int pitch_encoder_pin = A6;
int yaw_encoder_pin = A7;
int shoulder_encoder_pin = A4;


void setup()
{
  Serial.begin(9600);
  md.init();
  md2.init();
  md3.init();
}

void loop()
{
  char leading_char = Serial.read();
//  while (leading_char != '^' && leading_char != '#' && leading_char != '$' && leading_char != '&' && leading_char != '*')
//  {
//    leading_char = Serial.read();
//  }
  ///////////// Roll ////////////////////////////
  if (leading_char == '#')
  {
    //Note that this will require a null terminated string!!!!!
    serial_input = Serial.readStringUntil('\0');
    roll_speed = serial_input.toInt();
  }
  int roll_encoder_reading = analogRead(roll_encoder_pin);
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

  //////////// Base //////////////////////////////////
  if (leading_char == '$')
  {
    //Note that this will require a null terminated string!!!!!
    serial_input = Serial.readStringUntil('\0');
    y_speed = serial_input.toInt();
  }
  if (y_speed > 0)
  {
    base_speed = -400;
  }
  else if (y_speed < 0) {
    base_speed = 400;
  }
  else if (y_speed == 0)
  {
    base_speed = 0;
  }

  ////////// Elbow //////////////////////////////////////
  if (leading_char == '^')
  {
    //Note that this will require a null terminated string!!!!!
    serial_input = Serial.readStringUntil('\0');
    x_speed = serial_input.toInt();
  }
    int elbow_encoder_reading = analogRead(elbow_encoder_pin);
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
  

  /////// Pitch ////////////////////////////////////////
  if (leading_char == '&')
  {
    //Note that this will require a null terminated string!!!!!
    serial_input = Serial.readStringUntil('\0');
    pitch_speed = serial_input.toInt();
  }
  int pitch_encoder_reading = analogRead(pitch_encoder_pin);
  //  if (pitch_speed > 7)
  //  {
  //    setYawSpeed(70);
  //  }
  //  else if (pitch_speed < -7)
  //  {
  //    setYawSpeed(-70);
  //  }
  if (pitch_speed > 0) {
    pitch_speed = 150;
  }
  else if (pitch_speed < 0)
  {
    pitch_speed = -50;
  }
  if (pitch_encoder_reading < 90 && pitch_speed > 0)
  {
    pitch_speed = 0;
  }
  else if (pitch_encoder_reading > 150 && pitch_speed < 0)
  {
    pitch_speed = 0;
  }

  /////// Yaw ////////////////////////////////////////
  if (leading_char == '*')
  {
    //Note that this will require a null terminated string!!!!!
    serial_input = Serial.readStringUntil('\0');
    yaw_speed = serial_input.toInt();
  }
  int yaw_encoder_reading = analogRead(yaw_encoder_pin);

  if (yaw_speed > 0) {
    yaw_speed = 50;
  }
  else if (yaw_speed < 0)
  {
    yaw_speed = -50;
  }
  if (yaw_encoder_reading > 100 && yaw_encoder_reading < 700 && yaw_speed > 0)
  {
    yaw_speed = 0;
  }
  else if (yaw_encoder_reading < 900 && yaw_encoder_reading > 200 && yaw_speed < 0)
  {
    yaw_speed = 0;
  }
    setBaseSpeed(base_speed);
    setRollSpeed(roll_speed);
    setPitchSpeed(pitch_speed);
    setYawSpeed(yaw_speed);
    setElbowSpeed(x_speed);
}
