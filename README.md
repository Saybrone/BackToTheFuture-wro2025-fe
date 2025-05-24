Engineering Documentation
===
This repository details team *Back To The Future*'s building and programming process in our first participating year of the 2025 WRO Future Engineers Competition.

## Contents

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)
* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.
  ## Team Members
  *  `Ayca Nisa Cerci`, `16`, [aycanisa2009@gmail.com]()
  * `Tibet Ozkarslioglu`,`17`,[]()
  * `Mert Ata Makinaci`, `17`, []()

## Content of README
- [Hardware](#hardware)
  - [Components](#components)
  - [Mobility Management](mobility-management)
    - [Chassis](chassis)
    - [Design](design)
    - [Motors](motors)
- [Power and Sense Management](power-and-sense-management)
    - [Power and Wiring](power-and-wiring)
    - [Sensors](sensors)
    
- [Software](#software)
- [VehicleAssembly](vehicle-assembly)
## Hardware      
### Components
|         Name         | Product |  | Price |
|----------------------|---------|--|---------------|
|Motor with Encoder|[Pololu Metal Gearmotor](https://www.pololu.com/product/4752)|![pololu](https://github.com/user-attachments/assets/019b71c6-35ac-46f1-a9e4-02765043771c)|90$| 
|Servo Motor       |[Tower Pro MG995 (270 degrees)](https://www.ebay.com/itm/192002483556)| ![servo mg995](https://github.com/user-attachments/assets/dfcc7500-9c63-4463-907d-12806d3642b5) |12$|(https://github.com/user-attachments/assets/24153173-324e-47f3-af15-a5b4c12d5f1b)|
|Motor Controller|[EVN Alpha](https://coresg.tech/product/evn-alpha/)|![evn](https://github.com/user-attachments/assets/5e598600-4bd6-4547-a392-e0a88f6ed4d6)|168$|
|Camera and Processor|[Samsung Galaxy A53 5G](https://www.amazon.com/SAMSUNG-Smartphone-Unlocked-Android-Battery/dp/B09XP9FX25?th=1)|![samsung-galaxy-a53-5g-1649224506](https://github.com/user-attachments/assets/7d8ca584-5bd3-4486-b065-0236df9594a8)|142$|

Total cost:          387$

## Mobility Management

 ## Chassis
 
 ## Design
 ## Motors
 Our robot uses `Pololu Metal Gearmotor`. This gearmotor is a powerful 12V brushed DC motor with a 30:1 metal gearbox and an integrated quadrature encoder with a resolution of 64 counts per revolution (CPR) of the motor shaft and 1920 CPR of the gearbox’s output shaft. The gearbox is composed mainly of spur gears, but it features helical gears for the first stage for reduced noise and improved efficiency. These units have a 16 mm-long, 6 mm-diameter D-shaped output shaft.
 To control steering we use a  `Tower Pro MG995`. The MG995 servo motor offers an increase in speed, tension and precision over the SG90 and MG90S micro servo motors. This high-speed standard servo motor can rotate 270 degrees.


## Power and Sense Management
 ## Power and Wiring
 ## Sensors
 We use a `Samsung Galaxy A53 5G ` for the camera. It has a Quad Camera Array system that includes 64MP main, 12MP ultrawide, 5MP macro, and 5MP depth cameras for versatile photography.

## Software







## Vehicle Assembly  
