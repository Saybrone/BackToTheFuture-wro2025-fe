/*
Code for controlling DC Motor with Encoder and Servo Motor with EVN Alpha via the Serial USB Terminal.

Circuit:
	Motor on motor port 1
	Servo on servo port 1
	Serial terminal via on-board USB-C port
	
Commands can start with 'M' 'W' or 'S'. 
	'M' is for driving the motor forward.
	'W' is for driving the motor backward.
	'S' is for turning the servo.

The 'M' and 'W' commands are followed by a string of an integer ranging 0-100, representing the motor throttle percentage.
The 'S' command is followed by a string of an integer ranging 45-135 (safe range of the servo in steering assembly), representing the servo heading in degrees.

Example uses:
Drive the motor forward at 75% throttle: "M75"
Drive the motor backward at 20% throttle: "W20"
Stop the motor: "M0" or "W0"
Turn servo to head straight: "S90"
Turn servo to turn left: "S50"


This code is licensed under GPLv3.
SPDX-License-Identifier: GPL-3.0-or-later
Copyright (C) 2025, Mert Ata Makinaci, Tibet Ozkarslioglu, Ayca Nisa Cerci
*/


#include <EVN.h>  //include neccessary header for EVN

#define MOTOR_PORT 1
#define PPR_VALUE 1600 	// Gear ratio * encoder PPR
#define MAX_DPS 380	// Max speed in degrees per second of motor, can be calculated with motor.runPWM(100)
#define ENC_DIR 1 //0 for DIRECT, 1 for REVERSE

#define SERVO_PORT 1	

EVNAlpha board;
EVNMotor motor(MOTOR_PORT, CUSTOM_MOTOR, DIRECT, ENC_DIR);
EVNServo servo(SERVO_PORT);

void setup() {
  board.begin();
  Serial.begin(9600);
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
void loop() {
  Serial.println(speed);
  motor.runSpeed(speed);
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove whitespace/newlines

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
