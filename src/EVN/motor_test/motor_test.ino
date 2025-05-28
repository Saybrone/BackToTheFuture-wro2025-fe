#include <EVN.h>

#define MOTOR_PORT 1
#define PPR_VALUE 1600  // Gear ratio * encoder PPR
#define MAX_DPS 380

EVNAlpha board;
EVNMotor motor(MOTOR_PORT, CUSTOM_MOTOR, DIRECT, REVERSE);

void setup1() {
  motor.begin();
  //motor.setDebug(true);
  motor.setPPR(PPR_VALUE);
  //motor.setMaxRPM(MAX_RPM);
  //motor.resetPosition();
}

void setup() {
  Serial.begin(9600);
  board.begin();
  delay(1000);

  //Serial.println("Starting");
}

void loop() {
  motor.runPWM(100);

  char strBuf[128];
  sprintf(strBuf, "pos:%3.0f, speed:%3.1f", motor.getPosition(), motor.getSpeed());
  Serial.println(strBuf);
  //delay(5);
}
