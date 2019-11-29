int roll_encoder_pin = A5;
int elbow_encoder_pin = A8;
int pitch_encoder_pin = A6;
int yaw_encoder_pin = A7;
int shoulder_encoder_pin = A4;
double degrees_per_step = 360.0/1024.0; //see page 6 of RM22 rotary magnetic modular encoder data sheet

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(360 - analogRead(shoulder_encoder_pin)*degrees_per_step);

}
