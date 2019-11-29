int roll_encoder_pin = A5;
int elbow_encoder_pin = A8;
int pitch_encoder_pin = A6;
int yaw_encoder_pin = A7;
int shoulder_encoder_pin = A4;
double degrees_per_step = 360.0/1024.0; //see page 6 of RM22 rotary magnetic modular encoder data sheet
double degreesInCircle = 360;
#define sinDegrees(degrees) sin((degrees)*PI/180.0)
#define cosDegrees(degrees) cos((degrees)*PI/180.0)
double a1 = 16.0; //inches
double a2 = 19.75; //inches

double shoulderAngle()
{
  // This encoder is backwards, so I subtract the reading from 360 degrees so
  // that the right hand rule will still be followed.
  return degreesInCircle - analogRead(shoulder_encoder_pin)*degrees_per_step;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(shoulderAngle());
  Serial.print("x = ");
  Serial.println(a1*cosDegrees(shoulderAngle()));
  Serial.print("y = ");
  Serial.println(a1*sinDegrees(shoulderAngle()));
  delay(500);
}
