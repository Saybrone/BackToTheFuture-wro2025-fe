#include <EVN.h>  //include neccessary header for EVN

#define MOTOR_PORT 4
#define PPR_VALUE 1600 	// Gear ratio * encoder PPR
#define MAX_DPS 480	// Max speed in degrees per second of motor, can be calculated with motor.runPWM(100)
#define ENC_DIR 1 //0 for DIRECT, 1 for REVERSE

#define SERVO_PORT 1

#define R_DST_PORT 1
#define L_DST_PORT 2
#define FALLBACK_DIST 250
//#define TARGET_DIST 150
#define W_KP 0.2
#define DST_DELAY 5

EVNAlpha board;
EVNMotor motor(MOTOR_PORT, CUSTOM_MOTOR, DIRECT, ENC_DIR);
EVNServo servo(SERVO_PORT);
EVNDistanceSensor ds_L(L_DST_PORT);
EVNDistanceSensor ds_R(R_DST_PORT);

void setup() {
  board.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  
  ds_L.begin(); 
  ds_R.begin(); 
}

void setup1() {  //calling motor begin on 2nd core improves performance
  servo.begin();
  servo.write(180);
  
  motor.begin();
  motor.setPPR(PPR_VALUE);
  motor.setMaxRPM(MAX_DPS / 6);
  motor.resetPosition();
}

int throttle = 60;
float speed = (throttle / 100.0) * MAX_DPS;
int error = 0;

void loop(){
  if(board.buttonRead())
    motor.runSpeed(speed);
  //Serial.println(speed); //debug
  else
   motor.stop();

  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();  //Remove whitespace/newlines

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

  delay(DST_DELAY);
  uint16_t dist_L = ds_L.read();
  delay(DST_DELAY);
  uint16_t dist_R = ds_R.read();
  
  char strBuf[128]; //debug
  sprintf(strBuf, "L:%d, R:%d", dist_L, dist_R);
  Serial.println(strBuf);

  dist_L = (dist_L == 0) ? FALLBACK_DIST : dist_L;
  dist_R = (dist_R == 0) ? FALLBACK_DIST : dist_R ; 

  error = dist_R - dist_L;
  float command = error * W_KP;
  int angle = constrain(command + 90, 40, 140);
  servo.write(90 + angle);

}