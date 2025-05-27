![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)

BACK TO THE FUTURE
===
This repository details team *Back To The Future*'s building and programming process in our first participating year of the 2025 WRO Future Engineers Competition.

## Contents

* `t-photos` contains 2 photos of the team
* `v-photos` contains 6 photos of the vehicle
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.
  
## Team Members
* `Ayça Nisa Çerçi`, `16`
* `Mert Ata Makinacı`, `16`
* `Tibet Özkarslıoğlu`,`17`


## Content of README
- [Hardware](#hardware)
  - [Main Components](#main-components)
  - [Mobility Management](#mobility-management)
    - [Chassis](#chassis)
    - [Locomotion](#locomotion)
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
|Servo Motor|[Tower Pro MG995 (270 degrees)](https://www.ebay.com/itm/192002483556)|![servo mg995](https://github.com/user-attachments/assets/775db116-2eb7-49bd-b430-ee684dd2f643)|12$|(https://github.com/user-attachments/assets/24153173-324e-47f3-af15-a5b4c12d5f1b)|
|Motor Controller|[EVN Alpha](https://coresg.tech/product/evn-alpha/)|![evn](https://github.com/user-attachments/assets/ea11b87a-3cdb-4b34-91df-56fa9f72e148)|168$|
|Camera and Processor|[Samsung Galaxy A53 5G](https://www.amazon.com/SAMSUNG-Smartphone-Unlocked-Android-Battery/dp/B09XP9FX25?th=1)|![samsung-galaxy-a53-5g-1649224506](https://github.com/user-attachments/assets/bb0c2284-e31f-4d1e-9894-2a4d427404f4)|142$|
<!-- add TOF -->
Total cost: *To be determined*

## Mobility Management

### Chassis


### Locomotion
 ![pololu](https://github.com/user-attachments/assets/98ad7a46-8e2f-4e3d-b88e-eaa1144e8000)

 Our robot **does not use** 'Pololu Metal Gearmotor'. This gearmotor is a powerful 12V brushed DC motor with a 30:1 metal gearbox and an integrated quadrature encoder with a resolution of 64 counts per revolution (CPR) of the motor shaft and 1920 CPR of the gearbox’s output shaft. The gearbox is composed mainly of spur gears, but it features helical gears for the first stage for reduced noise and improved efficiency. These units have a 16 mm-long, 6 mm-diameter D-shaped output shaft.
 <!-- update motor -->
 ![MG995 Servo](https://github.com/user-attachments/assets/b2d15c89-af1f-4998-85a2-f57b6c1cd723)

### Steering
 To control steering we use a 'Tower Pro MG995'. The MG995 servo motor offers an increase in speed, tension and precision over the SG90 and MG90S micro servo motors. This high-speed standard servo motor can rotate 270 degrees.


## Power and Sense Management
### Power and Wiring
### Sensors
 ![samsung-galaxy-a53-5g-1649224506](https://github.com/user-attachments/assets/c52c331c-2ae9-4525-b641-e5fa8973589e)

Our robot uses the `Samsung Galaxy A53 5G`'s cameras for visual input. The code accesses the 64 MP ƒ/1.6 Main Camera with OIS for driving forward and 32 MP ƒ/2.2 Front Camera for going backwards.

<!-- add TOF -->

## Software and Control

### Smarthphone

### EVN Alpha
For controlling the DC Motor With Encoder and the Servo Motor, our robot utilizes an EVN Alpha, based on the [RP2040](https://www.raspberrypi.com/products/rp2040/) microcontroller designed by Raspberry Pi. It features 4 motor drivers with encoder inputs, 2 UART controllers, 16 I2C ports (achieved with multiplexing of the 2 I2C controllers on RP2040), 4 Servo controllers and a USB-C port for charging and data transfer. It can be programmed with the [Arduino IDE](https://www.arduino.cc/en/software/), after installing the [Arduino Pico Core](github.com/earlephilhower/arduino-pico/) and [EVN Library](https://github.com/EVNdevs/EVN-arduino).
## Vehicle Assembly  
