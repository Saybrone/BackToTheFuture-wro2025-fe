[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](/LICENSE)

# Team BACK TO THE FUTURE - WRO® 2025 Future Engineers

<table border="0">
  <tr border="0">
    <td  border="0" colspan="2">
      <img src="t-photos/logo/Banner.png" alt="Banner" width="100%">
    </td>
  </tr>
  <tr border="0">
    <td width="70%"  border="0">
      <img src="t-photos/TeamOfficial.jpg" alt="Official Photo" width="45%">
      <img src="t-photos/TeamFunny.jpg" alt="Funny Photo" width="45%">
    </td>
    <td valign="top" style="padding-left: 0px;" border="0">
        This repository details team <em>Back To The Future</em>'s building and programming process in the 2025 WRO Future Engineers Competition. 
      We are team <em> Back To The Future</em>, two students who are passionate about technology and robotics. For this competition we built an autonomous vehicle. We worked after school and on weekends. Through this competition, we learned how to work as a team and solve problems related to robotics.
       </p>
        <strong>Team Members:</strong>
      <ul>
        <li>Ayça Nisa Çerçi, 16</li>
        <li>Batuhan Pekcan, 15</li>
      </ul>
      </p>
    </td>
  </tr>
</table>

[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:backtothefuturefeteamofficial@gmail.com)  [![Youtube](https://img.shields.io/badge/Youtube-%23FF0000.svg?style=for-the-badge&logo=Youtube&logoColor=white)](https://www.youtube.com/@BackToTheFuture-WRO)


# Table of Contents
- [Folder Contents](#folder-contents)
- [The Challenge](#the-challenge)
- [Vehicle Overview](#vehicle-overview)
  - [V-Photos](#v-photos)
- [Hardware Components](#hardware-components)
  - [Electronic Components](#electronic-components)
  - [Mobility Management](#mobility-management)
    - [Powertrain](#powertrain)
    - [Steering](#steering)
    - [Chassis](#chassis)
- [Power and Sense Management](#power-and-sense-management)
  - [Li-ion Battery](#li-ion-battery)
  - [IMU Sensor](#imu-sensor)
  - [Camera](#camera)
  - [EVN Alpha Controller](#evn-alpha-controller)
- [Software Components](#software-components)
  - [Setup](#setup)
  - [Gyroscope Handling](#gyroscope-handling)
  - [Turning Functions](#turning-functions)
  - [Forward Movement Functions](#forward-movement-functions)
  - [Sensor Decision Functions](#sensor-decision-functions)
  - [Open Challenge Routine](#open-challenge-routine)
  - [Turn in Black Function](#turn-in-black-function)
  - [Obstacle Handling Functions](#obstacle-handling-functions)
    - [Parse Sensor Data](#parse-sensor-data)
    - [Find First Obstacle](#find-first-obstacle)
    - [Pass Obstacles](#pass-obstacles)
    - [Obstacle Challenge Routine](#obstacle-challenge-routine)
- [Loop](#loop)
- [Serial Communication](#serial-communication)
- [Resources](#resources)
- [License](#license)

# Folder Contents <a class="anchor" id="folder-contents"></a>
* `models` is for the 3D files we used to print our parts
* `other` includes other files which can be used to understand how to prepare the vehicle for the competition. It includes documentations, datasets, hardware specifications, communication protocols,  descriptions etc.
* `schemes` contains schematic diagrams of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `t-photos` contains photos of the team and logos
* `v-photos` contains 6 photos of the vehicle from various angles
* `video` contains the video.md file with the link to our YouTube channel and the respective videos

# The Challenge <a class="anchor" id="the-challenge"></a>

In the **[WRO 2025 Future Engineers – Self-Driving Cars](https://wro-association.org/)** category, teams are tasked with creating a robotic vehicle that can autonomously navigate a changing racetrack. Each round introduces new track layouts, requiring vehicles to adapt in real time.
The competition highlights the full engineering process:

- **Vehicle Design**: Building a functional robot with electromechanical components and advanced steering or motion systems.
- **Obstacle Management**: Applying computer vision, sensor fusion, and motion planning to make real-time decisions.
- **Project Documentation**: Maintaining an engineering journal and sharing designs in a public GitHub repository.

Teams are judged on performance, innovation, reliability, and the clarity of their engineering process, encouraging creativity, teamwork, and STEM skills.

Learn more about the challenge [here](https://wro-association.org/wp-content/uploads/WRO-2025-Future-Engineers-Self-Driving-Cars-General-Rules.pdf).

# Vehicle <a class="anchor" id="Vehicle"></a>
Our robot integrates LEGO components with custom 3D-printed hardware, designed to maximize stability and durability. It features a 3D-printed motor mount and camera holder, integrated with a LEGO-based chassis. For steering, we implemented a simplified Ackermann setup without linkage geometry (reckless steering), allowing the robot to turn easily while keeping the design compact. Our robot is powerized by a [GA12-N20 200RPM](https://www.handsontec.com/dataspecs/GA12-N20.pdf) dc motor and controlled by an [EVNAlpha](https://evn.readthedocs.io/). It uses [OpenMV RT1062](https://openmv.io/products/openmv-cam-rt?srsltid=AfmBOorMjCmNBP1AZA_3V53JQMS-8N7Mg5ljP10ljHe4SLFoCauGWzZN) to locate obstacles, lines and walls. Steering was managed by [GeekServo 2KG Motor](https://kittenbothk-eng.readthedocs.io/en/latest/motors/2kgMotor.html). Also it uses [MPU6500 IC 6 DoF IMU Sensor](https://datasheet.octopart.com/MPU-6500-InvenSense-datasheet-138896167.pdf) to manage certain turns and hold position during movement.



## V-Photos <b class="anchor" id="Vphotos"></a>
| <img src="v-photos/front.jpg" width="40%" /> | <img src="v-photos/back.jpg" width="40%" /> | 
| :--: | :--: | 
| *Front* | *Back* |
| <img src="v-photos/left.jpg" width="40%" /> | <img src="v-photos/right.jpg" width="40%" /> | 
| *Left* | *Right* |
| <img src="v-photos/top.jpg" width="40%" /> | <img src="v-photos/bottom.jpg" width="40%" /> | 
| *Top* | *Bottom* |

<br>

# Hardware Components <a class="anchor" id="Hardware"></a>
This section covers all the parts utilized in the vehicle, such as motors, sensors, controllers, chassis, mechanical systems, and other components.
## Electronic Components
<table border="1" cellpadding="12" cellspacing="0">
  <thead>
    <tr>
      <th>Component</th>
      <th>Description / Link</th>
      <th>Image</th>
      <th>Price</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Motor</td>
      <td><a href="https://www.aliexpress.us/item/3256805071786531.html?gatewayAdapt=glo2usa4itemAdapt">GA12 N20 Encoder DC Mini Micro Metal Gear DC Motor</td>
      <td><img src = "other/motor/pixelcut-export.png" alt= "Motor" width="200"</td>
      <td>$7</td>
    </tr>
    <tr>
      <td>Servo Motor</td>
      <td><a href="https://www.robotshop.com/products/geekservo-motor-2kg-compatible-w-lego">GeekServo (360 degrees)</a></td>
      <td><img src = "other/servo motor/geek.PNG"  alt = "Servo motor" width ="135"</td>
      <td>$10</td>
    </tr>
  <tr>
    <tr>
      <td>Motor Controller and Processor</td>
      <td><a href="https://coresg.tech/product/evn-alpha/">EVN Alpha</a></td>
      <td><img src="other/evn/evn2.png" alt="evn" width="150"></td>
      <td>$168</td>
    </tr>
      <td>IMU</td>
      <td><a href="https://tr.aliexpress.com/item/1005006996048940.html?spm=a2g0o.productlist.main.5.6ef53353cKZzxy&algo_pvid=fd17a8c4-be06-4443-bb16-ca5842e753da&algo_exp_id=fd17a8c4-be06-4443-bb16-ca5842e753da-4&pdp_ext_f=%7B%22order%22%3A%223%22%2C%22eval%22%3A%221%22%7D&pdp_npi=6%40dis%21TRY%2161.03%2150.05%21%21%2110.06%218.25%21%40211b80f717561234906297648ea906%2112000038988133079%21sea%21TR%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A9b91ce8e%3Bm03_new_user%3A-29895&curPageLogUid=WZMpWQdAhpsJ&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006996048940%7C_p_origin_prod%3A">MPU 6500 Gyro Sensor</td>
      <td><img src ="other/IMU/IMU.PNG" alt="IMU" width="150"</td>
      <td>$1.88</td> 
    <tr>
      <td>Battery</td>
      <td><a href="https://www.pilpaketi.com/molicel-inr18650-p28a-2800-mah-35a-li-ion-pil?srsltid=AfmBOoq0NI6NCh02JlGpFI8KTAQyYEYrH5VP3xPdYOHkjVYT9HXYP0vB">Molicel 35A Li-ion battery</td>
      <td><img src="other/battery/Battery.png" alt="battery" width="150"</td>
      <td>$10x2</td>
    </tr>
    </tr>
    <tr>
      <td>Camera</td>
      <td><a href="https://openmv.io/products/openmv-cam-rt?srsltid=AfmBOorMjCmNBP1AZA_3V53JQMS-8N7Mg5ljP10ljHe4SLFoCauGWzZN">OpenMV Cam RT1062</a></td>
      <td><img src= "other/camera/cam.PNG" alt= "Camera" width="143"</td>
      <td>$120</td>
    </tr>
    <tr>
      <td colspan="3"><strong>Total Cost</strong></td>
      <td><strong>$326.88</strong></td>
    </tr>
  </tbody>
</table>

## Mobility Management

Our robot’s mobility depends on the coordination of its powertrain, steering system, and chassis. Together, these components provide stability, control, and efficiency, enabling smooth and reliable movement.

### Powertrain

#### Motor
<table> <tr><td> <img src = "other/motor/pixelcut-export.png" alt="Motor" width = "900" </td><td valign="top" style="padding-left: 15px;"> <b>Specifications:</b><br> Rated Voltage: 6~12V <br> Weight: 10g <br> Revolving Speed: 100RPM @ 6V <br> Load Speed: 80RPM <br> Rated Torque: 2 kg.cm <br> Stall Torque: 16 kg.cm <br><br> This <b>DC Mini Metal Gear Motor</b> is the one we used in our robot. Its <b>light weight</b> and <b>compact size</b> make it suitable for small robotic platforms, while the <b>high torque</b> and <b>low RPM</b> ensure powerful and controlled movement. <br><br> Thanks to its <b>excellent stall characteristics</b>, the motor provides enough force to climb slopes or overcome obstacles, which is highly beneficial for mobile robots. Additionally, the <b>durable metal gears</b> extend the lifetime of the motor, making it reliable for long-term use. <br><br> Another important advantage is that a wheel can be easily mounted on the motor’s output shaft, allowing for simple integration with the robot’s chassis. </td> </tr> </table>
<p style="margin:0;"> Below, we have included the diagram of our motor for clarity. </p> <img src ="schemes/Motor diagram.jpg" alt= "Diagram" width = "700" style="display:block; margin:0 auto;" />
  

### Steering
Our robot uses a **reckless steering** mechanism, a simplified form of Ackermann steering where the wheels are directly turned without complex linkage geometry. This method makes the robot easier to turn and keeps the overall design compact. It is highly effective for lightweight and fast-moving prototypes where simplicity and space efficiency are key.

#### Servo Motor
<table> <tr><td><img src = "other/servo motor/geek.PNG" alt="Servo motor" width = "800" </td> <td valign="top" style="padding-left: 15px;"> <b>Specifications:</b><br> Operating Voltage: 3.3V~6V<br> Rated Voltage: 4.8V<br> Rotational range: 360°<br> Maximum Torque: 1.6kg±0.2kg/cm (4.8V)<br> Maximum Speed: 45rpm (3V)<br> Weight: 20g<br><br> For steering we selected the <b>GeekServo</b>. This motor is compatible with Lego Technic parts and offers a higher speed compared to 9g motors. The output shaft features a Lego Technic axle connector, making it ideal for applications that require a high-power drive. </td> </tr> </table> 
<p style="margin:0;"> <p>Below, we have included the diagram of our servo motor.</p> <img src="other/servo motor/servo.diagram.jpg" alt = "servo diagram" width = "500" display:block; margin:0 auto; width:400px;" />

### Chassis
Our chassis combines LEGO components with custom 3D-printed parts, creating a reliable and durable structure. The chassis provides mounting points for all motors, controllers, and sensors, ensuring stable alignment and easy integration. Below, a schematic of the connections is included for clarity.

## Power and Sense Management
### Li-ion Battery
<table> <tr><td> <img src = "other/battery/Battery.png" alt = "Battery" width = 100 </td><td valign="top" style="padding-left: 15px;"> <b>Specifications:</b><br> Voltage: 3.7V <br>Capacity:2800mAh<br> Diameter: 18mm <br> Length: 65mm <br></td> </tr> </table> 

### IMU
<table> <tr><td> <img src ="other/IMU/IMU.PNG" alt="IMU" width="150" alt = "IMU" width = "300" <td valign="top" style="padding-left: 15px;"> <b>Specifications:</b><br> Gyroscope Range: ±250, ±500, ±1000, ±2000 °/s<br>Accelerometer Range: ±2g, ±4g, ±8g, ±16g<br> Interface : I2C <br>Power Supply: 3.5V  <br> </td> </tr> </table> The MPU-6500 is a 6-axis MotionTracking sensor that combines a 3-axis gyroscope and a 3-axis accelerometer in a compact 3x3x0.9 mm package. This integration allows reliable motion detection and orientation tracking with reduced size and complexity. We selected the MPU-6500 because it provides reliable motion tracking, low power consumption, and small form factor, making it well-suited for our vehicle’s navigation and stability control.

### OpenMV Cam RT1062
<table> <tr> <td><img src="other/camera/cam.PNG" alt = "Camera " width = "800" width:800px; height:auto; display:block; margin:0 auto;" />
 </td> <td valign="top" style="padding-left: 15px;"> <b>Specifications:</b><br> Microcontroller: ARM Cortex M7 (RT1062)<br>Frequency: 600 MHz<br> RAM: 32 MB SDRAM + 1 MB SRAM <br> Flash Memory: 16 MB program/storage flash<br>Camera Resolution: 2592 × 1944 (5 MP) <br> Frame Rate:~40 FPS on QVGA (320 × 240) <br><br> This <b>OpenMV Cam -RT1062</b> is the one we used in our robot. The OpenMV Cam is a small, low-power microcontroller board that we used in our robot to implement machine vision applications. We program the OpenMV Cam in high-level Python scripts (via the MicroPython Operating System) instead of C/C++, which makes it much easier to handle the complex outputs of machine vision algorithms and work with high-level data structures. At the same time, we retain full control over the OpenMV Cam and its I/O pins in Python. This allows our robot to locate obstacles, lines and walls, enabling intelligent, autonomous behaviors. </td> </tr> </table>


### EVN Alpha
<table> <tr> <td><img src="other/evn/evn alpha2.jpg" alt = "evn alpha" width = "1100"  width:800px; height:auto; display:block; margin:0 auto;" />
 </td> <td valign="top" style="padding-left: 15px;"> <b>The EVN ALPHA is a compact robot controller based on the RP2040, housed in a LEGO Technic-compatible shell. It provides 26 I/O channels for controlling brushed DC motors, servos, and connecting UART or I2C peripherals. The board also integrates a 2-cell Lithium-Ion power management system, offering charging, cell balancing, and voltage regulation, making it ideal for safely powering and controlling our robot’s motors and sensors.</td> </tr> </table>
   
## Software Components <a class="anchor" id="Software"></a>
### EVN Alpha Side
#### 1. Setup
- Configures **servo** and **DC motor**.  
- Defines constants (angles, speeds, gyro calibration values).  
- Initializes **UART** (`Serial2`) to communicate with OpenMV.  
- Sets up **IMU (BMI088)** and calibrates **gyro bias**.  

#### 2. Gyroscope Handling
- Reads gyro Z-axis to measure angular velocity.  
- Subtracts bias → integrates over time → produces **yaw angle**.  
- Used to know robot’s heading (rotation in degrees).  
- Every movement command relies on yaw correction to stay accurate.  

#### 3. Turning Functions
- Calculate a **target yaw angle**.  
- Drive motors while comparing current yaw to target.  
- Servo steers left/right, motor power adjusts proportionally.  
- Variants:
  - `Turn()` → normal calibrated turn.  
  - `TurnWithoutCalib()` → faster, skips recalibration.  
  - `Turn_Back()` → reverse turn.  

#### 4. Forward Movement
- `Move(distance)` drives a set distance using encoders.  
- Constantly checks yaw and adjusts steering with servo.  
- Ensures straight driving.  
- `Move_w_c()` skips recalibration.  

#### 5. Camera Communication (UART)
EVN Alpha sends single-byte commands:  
- `1` → detect green box.  
- `2` → detect red box.  
- `3` → check brightness.  
- `4` → detect orange line.  
- `5` → detect blue line.  

Camera replies with formatted data: `<area,error*>` or `<1*>`.  

#### 6. Open Challenge Routine
- Calibrates IMU.  
- Uses camera to detect:  
  - **Orange line → left path**  
  - **Blue line → right path**  
  - **Brightness → walls**  
- Moves forward, checks brightness → if dark → turn 90°.  
- Repeats laps until finished.  

#### 7. Obstacle Challenge Routine
- Searches for **red/green obstacles**.  
- Uses `pass_obs()` to:  
  - Read box area + position.  
  - Adjust steering based on error.  
  - Slow down when close.  
  - Perform bypass maneuver if very close.  

Here is the EVN Alpha control code, responsible for motor control, gyroscope-based stabilization, and coordination with the OpenMV camera
```ino
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

// Standard setup function
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

// Main loop; executes the challenge once and halts
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
```
### OpenMV Camera Side

#### 1. Color Detection
- **Orange / Blue line**:  
  - Detects blobs in bottom ROI.  
  - Returns `True` if blob is large enough.  
- **Red / Green box**:  
  - Detects rectangular blobs.  
  - Filters by size and shape.  
  - Returns `[area, error]` for EVN Alpha.  

#### 2. Brightness Detection
- Reads a central ROI.  
- Computes average brightness.  
- Low brightness → wall detected.  

#### 3. UART Control
- Waits for EVN Alpha command.  
- Runs appropriate detection function.  
- Sends results back wrapped in `<...*>`.  

Example:  
- EVN Alpha sends `1`.  
- Camera detects green box.  
- Camera replies: `<500,20*>` (area=500, error=20px right).  
---
## Robot Construction Guide <a class="anchor" id="robot-construction-guide-"></a>
**Step 1: Assemble the steering system**  
- Print 3D models located in /models
- Mount the GeekServo motor securely onto the chassis using screws or brackets.  
- Connect the steering axle to the servo using a suitable coupling or connector.  
- Ensure the servo mount is firmly fixed so it doesn’t wobble during operation.  
- Install the front steering hubs using a axle to secure them.  
- Make sure the steering arm moves freely and does not collide with the chassis.  

**Step 2: Assemble the powertrain**  
- The motor was mounted securely onto the chassis to ensure stability during operation.
- The GA12-N20 DC motor is placed into the mount and attached firmly (using appropriate fastening components).
- The motor output shaft is connected to an axle and gear mechanism to transmit rotation.
- 
**Step 3: Mount the electronics**
- Attach the Li-ion battery underneath the EVN Alpha.
- Place the EVN Alpha controller onto the chassis and secure it in position using appropriate fastening components.
- Mount the MPU-6500 IMU on the back of EVN Alpha to make it stable during the challenges.
- Install the OpenMV Cam RT1062 onto its holder and slightly tilt the camera downwards for improved line and obstacle detection.

**Step 4: Attach the Wheels**
- Attach the front wheels securely to the steering hubs using appropriate axles.
- Install the rear wheels onto the driven axle that is connected to the motor.
- Add spacers or equivalent components to keep the wheels properly fixed and aligned.

**Step 5: Preparation for operation**
- Ensure the chassis is stable and properly balanced.
- Arrange cables so that they do not interfere with moving parts.

**Step 6: Software setup**
- Connect the controllers and sensors to a computer for programming.
- Upload the control and vision codes located in /src
- Verify that each component (motors, servos, camera, IMU) responds correctly.


## License <a class="anchor" id="License"></a>

```
GNU General Public License v3.0

Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
