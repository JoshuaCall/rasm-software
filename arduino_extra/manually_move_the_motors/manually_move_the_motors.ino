// yaw ab
// elbow cd
// roll ef
// shoulder gh
// base ij
// pitch kl

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



void setup()
{
  Serial.begin(9600);
  md.init();
  md2.init();
  md3.init();
}




void loop() {
  if (Serial.available() > 0)
  {
    char test = Serial.read();

    //
    if (test == 'a' || test == 'b') {
      int yaw_encoder_reading = analogRead(yaw_encoder_pin);
      if (test == 'a')
      {
        yaw_speed = 70;
      }
      if (test == 'b')
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
      setYawSpeed(yaw_speed);
      delay(500);
    }

    //
    if (test == 'c' || test == 'd')
    {
      int elbow_encoder_reading = analogRead(elbow_encoder_pin);
      if (test == 'c')
      {
        elbow_speed = 70;
      }
      if (test == 'd')
      {
        elbow_speed = -70;
      }
      if (elbow_encoder_reading > 830 && elbow_speed > 0)
      {
        elbow_speed = 0;
      }
      else if (elbow_encoder_reading < 400 && elbow_speed < 0)
      {
        elbow_speed = 0;
      }
      setElbowSpeed(elbow_speed);
      delay(500);
    }

    //
    if (test == 'e' || test == 'f')
    {
      int roll_encoder_reading = analogRead(roll_encoder_pin);
      if (test == 'e')
      {
        roll_speed = 70;
      }
      if (test == 'f')
      {
        roll_speed = -70;
      }
      if (roll_encoder_reading > 790 && roll_speed > 0)
      {
        roll_speed = 0;
      }
      else if (roll_encoder_reading < 650 && roll_speed < 0)
      {
        roll_speed = 0;
      }
      setRollSpeed(roll_speed);
      delay(100);
    }

    //
    if (test == 'g' || test == 'h')
    {
      int shoulder_encoder_reading = analogRead(shoulder_encoder_pin);
      if (test == 'g')
      {
        shoulder_speed = 70;
      }
      if (test == 'h')
      {
        shoulder_speed = -70;
      }
      if (shoulder_encoder_reading > 500)
      {
        shoulder_speed = 0;
      }
      setShoulderSpeed(shoulder_speed);
      delay(500);
    }

    //
    if (test == 'i')
    {
      setBaseSpeed(400);
      delay(500);
    }
    if (test == 'j')
    {
      setBaseSpeed(-400);
      delay(500);
    }

    //
    if (test == 'k' || test == 'l') {
      int pitch_encoder_reading = analogRead(pitch_encoder_pin);
      if (test == 'k')
      {
        pitch_speed = 130;
      }
      if (test == 'l')
      {
        pitch_speed = -70;
      }
      if (pitch_encoder_reading < 90 && pitch_speed > 0)
      {
        pitch_speed = 0;
      }
      else if (pitch_encoder_reading > 150 && pitch_speed < 0)
      {
        pitch_speed = 0;
      }
      setPitchSpeed(pitch_speed);
      delay(100);
    }


  }

  else
  {
    setYawSpeed(0);
    setElbowSpeed(0);
    setRollSpeed(0);
    setShoulderSpeed(0);
    setBaseSpeed(0);
    setPitchSpeed(0);
  }
Serial.println(analogRead(elbow_encoder_pin));

}
