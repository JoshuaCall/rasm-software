int roll_encoder_pin = A5;
int elbow_encoder_pin = A8;
int pitch_encoder_pin = A6;
int yaw_encoder_pin = A7;
int shoulder_encoder_pin = A4;
double degrees_per_step = 360.0/1024.0; //see page 6 of RM22 rotary magnetic modular encoder data sheet
double degreesInCircle = 360;
double elbowEncoderOffset = 171.7; //degrees
#define sinDeg(degrees) sin((degrees)*PI/180.0)
#define cosDeg(degrees) cos((degrees)*PI/180.0)
double a1 = 16.0; //inches
double a2 = 19.75; //inches

double shoulderAngle()
{
  // This encoder is backwards, so I subtract the reading from 360 degrees so
  // that the right hand rule will still be followed.
  return degreesInCircle - analogRead(shoulder_encoder_pin)*degrees_per_step;
}

double elbowAngle()
{
  // Following the Denavit–Hartenberg parameter system, this angle (theta2) is off by about 172
  // degrees, so I add roughly 172 degrees from the reading.
  return analogRead(elbow_encoder_pin)*degrees_per_step - elbowEncoderOffset;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  double theta1 = shoulderAngle();
  double theta2 = elbowAngle();

  // This math uses the result of the linear transform T1*T2*[a2, 0, 0, 1] using the DH parameter method
  Serial.print("x = ");
  Serial.println((cosDeg(theta1)*cosDeg(theta2)-sinDeg(theta1)*sinDeg(theta2))*a2 + a1*cosDeg(theta1));
  Serial.print("y = ");
  Serial.println((sinDeg(theta1)*cosDeg(theta2)+cosDeg(theta1)*sinDeg(theta2))*a2 + a1*sinDeg(theta1));
  delay(500);
}
