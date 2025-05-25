#include <EVN.h>

#define MOTOR_PORT 1
#define PPR_VALUE 480            // Gear ratio × encoder PPR
#define MAX_RPM 1300

EVNAlpha board;
EVNMotor motor(MOTOR_PORT, CUSTOM_MOTOR, DIRECT, DIRECT);

void setup1() {
    motor.begin();
}

void setup() {
  Serial.begin(9600);
  board.begin();
  delay(1000);

  //motor.setDebug(true);
  motor.setPPR(PPR_VALUE);
  motor.setMaxRPM(MAX_RPM);
  motor.resetPosition();


  Serial.println("Starting");

    
}

void loop() {
  motor.runPWM(100);

  char strBuf[128];
  sprintf(strBuf, "pos:%3.0f, speed:%3.1f, ", motor.getPosition(), motor.getSpeed());
  Serial.println(strBuf);
  //delay(5);
}
