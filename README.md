![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)

TEAM BACK TO THE FUTURE
===
<table>
  <tr>
    <td colspan="2">
      <img src="t-photos/logo/Banner.png" alt="Banner" width="100%">
    </td>
  </tr>
  <tr>
    <td width="60%">
      <img src="t-photos/TeamOfficial.jpg" alt="Official Photo" width="48%">
      <img src="t-photos/TeamFunny.jpg" alt="Funny Photo" width="48%">
    </td>
    <td valign="top" style="padding-left: 0px;">
      <p>
        This repository details team <em>Back To The Future</em>'s building and programming process in our first participating year of the 2025 WRO Future Engineers Competition. 
      </p>
      We are team <em> Back To The Future</em>, three students who are passionate about technology and robotics. For this competition we built an autonomous robot. We worked after school and on weekends. Through this competition, we learned how to work as a team and solve problems related to robotics.
       </p>
        Team Members:
          Ayça Nisa Çerçi, 16,
          Mert Ata Makinacı, 16,
          Tibet Özkarslıoğlu, 17
      </p>
    </td>
  </tr>
</table>

## Contents

* `t-photos` contains 2 photos of the team
* `v-photos` contains 6 photos of the vehicle
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.



## Content of README
- [Hardware](#hardware)
  - [Main Components](#main-components)
  - [Mobility Management](#mobility-management)
    - [Locomotion](#locomotion)
    - [Chassis](#chassis)
    - [Steering](#steering)
  - [Power and Sense Management](#power-and-sense-management)
      - [Power and Wiring](#power-and-wiring)
      - [Sensors](#sensors)
- [Software and Control](#software-and-control) <!-- split open & obstacle -->
  - [Smartphone](#smartphone)
  - [EVN Alpha](#evn-alpha) 
- [Vehicle Assembly](vehicle-assembly)

## Hardware      
## Main Components
|         Name         | Product |  | Price |
|----------------------|---------|--|---------------|
|Motor with Encoder| | | | 
|Servo Motor|[Tower Pro MG995 (270 degrees)](https://www.ebay.com/itm/192002483556)|![5636c657-0cd0-4d13-8898-64bef9c5e61f](https://github.com/user-attachments/assets/547408d4-09bc-4009-9e1d-5a8174e7c158) |12$|(https://github.com/user-attachments/assets/24153173-324e-47f3-af15-a5b4c12d5f1b)|
|Motor Controller|[EVN Alpha](https://coresg.tech/product/evn-alpha/)|![51e03d1a-d107-451d-8259-466d851f1624](https://github.com/user-attachments/assets/5b57c9b9-c09f-42b9-89eb-908f45598b74)|168$|
|Camera and Processor|[Samsung Galaxy A53 5G](https://www.amazon.com/SAMSUNG-Smartphone-Unlocked-Android-Battery/dp/B09XP9FX25?th=1)|![313c07cd-1411-4db1-8fcf-41a2f3f53fa0](https://github.com/user-attachments/assets/588559a9-8b7e-48d5-888c-0a5fe9707440)|142$|
<!-- add TOF -->
Total cost: *To be determined*

## Mobility Management

### Chassis


### Locomotion
 ![pololu](https://github.com/user-attachments/assets/98ad7a46-8e2f-4e3d-b88e-eaa1144e8000)

 Our robot **does not use** 'Pololu Metal Gearmotor'. This gearmotor is a powerful 12V brushed DC motor with a 30:1 metal gearbox and an integrated quadrature encoder with a resolution of 64 counts per revolution (CPR) of the motor shaft and 1920 CPR of the gearbox’s output shaft. The gearbox is composed mainly of spur gears, but it features helical gears for the first stage for reduced noise and improved efficiency. These units have a 16 mm-long, 6 mm-diameter D-shaped output shaft.
 <!-- update motor -->
 ![5636c657-0cd0-4d13-8898-64bef9c5e61f](https://github.com/user-attachments/assets/496ba26b-fb70-4716-afa9-adf85f60039e)


### Steering
 To control steering we use a 'Tower Pro MG995'. The MG995 servo motor offers an increase in speed, tension and precision over the SG90 and MG90S micro servo motors. This high-speed standard servo motor can rotate 270 degrees.


## Power and Sense Management
### Power and Wiring
### Sensors
![313c07cd-1411-4db1-8fcf-41a2f3f53fa0](https://github.com/user-attachments/assets/1457b2ef-e899-43d1-bb90-d939aba67b07)


Our robot uses the `Samsung Galaxy A53 5G`'s cameras for visual input. The code accesses the 64 MP ƒ/1.6 Main Camera with OIS for driving forward and 32 MP ƒ/2.2 Front Camera for going backwards.

<!-- add TOF -->

## Software and Control

### Smarthphone

### EVN Alpha
For controlling the DC Motor With Encoder and the Servo Motor, our robot utilizes an EVN Alpha, based on the [RP2040](https://www.raspberrypi.com/products/rp2040/) microcontroller designed by Raspberry Pi. It features 4 motor drivers with encoder inputs, 2 UART controllers, 16 I2C ports (achieved with multiplexing of the 2 I2C controllers on RP2040), 4 Servo controllers and a USB-C port for charging and data transfer. It can be programmed with the [Arduino IDE](https://www.arduino.cc/en/software/), after installing the [Arduino Pico Core](github.com/earlephilhower/arduino-pico/) and [EVN Library](https://github.com/EVNdevs/EVN-arduino).
## Vehicle Assembly  
