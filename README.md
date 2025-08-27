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
- [Folder Contents](#folder-contents-)
- [The Challenge](#challenge)
  [Vehicle](#Vehicle)
- [Hardware Components](#Hardware)
- [Power and Sense Management](#power-and-sense-management)
- [Software Components](#Software)
- [Robot Construction Guide](#robot-construction-guide-)
- [Resources](#Resources)
- [License](#License)

# Folder Contents <a class="anchor" id="folder-contents-"></a>
* `models` is for the 3D files we used to print our parts
* `other` includes other files which can be used to understand how to prepare the vehicle for the competition. It includes documentations, datasets, hardware specifications, communication protocols,  descriptions etc.
* `schemes` contains schematic diagrams of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `t-photos` contains photos of the team and logos
* `v-photos` contains 6 photos of the vehicle from various angles
* `video` contains the video.md file with the link to our YouTube channel and the respective videos

# The Challenge <a class="anchor" id="challenge"></a>

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
<p style="margin:0;"> Below, we have included the diagram of our motor for clarity. </p> <img src ="other/motor/motor.diagram.png" alt= "Diagram" width = "400" style="display:block; margin:0 auto;" />
  

### Steering
Our robot uses a **reckless steering** mechanism, a simplified form of Ackermann steering where the wheels are directly turned without complex linkage geometry. This method makes the robot easier to turn and keeps the overall design compact. It is highly effective for lightweight and fast-moving prototypes where simplicity and space efficiency are key.

#### Servo Motor
<table> <tr><td><img src = "other/servo motor/geek.PNG" alt="Servo motor" width = "800" </td> <td valign="top" style="padding-left: 15px;"> <b>Specifications:</b><br> Operating Voltage: 3.3V~6V<br> Rated Voltage: 4.8V<br> Rotational range: 360°<br> Maximum Torque: 1.6kg±0.2kg/cm (4.8V)<br> Maximum Speed: 45rpm (3V)<br> Weight: 20g<br><br> For steering we selected the <b>GeekServo</b>. This motor is compatible with Lego Technic parts and offers a higher speed compared to 9g motors. The output shaft features a Lego Technic axle connector, making it ideal for applications that require a high-power drive. </td> </tr> </table> 
<p style="margin:0;"> <p>Below, we have included the diagram of our servo motor.</p> <img src="other/servo motor/servo.diagram.jpg" alt = "servo diagram" width = "500" display:block; margin:0 auto; width:400px;" />

### Chassis
Our chassis combines LEGO components with custom 3D-printed parts, creating a reliable and durable structure.

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

## Robot Construction Guide <a class="anchor" id="robot-construction-guide-"></a>
**Step 1: Assemble the steering system**  
- Mount the GeekServo motor securely onto the chassis using screws or brackets.  
- Connect the steering axle to the servo using a suitable coupling or connector.  
- Ensure the servo mount is firmly fixed so it doesn’t wobble during operation.  
- Install the front steering hubs using a metal rod or axle to secure them.  
- Make sure the steering arm moves freely and does not collide with the chassis.  

**Step 2: Assemble the powertrain**  
- The motor was mounted securely onto the chassis to ensure stability during operation.
- The GA12-N20 DC motor is placed into the mount and attached firmly (using appropriate fastening components).
- The motor output shaft is connected to an axle and gear mechanism to transmit rotation.
- The rear axle with wheels is installed, ensuring that the gear ratio provides smooth and efficient power transfer to the wheels.

**Step 3: Mount the electronics**
- Place the EVN Alpha controller onto the chassis and secure it in position using appropriate fastening components.
- Attach the Li-ion battery underneath the electronics section to maintain balance.
- Mount the MPU-6500 IMU on the motor support so that it is stable during operation.
- Install the OpenMV Cam RT1062 onto its holder and slightly tilt the camera upwards for improved line and obstacle detection.

**Step 4: Attach the Wheels**
- Attach the front wheels securely to the steering hubs using appropriate axles.
- Install the rear wheels onto the driven axle that is connected to the motor.
- Add spacers or equivalent components to keep the wheels properly fixed and aligned.

**Step 5: Preparation for operation**
- Ensure the chassis is stable and properly balanced.
- Arrange cables so that they do not interfere with moving parts.

**Step 6: Software setup**
- Connect the controllers and sensors to a computer for programming.
- Upload the control and vision codes required for system operation.
- Verify that each component (motors, servos, camera, IMU) responds correctly.



## Resources <a class="anchor" id="Resources"></a>
Fusion360
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
