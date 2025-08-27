
#include <EVN.h>
#include <SoftwareSerial.h>
#include <math.h>
#define SERVO_DIR_PORT   1
#define IMU_I2C_PORT     1
#define MOTOR_PORT       2
#define PPR_VALUE        2200
#define MAX_RPM          77
#define ACCEL            7700
#define DECEL            7700
#define MOTOR_KP         0.4
#define MOTOR_KD         0.0048
const float SERVO_CENTER = 133;
const int SERVO_RIGHT  = 160;
const int SERVO_LEFT   = 106;
float gyroBias = 0.0f;         
unsigned long lastTime = 0;
const byte rxPin = 1;
const byte txPin = 0;
int timeout = 500;


EVNAlpha board;
EVNServo steeringServo(SERVO_DIR_PORT);
EVNIMUSensor imu(IMU_I2C_PORT);
EVNMotor motor(MOTOR_PORT, CUSTOM_MOTOR, DIRECT, REVERSE);
SoftwareSerial mySerial (rxPin, txPin);





void calibrateGyroBias(uint16_t duration_ms = 200) {
  unsigned long t0 = millis();
  uint16_t n = 0;
  double sum = 0.0;
  // araç duruyor ve servo yerleşmiş olmalı
  while (millis() - t0 < duration_ms) {
    float gz = imu.readGyroZ(); // deg/s
    sum += gz;
    n++;
    delay(4); // ~250 Hz örnek
  }
  if (n > 0) gyroBias = (float)(sum / n);
}

float yaw = 0.00f;
float updateYaw() {
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0f;
  lastTime = now;
  float gz = imu.readGyroZ();         // deg/s
  gz -= gyroBias;                      // bias düzeltmesi
  yaw += gz * dt;                      // derece
  return yaw;
}



void Turn(float Turn_Degree,float kp = 6.66,float turn_start_yaw = 0.0, float min_speed = 40,float max_speed = 400,float Near_Degree = 20.0f,int servo_right = 160, int servo_left = 115,int servo_min = 50,int servo_max = 210){
  delay(1000);
  calibrateGyroBias(200);
  float Turn_Degree_first = Turn_Degree - updateYaw();
  int turnAngle = (Turn_Degree_first >= 0.0f) ? servo_right : servo_left;
  float error = 0;

  steeringServo.write(constrain(turnAngle, servo_min, servo_max));
  
  float diff = updateYaw() - turn_start_yaw;
  while((Turn_Degree_first >= 0.0f) ? (Turn_Degree-diff > 0.1) : (Turn_Degree-diff < 0.1)){
    diff = updateYaw() - turn_start_yaw;
    error = Turn_Degree-diff ;
    float remaining = fabsf(Turn_Degree) - fabsf(diff);
    int spd = fabsf(error*kp);
    Serial.println(updateYaw());
    if (spd > max_speed){
      spd = max_speed;
    }
    if (spd < min_speed){
      spd = min_speed;
    }
    
    motor.runSpeed(spd);
  }
  motor.stop();
  steeringServo.write(constrain(SERVO_CENTER, servo_min, servo_max));
  
}
void TurnWithoutCalib(float Turn_Degree,float kp = 6.66,float turn_start_yaw = 0.0, float min_speed = 40,float max_speed = 400,float Near_Degree = 20.0f,int servo_right = 160, int servo_left = 115,int servo_min = 50,int servo_max = 210){
  float Turn_Degree_first = Turn_Degree - updateYaw();
  Serial.println("-----");
  Serial.println(Turn_Degree_first);
  int turnAngle = ((Turn_Degree_first >= 0.0f)) ? servo_right : servo_left;
  float error = 0;

  steeringServo.write(constrain(turnAngle, servo_min, servo_max));
  
  float diff = updateYaw() - turn_start_yaw;
  while((Turn_Degree_first >= 0.0f) ? (Turn_Degree-diff > 0.1) : (Turn_Degree-diff < 0.1)){
    diff = updateYaw() - turn_start_yaw;
    error = Turn_Degree-diff ;
    float remaining = fabsf(Turn_Degree) - fabsf(diff);
    int spd = fabsf(error*kp);
    
    if (spd > max_speed){
      spd = max_speed;
    }
    if (spd < min_speed){
      spd = min_speed;
    }
    
    motor.runSpeed(spd);
    Serial.println(error);
  }
  motor.stop();
  steeringServo.write(constrain(SERVO_CENTER, servo_min, servo_max));
  Serial.println(updateYaw());
}
void Turn_Back(float Turn_Degree,float kp = 6.66,float turn_start_yaw = 0.0, float min_speed = 40,float max_speed = 400,float Near_Degree = 20.0f,int servo_right = 160, int servo_left = 115,int servo_min = 50,int servo_max = 210){
  delay(1000);
  calibrateGyroBias(200);
  float Turn_Degree_first = Turn_Degree - updateYaw();
  int turnAngle = (Turn_Degree_first < 0.0f) ? servo_right : servo_left;
  float error = 0;

  steeringServo.write(constrain(turnAngle, servo_min, servo_max));
  
  float diff = updateYaw() - turn_start_yaw;
  while((Turn_Degree_first >= 0.0f) ? (Turn_Degree-diff > 0.1) : (Turn_Degree-diff < 0.1)){
    diff = updateYaw() - turn_start_yaw;
    error = Turn_Degree-diff ;
    float remaining = fabsf(Turn_Degree) - fabsf(diff);
    int spd = fabsf(error*kp);
    if (spd > max_speed){
      spd = max_speed;
    }
    if (spd < min_speed){
      spd = min_speed;
    }
    motor.runSpeed(-spd);
  }
  motor.stop();
  steeringServo.write(constrain(SERVO_CENTER, servo_min, servo_max));
  Serial.println(updateYaw());
}
void Turn_Back_WithoutCalib(float Turn_Degree,float kp = 6.66,float turn_start_yaw = 0.0, float min_speed = 40,float max_speed = 400,float Near_Degree = 20.0f,int servo_right = 160, int servo_left = 115,int servo_min = 50,int servo_max = 210){
  
  float error = 0;
  float Turn_Degree_first = Turn_Degree - updateYaw();
  int turnAngle = (Turn_Degree_first < 0.0f) ? servo_right : servo_left;
  steeringServo.write(constrain(turnAngle, servo_min, servo_max));

  float diff = updateYaw() - turn_start_yaw;
  while((Turn_Degree_first >= 0.0f) ? (Turn_Degree-diff > 0.1) : (Turn_Degree-diff < 0.1)){
    diff = updateYaw() - turn_start_yaw;
    error = Turn_Degree-diff ;
    float remaining = fabsf(Turn_Degree) - fabsf(diff);
    int spd = fabsf(error*kp);
    if (spd > max_speed){
      spd = max_speed;
    }
    if (spd < min_speed){
      spd = min_speed;
    }
    motor.runSpeed(-spd);
  }
  motor.stop();
  steeringServo.write(constrain(SERVO_CENTER, servo_min, servo_max));
  Serial.println(updateYaw());
}
void Move(float distance_mm,float speed = 600){
  steeringServo.write(constrain((SERVO_CENTER), 50, 210));
  delay(1000);
  calibrateGyroBias(200);
  long start_pos = motor.getPosition();
  float kp = 1;
  float diameter = 43.2;
  float distance_degree = 360*distance_mm/(3.1415*diameter);
  long pos = motor.getPosition()- start_pos;
  float error = 0;
  float start_yaw = updateYaw();
  while (llabs(pos) < distance_degree) {
    Serial.println(motor.getPosition());
    error = updateYaw() - start_yaw;
    steeringServo.write(constrain((SERVO_CENTER-error), 50, 210));
    pos = motor.getPosition() -  start_pos;
    Serial.println(llabs(pos));
    motor.runSpeed(speed);
  }
  motor.stop();
}
void Move_w_c(float distance_mm,float speed = 600){
  steeringServo.write(constrain((SERVO_CENTER), 50, 210));
  long start_pos = motor.getPosition();
  float kp = 1;
  float diameter = 43.2;
  float distance_degree = 360*distance_mm/(3.1415*diameter);
  long pos = motor.getPosition()- start_pos;
  float error = 0;
  float start_yaw = updateYaw();
  while (llabs(pos) < distance_degree) {
    Serial.println(motor.getPosition());
    error = updateYaw() - start_yaw;
    steeringServo.write(constrain((SERVO_CENTER-error), 50, 210));
    pos = motor.getPosition() -  start_pos;
    Serial.println(llabs(pos));
    motor.runSpeed(speed);
  }
  motor.stop();
}
void setup1() {
  motor.begin();
  steeringServo.begin();
}

void setup()
{
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

int find_direction(){
  Serial.println("<");
  String orange = requestOrangeLine(); 
  String blue = requestBlueLine();
  String bright = requestMiddleBrightness();
  float bright1 = bright.toFloat();
  Serial.println(">");
  if (orange == "True"){
    return 1;
  }else{
    if (blue == "True"){
      return 2;
    }else{
      if (bright1 < 12){
        return 1;
      }else{
        return 0;
      }
    }
  }
}

void open_challenge(){
  calibrateGyroBias(200);
  timeout = 2000;
  find_direction();
  timeout = 500;
  long start_pos = motor.getPosition();
  float kp = 1;
  long pos = motor.getPosition()- start_pos;
  float error = 0;
  float start_yaw = updateYaw();
  bool found_line_or_brightness = false;
  int a;
  Serial.println("S");
  while(true){

    board.ledWrite(true);
    board.ledWrite(true); 
    Serial.println(motor.getPosition());
    error = updateYaw() - start_yaw;
    steeringServo.write(constrain((SERVO_CENTER-error), 50, 210));
    pos = motor.getPosition() -  start_pos;
    Serial.println(llabs(pos));
    motor.runSpeed(300);
    a = find_direction();
    if (a != 0){
      found_line_or_brightness = true;
    }
    if (found_line_or_brightness){
      break;
    }
  }
  Serial.println(a);
  steeringServo.write(SERVO_CENTER, 50, 210);
  if (a == 1){
    int lap = 1;
    while(true){
      Serial.println(motor.getPosition());
      error = updateYaw() - start_yaw;
      steeringServo.write(constrain((SERVO_CENTER-error), 50, 210));
      pos = motor.getPosition() -  start_pos;
      Serial.println(llabs(pos));
      motor.runSpeed(700);
      String bright = requestMiddleBrightness();
      float bright1 = bright.toFloat();
      if (bright1 < 12){
        motor.stop();
        Turn(90*lap);
        start_yaw = updateYaw();
        lap +=1;
      }
      if (lap == 13){
        break;
      }
      }
      Move(400);
      motor.stop();
  }
  if (a == 2){
    motor.stop();
    int lap = 1;
    while(true){
      int x = millis();
      Serial.println(motor.getPosition());
      error = updateYaw() - start_yaw;
      steeringServo.write(constrain((SERVO_CENTER-error), 50, 210));
      pos = motor.getPosition() -  start_pos;
      Serial.println(llabs(pos));
      motor.runSpeed(700);
      String bright = requestMiddleBrightness();
      float bright1 = bright.toInt();
      Serial.println(bright1);
      if (bright1 < 12){
        motor.stop();
        Turn(-90*lap);
        start_yaw = updateYaw();
        lap +=1;
            }
      int y = millis();
      Serial.println((x-y));

    if (lap == 13){
      break;
    }
    }
    Move(400);
    motor.stop();
  }
  motor.stop();
}

void Turn_In_Black(int direction) {
  calibrateGyroBias(200);
  timeout = 500;

  float kp = 0.5;
  float error = 0;
  float startYaw = updateYaw();   

  while (true) {
    error = updateYaw() - startYaw;

    steeringServo.write(constrain(SERVO_CENTER - error, 50, 210));
    Serial.print("Yaw error: ");
    Serial.println(error);

    motor.runSpeed(700);

    String brightnessStr = requestMiddleBrightness();
    float brightness = brightnessStr.toInt();
    Serial.print("Brightness: ");
    Serial.println(brightness);

    if (brightness < 5) {
      motor.stop();
      Turn_Back(90 * direction);          
      startYaw = updateYaw();      
      break;
    }
  }
}


int parseAreaErrorList(String data, int areas[], int errors[], int maxSize) {
  int count = 0;
  int startIndex = 0;

  while (count < maxSize) {
    int open = data.indexOf('[', startIndex);
    if (open == -1) break;

    int comma = data.indexOf(',', open);
    if (comma == -1) break;

    int close = data.indexOf(']', comma);
    if (close == -1) break;

    String areaStr = data.substring(open + 1, comma);
    String errorStr = data.substring(comma + 1, close);

    areas[count] = areaStr.toInt();
    errors[count] = errorStr.toInt();
    count++;

    startIndex = close + 1;
  }

  return count;
}


void find_first_obstacle(bool goLeft) {
  String redBox = requestRedBox();
  String greenBox = requestGreenBox();
  if (redBox == "" && greenBox == "") {
    if (goLeft) {
      Turn_In_Black(-1);
    }
    else{
      Turn_In_Black(1);
    }
  }
}

void pass_obs(int directon_degree){
  int startTime = millis();
  String redBox = requestRedBox();
  String greenBox = requestGreenBox();
  int areas_red[10];
  int errors_red[10];
  int areas_green[10];
  int errors_green[10];
  int areas_box[10];
  int errors_box[10];
  int count = parseAreaErrorList(redBox, areas_red, errors_red, 10);
  int count_green = parseAreaErrorList(greenBox, areas_green, errors_green, 10); 
  int count_box;
  bool redtrue_greenfalse; 
  int k= 0;
  if ((count > 0) && (count_green == 0)){
    redtrue_greenfalse = true;
  }
  if ( count == 0 &&(count_green > 0)){
    redtrue_greenfalse = false;
  }
  if ( count > 0 &&(count_green > 0)){
    redtrue_greenfalse = (areas_red[0]>areas_green[0]) ? true : false;
  }
  while(true){
    updateYaw();
    if (redtrue_greenfalse){
      Box = requestRedBox();
    }else{
      Box  = requestGreenBox();   
    }
    count_box = parseAreaErrorList(Box, areas_box, errors_box, 10);
    if (count_box > 1){
      int t = areas_box[0];
      int e = errors_box[0];
      if(t < areas_box[1]){
        areas_box[0] = areas_box[1];
        areas_box[1] = t;
        errors_box[0] = errors_box[1];
        errors_box[1] = e;
      }
    }
    int error_now = errors_box[0];
    if (areas_box[0] > 5000){
      motor.runSpeed(100);
    } else {
      motor.runSpeed(200);
    }
    int move1 = (SERVO_CENTER + (error_now * 0.2));
    if (move1 > SERVO_RIGHT) move1 = SERVO_RIGHT;
    if (move1 < SERVO_LEFT)  move1 = SERVO_LEFT;
    steeringServo.write(constrain(move1, 50, 210));
    if (areas_box[0] > 7000 && count > 0){
      motor.stop();
      k = k +1;
      if (redtrue_greenfalse){
        Turn_Back_WithoutCalib(directon_degree + 50);
        TurnWithoutCalib(directon_degree + 70);
        Move_w_c(50);
        TurnWithoutCalib(directon_degree-10);
      }else{
        Turn_Back_WithoutCalib(directon_degree - 50);
        TurnWithoutCalib(directon_degree - 70);
        Move_w_c(50);
        TurnWithoutCalib(directon_degree+10);  
      }
      redBox = requestRedBox();
      greenBox = requestGreenBox();
      count = parseAreaErrorList(redBox, areas_red, errors_red, 10);
      count_green = parseAreaErrorList(greenBox, areas_green, errors_green, 10);  
      if (count > 0 && count_green == 0){
        redtrue_greenfalse = true;
      }else if(count == 0 && count_green > 0){
        redtrue_greenfalse = false;
      }else if(count > 0 && count_green > 0){
        redtrue_greenfalse = (areas_red[0]>areas_green[0]) ? true : false;
      }
      else{
        break;
      }
      if (k==2){
        break;
      }
      }
    }
    Turn(directon_degree);
    if (directon_degree <= 0){
      Turn_In_Black((directon_degree / 90) - 1);
    } else {
      Turn_In_Black((directon_degree / 90) + 1);
    }

  }


void obstacle_challenge() {
  calibrateGyroBias(200);
  Turn(-10,15);
  Turn_Back_WithoutCalib(-20,15,0.0,80);
  TurnWithoutCalib(-30,15,0.0,80);
  Turn_Back_WithoutCalib(-50,15,0.0,80);
  TurnWithoutCalib(-70,15,0.0,80);
  Turn_Back_WithoutCalib(-90,15,0.0,80);
  Move(40);
  Turn(0);
  find_first_obstacle(true);
  for (int i = 1;i<12;i++){
    pass_obs(-90*i);
  }
  Serial.print("Final Yaw: ");
  Serial.println(updateYaw());

}


void loop() { 
  obstacle_challenge();
    delay(999999);
}


char m[100];
char c;
int i;

String readMessage() {
  bool started = false;
  int i = 0;
  unsigned long startTime = millis();
  while (true) {
    updateYaw();
    if (mySerial.available() > 0) {
      char c = mySerial.read();
      if (c == '<') {          
        started = true;
        i = 0;
      } 
      else if (c == '*' && started) { 
        m[i] = '\0';
        String result = String(m);
        Serial.println(result); 
        Serial.println(millis() - startTime);
        return result;
      } 
      else if (started && i < sizeof(m) - 1) {
        m[i++] = c;
      }
    }

    if (millis() - startTime > timeout) {
      return "";
    }
  }
}
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
  int z = millis();
  String msg = readMessage();
  if  (msg == ""){
    msg = "100";
  }
  return msg;
}
String requestOrangeLine() {
  mySerial.write('4');
  String msg = readMessage();
  if  (msg == ""){
    msg = "False";
  }
  return msg;
}
String requestBlueLine() {
  mySerial.write('5');
  String msg = readMessage();
  if  (msg == ""){
    msg = "False";
  }
  return msg;
}
