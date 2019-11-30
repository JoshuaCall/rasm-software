int roll_encoder_pin = A5;
int elbow_encoder_pin = A8;
int pitch_encoder_pin = A6;
int yaw_encoder_pin = A7;
int shoulder_encoder_pin = A4;
double degrees_per_step = 360.0/1024.0; //see page 6 of RM22 rotary magnetic modular encoder data sheet
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
  return degreesInCircle - analogRead(shoulder_encoder_pin)*degrees_per_step - shoulderEncoderOffset;
}

double elbowAngle()
{
  // Following the Denavit–Hartenberg parameter system, this angle (theta2) is off by about 172
  // degrees, so I subtract roughly 172 degrees from the reading.
  return analogRead(elbow_encoder_pin)*degrees_per_step - elbowEncoderOffset;
}

double yawAngle()
{
  // Following the denavit-Hartenberg parameter system, this angle (theta3) is off by about 15
  // degrees, so I add roughly 15 degrees to the reading.
  return analogRead(yaw_encoder_pin)*degrees_per_step + yawEncoderOffset;
}

double pitchAngle()
{
  // Following the denavit-Hartenberg parameter system, this angle (theta4) is off by about 44
  // degrees, so I add roughly 44 degrees to the reading.
  return analogRead(pitch_encoder_pin)*degrees_per_step + pitchEncoderOffset;
}

double rollAngle()
{
  // Following the denavit-Hartenberg parameter system, this angle (theta5) is off by about 245
  // degrees, so I subtract roughly 245 degrees from the reading.
  return analogRead(roll_encoder_pin)*degrees_per_step - rollEncoderOffset;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  double th1 = shoulderAngle() * PI/180.0;
  double th2 = elbowAngle() * PI/180.0;
  double th3 = yawAngle() * PI/180.0;
  double th4 = pitchAngle() * PI/180.0;
  double th5 = rollAngle() * PI/180.0;

  // These formulas come from the output of the matlab file "linearTransformationDHParameters.m"
  Serial.print("x = ");
  Serial.println( (79*cos(th1 + th2))/4 + 16*cos(th1) - (3*sin(th1 + th2)*sin(th3))/2 + (cos(th4 + th5)*((13*sin(th1 + th2)*sin(th3))/2 - (13*cos(th1 + th2)*cos(th3))/2))/2 + (sin(th4 + th5)*((sin(th1 + th2)*sin(th3))/2 - (cos(th1 + th2)*cos(th3))/2))/2 - cos(th4)*(sin(th1 + th2)*sin(th3) - cos(th1 + th2)*cos(th3)) + cos(th5)*((cos(th1 + th2)*sin(th3))/2 + (sin(th1 + th2)*cos(th3))/2) - sin(th4)*((9*sin(th1 + th2)*sin(th3))/2 - (9*cos(th1 + th2)*cos(th3))/2) - sin(th5)*((13*cos(th1 + th2)*sin(th3))/2 + (13*sin(th1 + th2)*cos(th3))/2) + (cos(th4 - th5)*((13*sin(th1 + th2)*sin(th3))/2 - (13*cos(th1 + th2)*cos(th3))/2))/2 - (sin(th4 - th5)*((sin(th1 + th2)*sin(th3))/2 - (cos(th1 + th2)*cos(th3))/2))/2 + (3*cos(th1 + th2)*cos(th3))/2);
  Serial.print("y = ");
  Serial.println((79*sin(th1 + th2))/4 + 16*sin(th1) - (13*sin(th1 + th2 + th3)*cos(th4 + th5))/4 - (sin(th1 + th2 + th3)*sin(th4 + th5))/4 - (cos(th1 + th2 + th3)*cos(th5))/2 + sin(th1 + th2 + th3)*cos(th4) + (13*cos(th1 + th2 + th3)*sin(th5))/2 + (9*sin(th1 + th2 + th3)*sin(th4))/2 - (13*cos(th4 - th5)*sin(th1 + th2 + th3))/4 + (sin(th4 - th5)*sin(th1 + th2 + th3))/4 + (3*cos(th1 + th2)*sin(th3))/2 + (3*sin(th1 + th2)*cos(th3))/2);
  Serial.print("z = ");
  Serial.println((9*cos(th4))/2 - sin(th4) + (13*cos(th5)*sin(th4))/2 + (sin(th4)*sin(th5))/2);
  delay(500);
}
