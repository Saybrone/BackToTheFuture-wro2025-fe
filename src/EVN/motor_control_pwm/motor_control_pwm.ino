#include <EVN.h>

#define MOTOR_PORT 1
#define SERVO_PORT 1

EVNAlpha board;
EVNMotor motor(MOTOR_PORT, CUSTOM_MOTOR);
EVNServo servo(SERVO_PORT);

void setup1() {
  motor.begin();
  servo.begin();
}

void setup() {
  board.begin();
  Serial.begin(9600);       // Start serial communication
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove whitespace/newlines

    if (command.startsWith("S")) {
      int angle = command.substring(1).toInt();
      angle = constrain(angle, 45, 135);  // Ensure safe range
      servo.write(angle + 90);

    } else if (command.startsWith("M")) {
      int speed = command.substring(1).toInt();
      motor.runPWM(speed);

    } else if (command.startsWith("W")) {
      int speed = command.substring(1).toInt();
      motor.runPWM(-speed);
    }
    Serial.flush();
  }
}