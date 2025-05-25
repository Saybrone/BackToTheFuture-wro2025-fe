#include <EVN.h>  //include neccessary header for EVN

#define MOTOR_PORT 1  
#define SERVO_PORT 1
#define PPR_VALUE 1600  // Gear ratio * encoder PPR
#define MAX_DPS 480

EVNAlpha board;
EVNMotor motor(1, CUSTOM_MOTOR, DIRECT, REVERSE);
EVNServo servo(1);

void setup() {
  board.begin();
  Serial.begin(9600); 
}

void setup1() {  //calling motor begin on 2nd core improves performance
  motor.begin();
  servo.begin();

  motor.setPPR(PPR_VALUE);
  motor.setMaxRPM(MAX_DPS / 6);
  motor.resetPosition();
}
int throttle = 0;
float speed = 0;
void loop() {
  motor.runSpeed(speed);
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove whitespace/newlines
    Serial.println(command);

    if (command.startsWith("S")) {  //if command is to turn servo
      int angle = command.substring(1).toInt();
      angle = constrain(angle, 45, 135);  // Ensure safe range
      servo.write(angle + 90);
      
    } else if (command.startsWith("M")) { //if command is to run motor forward
      int throttle = command.substring(1).toInt();  //get motor speed as percentage (0-100)
      throttle = constrain(throttle, 0, 100);
      speed = (throttle / 100.0) * MAX_DPS;

    } else if (command.startsWith("W")) { //if command is to run motor backward
      int throttle = command.substring(1).toInt();
      throttle = constrain(throttle, 0, 100);
      speed = (throttle / -100.0) * MAX_DPS;

    }
    Serial.flush();
  }
}
