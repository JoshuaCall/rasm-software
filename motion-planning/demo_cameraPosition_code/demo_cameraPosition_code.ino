// demo key:
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

void setup() {
  Serial.begin(9600);
  md.init();
  md2.init();
  md3.init();
}

void loop() {
  double th1 = shoulderAngle() * PI / 180.0;
  double th2 = elbowAngle() * PI / 180.0;
  double th3 = yawAngle() * PI / 180.0;
  double th4 = pitchAngle() * PI / 180.0;
  double th5 = rollAngle() * PI / 180.0;

  // These formulas come from the output of the matlab file "linearTransformationDHParameters.m"
  Serial.print("x = ");
  Serial.println( (79 * cos(th1 + th2)) / 4 + 16 * cos(th1) - (3 * sin(th1 + th2)*sin(th3)) / 2 + (cos(th4 + th5) * ((13 * sin(th1 + th2)*sin(th3)) / 2 - (13 * cos(th1 + th2)*cos(th3)) / 2)) / 2 + (sin(th4 + th5) * ((sin(th1 + th2)*sin(th3)) / 2 - (cos(th1 + th2)*cos(th3)) / 2)) / 2 - cos(th4) * (sin(th1 + th2)*sin(th3) - cos(th1 + th2)*cos(th3)) + cos(th5) * ((cos(th1 + th2)*sin(th3)) / 2 + (sin(th1 + th2)*cos(th3)) / 2) - sin(th4) * ((9 * sin(th1 + th2)*sin(th3)) / 2 - (9 * cos(th1 + th2)*cos(th3)) / 2) - sin(th5) * ((13 * cos(th1 + th2)*sin(th3)) / 2 + (13 * sin(th1 + th2)*cos(th3)) / 2) + (cos(th4 - th5) * ((13 * sin(th1 + th2)*sin(th3)) / 2 - (13 * cos(th1 + th2)*cos(th3)) / 2)) / 2 - (sin(th4 - th5) * ((sin(th1 + th2)*sin(th3)) / 2 - (cos(th1 + th2)*cos(th3)) / 2)) / 2 + (3 * cos(th1 + th2)*cos(th3)) / 2);
  Serial.print("y = ");
  Serial.println((79 * sin(th1 + th2)) / 4 + 16 * sin(th1) - (13 * sin(th1 + th2 + th3)*cos(th4 + th5)) / 4 - (sin(th1 + th2 + th3)*sin(th4 + th5)) / 4 - (cos(th1 + th2 + th3)*cos(th5)) / 2 + sin(th1 + th2 + th3)*cos(th4) + (13 * cos(th1 + th2 + th3)*sin(th5)) / 2 + (9 * sin(th1 + th2 + th3)*sin(th4)) / 2 - (13 * cos(th4 - th5)*sin(th1 + th2 + th3)) / 4 + (sin(th4 - th5)*sin(th1 + th2 + th3)) / 4 + (3 * cos(th1 + th2)*sin(th3)) / 2 + (3 * sin(th1 + th2)*cos(th3)) / 2);
  Serial.print("z = ");
  Serial.println((9 * cos(th4)) / 2 - sin(th4) + (13 * cos(th5)*sin(th4)) / 2 + (sin(th4)*sin(th5)) / 2);
  Serial.println("");
  Serial.println("");
  delay(500);


  //////// demo code to move the motors goes here
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
}
