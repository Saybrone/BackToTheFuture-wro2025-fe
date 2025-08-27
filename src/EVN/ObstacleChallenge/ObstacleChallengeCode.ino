
#include <EVN.h>
#include <SoftwareSerial.h>
#include <math.h>

// --- Pin and Port Definitions ---
#define SERVO_DIR_PORT   1     // Steering servo control port
#define IMU_I2C_PORT     1     // IMU sensor I2C port
#define MOTOR_PORT       2     // Motor control port

// --- Motor Configuration Constants ---
#define PPR_VALUE        2200  // Motor pulses per revolution
#define MAX_RPM          77    // Maximum RPM
#define ACCEL            7700  // Acceleration
#define DECEL            7700  // Deceleration
#define MOTOR_KP         0.4   // Motor proportional gain
#define MOTOR_KD         0.0048 // Motor derivative gain

// --- Steering Servo Limits ---
const float SERVO_CENTER = 133; // Neutral steering position
const int SERVO_RIGHT  = 160;   // Maximum right turn
const int SERVO_LEFT   = 106;   // Maximum left turn

// --- Gyroscope Variables ---
float gyroBias = 0.0f;          // Bias offset for gyro
unsigned long lastTime = 0;      // Last time yaw was updated

// --- Software Serial Pins for Communication ---
const byte rxPin = 1;  // RX pin
const byte txPin = 0;  // TX pin
int timeout = 500;     // Serial communication timeout (ms)

// --- EVN Objects ---
EVNAlpha board;                     // Main EVN Alpha board
EVNServo steeringServo(SERVO_DIR_PORT);  // Steering servo object
EVNIMUSensor imu(IMU_I2C_PORT);    // IMU sensor object
EVNMotor motor(MOTOR_PORT, CUSTOM_MOTOR, DIRECT, REVERSE); // Motor object
SoftwareSerial mySerial (rxPin, txPin); // Software serial for communication

// --- Gyroscope Calibration ---
// Measure the gyro bias while vehicle is stationary
void calibrateGyroBias(uint16_t duration_ms = 200) {
  unsigned long t0 = millis();
  uint16_t n = 0;
  double sum = 0.0;

  while (millis() - t0 < duration_ms) {
    float gz = imu.readGyroZ(); // Read angular velocity (deg/s)
    sum += gz;
    n++;
    delay(4); // Sample at ~250 Hz
  }

  if (n > 0) gyroBias = (float)(sum / n); // Average bias
}

// --- Yaw Angle Update ---
// Integrates gyro data to calculate yaw (rotation around Z-axis)
float yaw = 0.0f;
float updateYaw() {
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0f; // Time delta in seconds
  lastTime = now;
  
  float gz = imu.readGyroZ(); // Read Z-axis gyro
  gz -= gyroBias;             // Apply bias correction
  yaw += gz * dt;             // Integrate angular velocity
  return yaw;
}

// ======================= TURNING FUNCTIONS =======================

// --- Turn the robot a specific angle with gyro calibration ---
// Turn_Degree: Target turn in degrees (+right, -left)
// kp: Proportional gain for speed control
// turn_start_yaw: Reference yaw angle before starting
// min_speed, max_speed: Speed limits during turn
// servo_right/servo_left: Max servo angles for turning
// servo_min/servo_max: Servo range limits
void Turn(float Turn_Degree, float kp = 6.66, float turn_start_yaw = 0.0,
          float min_speed = 40, float max_speed = 400, float Near_Degree = 20.0f,
          int servo_right = 160, int servo_left = 115, int servo_min = 50, int servo_max = 210) {

  delay(1000);                 // Short delay before turn
  calibrateGyroBias(200);      // Calibrate gyro for accurate turn
  float Turn_Degree_first = Turn_Degree - updateYaw(); // Remaining turn angle
  int turnAngle = (Turn_Degree_first >= 0.0f) ? servo_right : servo_left; // Decide turn direction
  float error = 0;

  // Set steering servo to initial turn angle
  steeringServo.write(constrain(turnAngle, servo_min, servo_max));
  
  float diff = updateYaw() - turn_start_yaw; // Current yaw relative to start
  // Continue turning until target angle reached
  while((Turn_Degree_first >= 0.0f) ? (Turn_Degree - diff > 0.1) : (Turn_Degree - diff < 0.1)){
    diff = updateYaw() - turn_start_yaw;
    error = Turn_Degree - diff;       // Remaining angle error
    float remaining = fabsf(Turn_Degree) - fabsf(diff); // Not used here
    int spd = fabsf(error * kp);       // Speed proportional to error
    Serial.println(updateYaw());       // Print current yaw for debugging

    // Limit speed to min/max
    if (spd > max_speed) spd = max_speed;
    if (spd < min_speed) spd = min_speed;

    motor.runSpeed(spd);               // Move motor during turn
  }

  motor.stop(); // Stop after reaching target
  steeringServo.write(constrain(SERVO_CENTER, servo_min, servo_max)); // Reset steering
}

// --- Turn the robot without gyro calibration ---
// Useful when calibration was already done
void TurnWithoutCalib(float Turn_Degree, float kp = 6.66, float turn_start_yaw = 0.0,
                      float min_speed = 40, float max_speed = 400, float Near_Degree = 20.0f,
                      int servo_right = 160, int servo_left = 115, int servo_min = 50, int servo_max = 210) {

  float Turn_Degree_first = Turn_Degree - updateYaw(); // Remaining turn
  Serial.println("-----");
  Serial.println(Turn_Degree_first);

  int turnAngle = (Turn_Degree_first >= 0.0f) ? servo_right : servo_left;
  float error = 0;

  steeringServo.write(constrain(turnAngle, servo_min, servo_max)); // Initial turn

  float diff = updateYaw() - turn_start_yaw;
  // Loop until target turn reached
  while((Turn_Degree_first >= 0.0f) ? (Turn_Degree - diff > 0.1) : (Turn_Degree - diff < 0.1)){
    diff = updateYaw() - turn_start_yaw;
    error = Turn_Degree - diff;
    float remaining = fabsf(Turn_Degree) - fabsf(diff);
    int spd = fabsf(error * kp);

    if (spd > max_speed) spd = max_speed;
    if (spd < min_speed) spd = min_speed;

    motor.runSpeed(spd);
    Serial.println(error); // Debug: current error
  }

  motor.stop();
  steeringServo.write(constrain(SERVO_CENTER, servo_min, servo_max));
  Serial.println(updateYaw()); // Debug: final yaw
}

// --- Turn backward with gyro calibration ---
// Same logic as Turn(), but motor moves in reverse (-spd)
void Turn_Back(float Turn_Degree, float kp = 6.66, float turn_start_yaw = 0.0,
               float min_speed = 40, float max_speed = 400, float Near_Degree = 20.0f,
               int servo_right = 160, int servo_left = 115, int servo_min = 50, int servo_max = 210) {

  delay(1000);
  calibrateGyroBias(200);
  float Turn_Degree_first = Turn_Degree - updateYaw();
  int turnAngle = (Turn_Degree_first < 0.0f) ? servo_right : servo_left;
  float error = 0;

  steeringServo.write(constrain(turnAngle, servo_min, servo_max));

  float diff = updateYaw() - turn_start_yaw;
  while((Turn_Degree_first >= 0.0f) ? (Turn_Degree - diff > 0.1) : (Turn_Degree - diff < 0.1)){
    diff = updateYaw() - turn_start_yaw;
    error = Turn_Degree - diff;
    int spd = fabsf(error * kp);

    if (spd > max_speed) spd = max_speed;
    if (spd < min_speed) spd = min_speed;

    motor.runSpeed(-spd); // Reverse motor
  }

  motor.stop();
  steeringServo.write(constrain(SERVO_CENTER, servo_min, servo_max));
  Serial.println(updateYaw());
}

// --- Turn backward without calibration ---
// Similar to Turn_Back but skips gyro calibration
void Turn_Back_WithoutCalib(float Turn_Degree, float kp = 6.66, float turn_start_yaw = 0.0,
                            float min_speed = 40, float max_speed = 400, float Near_Degree = 20.0f,
                            int servo_right = 160, int servo_left = 115, int servo_min = 50, int servo_max = 210) {

  float error = 0;
  float Turn_Degree_first = Turn_Degree - updateYaw();
  int turnAngle = (Turn_Degree_first < 0.0f) ? servo_right : servo_left;
  steeringServo.write(constrain(turnAngle, servo_min, servo_max));

  float diff = updateYaw() - turn_start_yaw;
  while((Turn_Degree_first >= 0.0f) ? (Turn_Degree - diff > 0.1) : (Turn_Degree - diff < 0.1)){
    diff = updateYaw() - turn_start_yaw;
    error = Turn_Degree - diff;
    int spd = fabsf(error * kp);

    if (spd > max_speed) spd = max_speed;
    if (spd < min_speed) spd = min_speed;

    motor.runSpeed(-spd);
  }

  motor.stop();
  steeringServo.write(constrain(SERVO_CENTER, servo_min, servo_max));
  Serial.println(updateYaw());
}

// ======================= MOVEMENT FUNCTIONS =======================

// --- Move robot forward a specific distance ---
// distance_mm: Target distance in millimeters
// speed: Motor speed
void Move(float distance_mm, float speed = 600) {
  steeringServo.write(constrain(SERVO_CENTER, 50, 210)); // Keep straight
  delay(1000);
  calibrateGyroBias(200);

  long start_pos = motor.getPosition(); // Get initial motor position
  float diameter = 43.2; // Wheel diameter
  float distance_degree = 360 * distance_mm / (3.1415 * diameter); // Convert mm to degrees
  long pos = motor.getPosition() - start_pos;
  float start_yaw = updateYaw();

  while (llabs(pos) < distance_degree) { // Loop until distance reached
    float error = updateYaw() - start_yaw; // Yaw deviation
    steeringServo.write(constrain(SERVO_CENTER - error, 50, 210)); // Correct steering
    pos = motor.getPosition() - start_pos;
    motor.runSpeed(speed);
    Serial.println(motor.getPosition()); // Debug: current motor position
    Serial.println(llabs(pos));
  }

  motor.stop();
}

// --- Move forward without gyro recalibration ---
// Useful when moving after already calibrated
void Move_w_c(float distance_mm, float speed = 600) {
  steeringServo.write(constrain(SERVO_CENTER, 50, 210));
  long start_pos = motor.getPosition();
  float diameter = 43.2;
  float distance_degree = 360 * distance_mm / (3.1415 * diameter);
  long pos = motor.getPosition() - start_pos;
  float start_yaw = updateYaw();

  while (llabs(pos) < distance_degree) {
    float error = updateYaw() - start_yaw;
    steeringServo.write(constrain(SERVO_CENTER - error, 50, 210));
    pos = motor.getPosition() - start_pos;
    motor.runSpeed(speed);
    Serial.println(motor.getPosition());
    Serial.println(llabs(pos));
  }

  motor.stop();
}

// ======================= SETUP FUNCTIONS =======================

// Initialize motor and servo (simple setup)
void setup1() {
  motor.begin();           // Start motor controller
  steeringServo.begin();   // Start servo controller
}

// Standard Arduino setup function
void setup() {
  board.begin();            // Initialize EVNAlpha board
  Serial.begin(9600);       // Start serial communication for debugging
  imu.begin();              // Initialize IMU (gyro + accelerometer)
  imu.setGyroRange(IMU_GYRO_DPS_1000); // Set gyro range to ±1000 deg/sec

  // Motor configuration
  motor.setPPR(PPR_VALUE); // Encoder pulses per revolution
  motor.setMaxRPM(MAX_RPM); // Max motor speed
  motor.setAccel(ACCEL);    // Acceleration
  motor.setDecel(DECEL);    // Deceleration
  motor.setKp(MOTOR_KP);    // Proportional gain for speed control
  motor.setKd(MOTOR_KD);    // Derivative gain for speed control
  motor.resetPosition();     // Reset encoder position

  // Center the steering servo
  steeringServo.write(SERVO_CENTER, 50, 210);

  // Initialize SoftwareSerial pins
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);

  lastTime = millis();       // Store initial time for yaw calculations
}

// ======================= SENSOR DECISION FUNCTION =======================

// Determines robot direction based on line or brightness sensors
// Returns:
// 1 = Orange line detected
// 2 = Blue line detected
// 0 = No line, brightness determines direction
int find_direction() {
  Serial.println("<");            // Debug: start reading
  String orange = requestOrangeLine(); 
  String blue = requestBlueLine();
  String bright = requestMiddleBrightness();
  float bright1 = bright.toFloat(); // Convert brightness to float
  Serial.println(">");            // Debug: end reading

  if (orange == "True") {         // Orange line detected
    return 1;
  } else if (blue == "True") {    // Blue line detected
    return 2;
  } else {                        // No line detected
    if (bright1 < 12) {           // Dark area, assume orange direction
      return 1;
    } else {                       // Bright area, go straight/no line
      return 0;
    }
  }
}

// ======================= OPEN CHALLENGE FUNCTION =======================

// Navigate open space using sensors
void open_challenge() {
  calibrateGyroBias(200);       // Calibrate gyro for accurate movement
  timeout = 2000;               // Increase serial timeout for sensor reading
  find_direction();              // Initial check for direction
  timeout = 500;                // Reset timeout

  long start_pos = motor.getPosition(); // Save initial motor position
  float kp = 1;
  long pos = motor.getPosition() - start_pos;
  float error = 0;
  float start_yaw = updateYaw();       // Reference yaw angle
  bool found_line_or_brightness = false;
  int a;
  Serial.println("S");                 // Debug: start signal
  // Move forward until line or brightness is detected
  while(true) {
    board.ledWrite(true);               // Turn on board LED
    Serial.println(motor.getPosition());
    
    error = updateYaw() - start_yaw;   // Compute yaw deviation
    steeringServo.write(constrain(SERVO_CENTER - error, 50, 210)); // Correct steering
    
    pos = motor.getPosition() - start_pos;
    Serial.println(llabs(pos));         // Debug: distance traveled
    motor.runSpeed(300);               // Move forward slowly
    a = find_direction();               // Check sensors
    if (a != 0) {
      found_line_or_brightness = true; // Line or brightness detected
    }
    if (found_line_or_brightness) break;
  }

  Serial.println(a);                     // Debug: which line detected
  steeringServo.write(SERVO_CENTER, 50, 210); // Center steering

  // If orange line detected, follow path logic
  if (a == 1) {
    int lap = 1;
    while(true) {
      Serial.println(motor.getPosition());
      error = updateYaw() - start_yaw;
      steeringServo.write(constrain(SERVO_CENTER - error, 50, 210));
      pos = motor.getPosition() - start_pos;
      Serial.println(llabs(pos));
      motor.runSpeed(700);              // Move faster

      String bright = requestMiddleBrightness();
      float bright1 = bright.toFloat();
      if (bright1 < 12) {               // Dark patch detected
        motor.stop();
        Turn(90 * lap);                 // Turn 90 degrees per lap
        start_yaw = updateYaw();        
        lap += 1;
      }
      if (lap == 13) break;             // Stop after 12 laps
    }
    Move(400);                           // Move forward 400 mm
    motor.stop();
  }
  // If blue line detected, similar logic but turn left (-90 deg)
  if (a == 2) {
    motor.stop();
    int lap = 1;
    while(true) {
      int x = millis();
      Serial.println(motor.getPosition());
      error = updateYaw() - start_yaw;
      steeringServo.write(constrain(SERVO_CENTER - error, 50, 210));
      pos = motor.getPosition() - start_pos;
      Serial.println(llabs(pos));
      motor.runSpeed(700);
      String bright = requestMiddleBrightness();
      float bright1 = bright.toInt();
      Serial.println(bright1);
      if (bright1 < 12) {                // Dark patch detected
        motor.stop();
        Turn(-90 * lap);                 // Turn left
        start_yaw = updateYaw();
        lap += 1;
      }
      int y = millis();
      Serial.println((x - y));          // Debug: loop timing
      if (lap == 13) break;             // Stop after 12 laps
    }
    Move(400);                           // Move forward 400 mm
    motor.stop();
  }
  motor.stop();                           // Stop at end of challenge
}


// ======================= TURN IN BLACK =======================

// This function moves the robot forward until it detects a black line (very low brightness).
// Once detected, it stops and performs a backward turn based on 'direction'.
void Turn_In_Black(int direction) {
  calibrateGyroBias(200); // Calibrate gyro for accurate steering
  timeout = 500;           // Set timeout for sensor readings

  float kp = 0.5;          // Steering correction factor
  float error = 0;
  float startYaw = updateYaw(); // Save initial yaw angle

  while (true) {
    error = updateYaw() - startYaw;                      // Calculate yaw deviation
    steeringServo.write(constrain(SERVO_CENTER - error, 50, 210)); // Correct steering

    Serial.print("Yaw error: "); Serial.println(error);

    motor.runSpeed(700);                                  // Move forward

    String brightnessStr = requestMiddleBrightness();     // Read middle brightness sensor
    float brightness = brightnessStr.toInt();
    Serial.print("Brightness: "); Serial.println(brightness);

    if (brightness < 5) { // Black line detected
      motor.stop();
      Turn_Back(90 * direction); // Turn backward in the specified direction
      startYaw = updateYaw();
      break;
    }
  }
}

// ======================= PARSE SENSOR DATA =======================

// Parses area and error values from a string like "[area,error]"
// Returns the number of items parsed
int parseAreaErrorList(String data, int areas[], int errors[], int maxSize) {
  int count = 0;
  int startIndex = 0;

  while (count < maxSize) {
    int open = data.indexOf('[', startIndex); if (open == -1) break;
    int comma = data.indexOf(',', open);     if (comma == -1) break;
    int close = data.indexOf(']', comma);    if (close == -1) break;

    // Extract area and error as integers
    areas[count] = data.substring(open + 1, comma).toInt();
    errors[count] = data.substring(comma + 1, close).toInt();
    count++;

    startIndex = close + 1;
  }
  return count;
}

// ======================= FIND FIRST OBSTACLE =======================

// Checks if any red or green box is detected; if none, uses Turn_In_Black
void find_first_obstacle(bool goLeft) {
  String redBox = requestRedBox();
  String greenBox = requestGreenBox();
  if (redBox == "" && greenBox == "") {
    if (goLeft) {
      Turn_In_Black(-1);
    } else {
      Turn_In_Black(1);
    }
  }
}

// ======================= PASS OBSTACLES =======================

// Handles passing obstacles based on sensor input (red/green boxes)
void pass_obs(int directon_degree){
  int startTime = millis();
  
  // Get sensor data
  String redBox = requestRedBox();
  String greenBox = requestGreenBox();
  
  // Arrays for storing parsed area/error values
  int areas_red[10], errors_red[10];
  int areas_green[10], errors_green[10];
  int areas_box[10], errors_box[10];
  
  int count = parseAreaErrorList(redBox, areas_red, errors_red, 10);
  int count_green = parseAreaErrorList(greenBox, areas_green, errors_green, 10); 
  int count_box;
  bool redtrue_greenfalse; 
  int k = 0;

  // Decide which box type to follow based on detected areas
  if ((count > 0) && (count_green == 0)) redtrue_greenfalse = true;
  else if ((count == 0) && (count_green > 0)) redtrue_greenfalse = false;
  else if ((count > 0) && (count_green > 0)) redtrue_greenfalse = (areas_red[0] > areas_green[0]);

  while(true){
    updateYaw(); // Update yaw for steering

    // Choose which box data to follow
    String Box = redtrue_greenfalse ? requestRedBox() : requestGreenBox();
    count_box = parseAreaErrorList(Box, areas_box, errors_box, 10);

    // Swap largest area to front if more than 1 box
    if (count_box > 1) {
      if (areas_box[0] < areas_box[1]) {
        swap(areas_box[0], areas_box[1]);
        swap(errors_box[0], errors_box[1]);
      }
    }

    int error_now = errors_box[0];

    // Adjust motor speed based on obstacle size
    if (areas_box[0] > 5000) motor.runSpeed(100);
    else motor.runSpeed(200);

    // Adjust steering based on box error
    int move1 = SERVO_CENTER + (error_now * 0.2);
    move1 = constrain(move1, SERVO_LEFT, SERVO_RIGHT);
    steeringServo.write(constrain(move1, 50, 210));

    // If obstacle is large enough, execute avoidance maneuver
    if (areas_box[0] > 7000 && count > 0) {
      motor.stop();
      k++;

      if (redtrue_greenfalse) {
        Turn_Back_WithoutCalib(directon_degree + 50);
        TurnWithoutCalib(directon_degree + 70);
        Move_w_c(50);
        TurnWithoutCalib(directon_degree - 10);
      } else {
        Turn_Back_WithoutCalib(directon_degree - 50);
        TurnWithoutCalib(directon_degree - 70);
        Move_w_c(50);
        TurnWithoutCalib(directon_degree + 10);  
      }

      // Update box data after maneuver
      redBox = requestRedBox();
      greenBox = requestGreenBox();
      count = parseAreaErrorList(redBox, areas_red, errors_red, 10);
      count_green = parseAreaErrorList(greenBox, areas_green, errors_green, 10);  

      // Decide which box to follow next
      if (count > 0 && count_green == 0) redtrue_greenfalse = true;
      else if (count == 0 && count_green > 0) redtrue_greenfalse = false;
      else if (count > 0 && count_green > 0) redtrue_greenfalse = (areas_red[0] > areas_green[0]);
      else break;

      if (k == 2) break; // Stop after 2 maneuvers
    }
  }

  // Final turn to align after passing obstacle
  Turn(directon_degree);
  if (directon_degree <= 0) Turn_In_Black((directon_degree / 90) - 1);
  else Turn_In_Black((directon_degree / 90) + 1);
}



// ======================= OBSTACLE CHALLENGE =======================

// Main routine to navigate the obstacle course
void obstacle_challenge() {
  calibrateGyroBias(200);      // Calibrate gyro for accurate steering

  // Series of corrective turns to align robot at the start
  Turn(-10, 15);
  Turn_Back_WithoutCalib(-20, 15, 0.0, 80);
  TurnWithoutCalib(-30, 15, 0.0, 80);
  Turn_Back_WithoutCalib(-50, 15, 0.0, 80);
  TurnWithoutCalib(-70, 15, 0.0, 80);
  Turn_Back_WithoutCalib(-90, 15, 0.0, 80);

  Move(40);                    // Move forward 40 mm
  Turn(0);                      // Align straight
  find_first_obstacle(true);    // Search for first obstacle, default go left

  // Navigate multiple obstacles
  for (int i = 1; i < 12; i++) {
    pass_obs(-90 * i);          // Pass obstacles using calculated turn angles
  }

  // Print final yaw angle for debugging
  Serial.print("Final Yaw: ");
  Serial.println(updateYaw());
}

// ======================= LOOP =======================

// Arduino loop; executes the challenge once and halts
void loop() { 
  obstacle_challenge();
  delay(999999);                // Prevent repeating (simulate "end of challenge")
}

// ======================= SERIAL COMMUNICATION =======================

// Global buffer for storing serial messages
char m[100];
char c;
int i;

// Reads messages from serial port, delimited by '<' (start) and '*' (end)
String readMessage() {
  bool started = false;
  int i = 0;
  unsigned long startTime = millis();

  while (true) {
    updateYaw();                 // Update yaw for real-time steering correction

    if (mySerial.available() > 0) {
      char c = mySerial.read();

      if (c == '<') {            // Start of message
        started = true;
        i = 0;
      } 
      else if (c == '*' && started) { // End of message
        m[i] = '\0';
        String result = String(m);
        Serial.println(result); 
        Serial.println(millis() - startTime);
        return result;
      } 
      else if (started && i < sizeof(m) - 1) { // Store characters
        m[i++] = c;
      }
    }

    if (millis() - startTime > timeout) { // Timeout
      return "";
    }
  }
}

// Request functions for specific sensor data

// Request green box detection data
String requestGreenBox() {
  mySerial.write('1');          // Send request code
  return readMessage();          // Read response
}

// Request red box detection data
String requestRedBox() {
  mySerial.write('2');
  return readMessage();
}

// Request middle brightness sensor value
String requestMiddleBrightness() {
  mySerial.write('3');
  String msg = readMessage();
  if (msg == "") msg = "100";   // Default if no message
  return msg;
}

// Request detection of orange line
String requestOrangeLine() {
  mySerial.write('4');
  String msg = readMessage();
  if (msg == "") msg = "False"; // Default if no message
  return msg;
}

// Request detection of blue line
String requestBlueLine() {
  mySerial.write('5');
  String msg = readMessage();
  if (msg == "") msg = "False"; // Default if no message
  return msg;
}
