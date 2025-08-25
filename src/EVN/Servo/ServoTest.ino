
#include <EVN.h>
#define SERVO_DIR_PORT   1
const float SERVO_CENTER = 133;
const int SERVO_RIGHT  = 160;
const int SERVO_LEFT   = 106;
EVNAlpha board;
EVNServo steeringServo(SERVO_DIR_PORT);
void setup1() {
  steeringServo.begin();
}
void setup()
{
  board.begin(); 
  Serial.begin(9600);
  steeringServo.write(SERVO_CENTER, 50, 210);
}
void loop(){
steeringServo.write(SERVO_RIGHT, 50, 210);
delay(500);
steeringServo.write(SERVO_LEFT, 50, 210);
delay(500);
}
