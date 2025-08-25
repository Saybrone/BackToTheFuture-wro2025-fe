
#include <EVN.h>
#define MOTOR_PORT       2
#define PPR_VALUE        2200
#define MAX_RPM          77
#define ACCEL            7700
#define DECEL            7700
#define MOTOR_KP         0.4
#define MOTOR_KD         0.0048

EVNAlpha board;
EVNMotor motor(MOTOR_PORT, CUSTOM_MOTOR, DIRECT, REVERSE);

void setup1() {
  motor.begin();
}

void setup()
{
  board.begin(); 
  Serial.begin(9600);
  motor.setPPR(PPR_VALUE);
  motor.setMaxRPM(MAX_RPM);
  motor.setAccel(ACCEL);
  motor.setDecel(DECEL);
  motor.setKp(MOTOR_KP);
  motor.setKd(MOTOR_KD);
  motor.resetPosition();
}
void loop(){
  motor.runSpeed(1000);
}
