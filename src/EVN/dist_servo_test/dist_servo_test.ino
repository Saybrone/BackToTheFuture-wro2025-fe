#include <EVN.h>  //include neccessary header for EVN

#define MOTOR_PORT 1	
#define PPR_VALUE 1600 	// Gear ratio * encoder PPR
#define MAX_DPS 480	// Max speed in degrees per second of motor, can be calculated with motor.runPWM(100)
#define ENC_DIR 1 //0 for DIRECT, 1 for REVERSE

#define SERVO_PORT 1
#define DIST_I2C_PORT 16
#define DIST_SIDE 1 //1 if at left, -1 if at right

#define TARGET_DIST 150
#define W_KP 1.0

EVNAlpha board;
EVNMotor motor(1, CUSTOM_MOTOR, DIRECT, ENC_DIR);
EVNServo servo(1);
EVNDistanceSensor ds(DIST_I2C_PORT);

void setup() {
  board.begin();
  Serial.begin(9600);
  ds.begin(); 
}

void setup1() {  //calling motor begin on 2nd core improves performance
  servo.begin();
  servo.write(180);
  
  motor.begin();
  motor.setPPR(PPR_VALUE);
  motor.setMaxRPM(MAX_DPS / 6);
  motor.resetPosition();
}

int throttle = 0;
float speed = 0;
int error = 0;

void loop(){
  motor.runSpeed(speed);

  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove whitespace/newlines

    if (command.startsWith("M")) { //if command is to run motor forward
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

  int dist = ds.read();
  Serial.println(dist); //debug
  if(dist < 2048)
    error = TARGET_DIST - dist;
  float command = error * W_KP * DIST_SIDE;
  int angle = constrain(command + 90, 45, 135);
  servo.write(90 + angle);
}