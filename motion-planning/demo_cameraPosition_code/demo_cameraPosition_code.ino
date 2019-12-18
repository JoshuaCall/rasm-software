// demo key:
// yaw ab
// elbow cd
// roll ef
// shoulder gh
// base ij
// pitch kl


#include <common.h>

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
