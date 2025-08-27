#include <EVN.h>
#include <SoftwareSerial.h>
#include <math.h>

//---Constants and configurations---
#define SERVO_DIR_PORT   1
#define IMU_I2C_PORT     1
#define MOTOR_PORT       2
#define PPR_VALUE        2200
#define MAX_RPM          77
#define ACCEL            7700
#define DECEL            7700
#define MOTOR_KP         0.4
#define MOTOR_KD         0.0048

const float SERVO_CENTER = 133;  // Servo neutral position
const int SERVO_RIGHT  = 160;    // Servo right extreme
const int SERVO_LEFT   = 106;    // Servo left extreme

float gyroBias = 0.0f;           // Gyro bias for calibration
unsigned long lastTime = 0;

const byte rxPin = 1;
const byte txPin = 0;
int timeout = 500;

//---Hardware objects---
EVNAlpha board;
EVNServo steeringServo(SERVO_DIR_PORT);
EVNIMUSensor imu(IMU_I2C_PORT);
EVNMotor motor(MOTOR_PORT, CUSTOM_MOTOR, DIRECT, REVERSE);
SoftwareSerial mySerial(rxPin, txPin);


//---Calibrates gyro bias while vehicle is stationary---
void calibrateGyroBias(uint16_t duration_ms = 200) {
  unsigned long t0 = millis();
  uint16_t n = 0;
  double sum = 0.0;

  while (millis() - t0 < duration_ms) {
    float gz = imu.readGyroZ(); // deg/s
    sum += gz;
    n++;
    delay(4); // ~250 Hz sample
  }

  if (n > 0) gyroBias = (float)(sum / n); // average bias
}

//---Calculates cumulative yaw (heading) based on gyro readings---
float yaw = 0.00f;
float updateYaw() {
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0f;

  lastTime = now;
  float gz = imu.readGyroZ();   // deg/s
  gz -= gyroBias;                // bias correction
  yaw += gz * dt;                // integrate to get yaw in degrees
  return yaw;
}

//---Performs a gyro-based turn in the specified direction---
void Turn(float Turn_Degree, float kp = 6.66, float turn_start_yaw = 0.0, 
          float min_speed = 40, float max_speed = 400, float Near_Degree = 20.0f,
          int servo_right = 160, int servo_left = 115, int servo_min = 50, int servo_max = 210) {
  delay(1000);                    // Wait before starting
  calibrateGyroBias(200);         // Calibrate gyro before turn

  int turnAngle = (Turn_Degree >= 0.0f) ? servo_right : servo_left;
  steeringServo.write(constrain(turnAngle, servo_min, servo_max));

  float diff = updateYaw() - turn_start_yaw;
  float error = 0;

  //---Loop until target yaw is reached---
  while ((Turn_Degree >= 0.0f) ? (Turn_Degree - diff > 0.1) : (Turn_Degree - diff < 0.1)) {
    diff = updateYaw() - turn_start_yaw;
    error = Turn_Degree - diff;
    int spd = abs(error * kp);

    //---Limit motor speed---
    spd = constrain(spd, min_speed, max_speed);
    motor.runSpeed(spd);
  }

  motor.stop();
  steeringServo.write(constrain(SERVO_CENTER, servo_min, servo_max));
  Serial.println(updateYaw());
}

//---Performs a gyro-based backward turn---
void Turn_Back(float Turn_Degree, float kp = 6.66, float turn_start_yaw = 0.0, 
               float min_speed = 40, float max_speed = 400, float Near_Degree = 20.0f,
               int servo_right = 160, int servo_left = 115, int servo_min = 50, int servo_max = 210) {
  delay(1000);
  calibrateGyroBias(200);

  int turnAngle = (Turn_Degree < 0.0f) ? servo_right : servo_left;
  steeringServo.write(constrain(turnAngle, servo_min, servo_max));

  float diff = updateYaw() - turn_start_yaw;
  float error = 0;

  while ((Turn_Degree >= 0.0f) ? (Turn_Degree - diff > 0.1) : (Turn_Degree - diff < 0.1)) {
    diff = updateYaw() - turn_start_yaw;
    error = Turn_Degree - diff;
    int spd = error * kp;
    spd = constrain(spd, min_speed, max_speed);
    motor.runSpeed(-spd); // reverse
  }

  motor.stop();
  steeringServo.write(constrain(SERVO_CENTER, servo_min, servo_max));
  Serial.println(updateYaw());
}

//---Moves vehicle straight for a specified distance in mm---
void Move(float distance_mm, float speed = 600) {
  steeringServo.write(constrain(SERVO_CENTER, 50, 210)); // center steering
  delay(1000);
  calibrateGyroBias(200);

  long start_pos = motor.getPosition();
  float diameter = 43.2; // wheel diameter in mm
  float distance_degree = 360 * distance_mm / (3.1415 * diameter);

  float start_yaw = updateYaw();
  float error = 0;
  long pos = motor.getPosition() - start_pos;

  while (llabs(pos) < distance_degree) {
    error = updateYaw() - start_yaw;
    steeringServo.write(constrain(SERVO_CENTER - error, 50, 210));
    pos = motor.getPosition() - start_pos;
    motor.runSpeed(speed);
  }

  motor.stop();
}

//---Initializes motor and servo---
void setup1() {
  motor.begin();
  steeringServo.begin();
}

//---Main setup---
void setup() {
  board.begin();
  Serial.begin(9600);
  imu.begin();
  imu.setGyroRange(IMU_GYRO_DPS_1000);

  motor.setPPR(PPR_VALUE);
  motor.setMaxRPM(MAX_RPM);
  motor.setAccel(ACCEL);
  motor.setDecel(DECEL);
  motor.setKp(MOTOR_KP);
  motor.setKd(MOTOR_KD);
  motor.resetPosition();

  steeringServo.write(SERVO_CENTER, 50, 210);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);

  lastTime = millis();
}

//---Determines vehicle movement direction based on sensor readings---
int find_direction() {
  Serial.println("<");
  String orange = requestOrangeLine();
  String blue = requestBlueLine();
  String bright = requestMiddleBrightness();
  float bright1 = bright.toFloat();
  Serial.println(">");

  if (orange == "True") return 1;
  if (blue == "True") return 2;
  if (bright1 < 9) return 1;
  return 0;
}

//---Main challenge sequence for autonomous navigation---
void open_challenge() {
  calibrateGyroBias(200);
  timeout = 2000;
  find_direction();
  timeout = 500;

  long start_pos = motor.getPosition();
  float start_yaw = updateYaw();
  float error = 0;
  long pos = 0;
  bool found_line_or_brightness = false;
  int a;

  Serial.println("S");

  //---Drive forward until line or low brightness detected---
  while (true) {
    board.ledWrite(true);
    error = updateYaw() - start_yaw;
    steeringServo.write(constrain(SERVO_CENTER - error, 50, 210));
    pos = motor.getPosition() - start_pos;
    motor.runSpeed(300);

    a = find_direction();
    if (a != 0) found_line_or_brightness = true;
    if (found_line_or_brightness) break;
  }

  steeringServo.write(SERVO_CENTER, 50, 210);

  //---Execute turning and movement based on detected direction---
  if (a == 1) {
    int lap = 1;
    while (lap < 13) {
      error = updateYaw() - start_yaw;
      steeringServo.write(constrain(SERVO_CENTER - error, 50, 210));
      motor.runSpeed(700);
      String bright = requestMiddleBrightness();
      if (bright.toFloat() < 9) {
        motor.stop();
        Turn(90 * lap);
        start_yaw = updateYaw();
        lap++;
      }
    }
    Move(400);
    motor.stop();
  }

  if (a == 2) {
    motor.stop();
    int lap = 1;
    while (lap < 13) {
      error = updateYaw() - start_yaw;
      steeringServo.write(constrain(SERVO_CENTER - error, 50, 210));
      motor.runSpeed(700);
      String bright = requestMiddleBrightness();
      if (bright.toInt() < 9) {
        motor.stop();
        Turn(-90 * lap);
        start_yaw = updateYaw();
        lap++;
      }
    }
    Move(400);
    motor.stop();
  }

  motor.stop();
}

//---main loop---
void loop() {
  open_challenge();
  delay(9999999)
}

//---Reads a full message from UART and returns as string---
char m[100];
char c;
int i;
String readMessage() {
  bool started = false;
  int i = 0;
  unsigned long startTime = millis();

  while (true) {
    updateYaw(); // keep updating yaw
    if (mySerial.available() > 0) {
      char c = mySerial.read();

      if (c == '<') {  // start of message
        started = true;
        i = 0;
      } 
      else if (c == '*' && started) { // end of message
        m[i] = '\0';
        String result = String(m);
        Serial.println(result);
        mySerial.write('0'); // acknowledge
        return result;
      } 
      else if (started && i < sizeof(m) - 1) {
        m[i++] = c;
      }
    }

    if (millis() - startTime > timeout) return ""; // timeout
  }
}

//---Functions to request specific sensor data via UART---
String requestGreenBox() {
  mySerial.write('1');
  return readMessage();
}

String requestRedBox() {
  mySerial.write('2');
  return readMessage();
}

String requestMiddleBrightness() {
  mySerial.write('3');
  String msg = readMessage();
  if (msg == "") msg = "100";
  return msg;
}

String requestOrangeLine() {
  mySerial.write('4');
  String msg = readMessage();
  if (msg == "") msg = "False";
  return msg;
}

String requestBlueLine() {
  mySerial.write('5');
  String msg = readMessage();
  if (msg == "") msg = "False";
  return msg;
}
