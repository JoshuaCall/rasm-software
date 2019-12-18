#pragma once


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
int shoulder_speed = 0;
int elbow_speed = 0;
int y_speed = 0;
int x_speed = 0;
bool elbow_speed_not_necessarily_zero = true;
unsigned long time_at_change_in_elbow_speed = millis();
unsigned long time_since_change_elbow_speed = 0;
unsigned long elbow_delay_millis = 75;
int roll_encoder_pin = A5;
int elbow_encoder_pin = A8;
int pitch_encoder_pin = A6;
int yaw_encoder_pin = A7;
int shoulder_encoder_pin = A4;
double degrees_per_step = 360.0 / 1024.0; //see page 6 of RM22 rotary magnetic modular encoder data sheet

double degreesInCircle = 360;
double shoulderEncoderOffset = 273.16; //degrees
double elbowEncoderOffset = 171.7; //degrees
double yawEncoderOffset = 15.2; //degrees
double pitchEncoderOffset = 44; //degrees
double rollEncoderOffset = 245.4; //degrees
#define sinDeg(degrees) sin((degrees)*PI/180.0)
#define cosDeg(degrees) cos((degrees)*PI/180.0)
double a1 = 16.0; //inches
double a2 = 19.75; //inches

double shoulderAngle()
{
  // This encoder is backwards, so I subtract the reading from 360 degrees so
  // that the right hand rule will still be followed. Also adjust by an offset of 273.16 degrees
  // (this offset is so that the shoulder will conveniently be at a reading of zero when the
  // arm is stretched out oppposite from the spline/battery, and not necessary for the DH parameters).
  return degreesInCircle - analogRead(shoulder_encoder_pin) * degrees_per_step - shoulderEncoderOffset;
}

double elbowAngle()
{
  // Following the Denavit–Hartenberg parameter system, this angle (theta2) is off by about 172
  // degrees, so I subtract roughly 172 degrees from the reading.
  return analogRead(elbow_encoder_pin) * degrees_per_step - elbowEncoderOffset;
}

double yawAngle()
{
  // Following the denavit-Hartenberg parameter system, this angle (theta3) is off by about 15
  // degrees, so I add roughly 15 degrees to the reading.
  return analogRead(yaw_encoder_pin) * degrees_per_step + yawEncoderOffset;
}

double pitchAngle()
{
  // Following the denavit-Hartenberg parameter system, this angle (theta4) is off by about 44
  // degrees, so I add roughly 44 degrees to the reading.
  return analogRead(pitch_encoder_pin) * degrees_per_step + pitchEncoderOffset;
}

double rollAngle()
{
  // Following the denavit-Hartenberg parameter system, this angle (theta5) is off by about 245
  // degrees, so I subtract roughly 245 degrees from the reading.
  return analogRead(roll_encoder_pin) * degrees_per_step - rollEncoderOffset;
}
