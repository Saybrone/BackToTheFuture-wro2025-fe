
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
      We are team <em> Back To The Future</em>, three students who are passionate about technology and robotics. For this competition we built an autonomous vehicle. We worked after school and on weekends. Through this competition, we learned how to work as a team and solve problems related to robotics.
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

* `t-photos` contains photos of the team and logos
* `v-photos` contains 6 photos of the vehicle
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.

## Content of README
- [Hardware](#hardware)
  - [Components](#components)
  - [Mobility Management](#mobility-management)
    - [Chassis and Design](#chassis-and-design)
    - [Locomotion](#locomotion)
    - [Steering](#steering)
  - [Power and Sense Management](#power-and-sense-management)
    - [Power and Wiring](#power-and-wiring)
    - [Sensors](#sensors)
- [Software and Control](#software-and-control)
- [Vehicle Assembly](#vehicle-assembly)


## Hardware      
This section discusses all the parts used in the vehicle including the motors, sensors, controllers, chassis, mechanisms and other elements.

### Components
<table>
    <thead>
        <tr>
            <th>Component</th>
            <th>Product Link</th>
            <th>Image</th>
            <th>Price</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Motor with Encoder</td>
            <td><a href="https://www.pololu.com/product/4755">Metal Gearmotor</a></td>
            <td><img src="other/motor/motor_trn.png" alt="motor trn" width="120"></td>
            <td>90$</td>
        </tr>
        <tr>
            <td>Servo Motor</td>
            <td><a href="https://www.ebay.com/itm/192002483556">Tower Pro MG995 (270 degrees)</a></td>
            <td><img src="other/servo/servo2.png" alt="servo mg995" width="120"></td>
            <td>12$</td>
        </tr>
        <tr>
            <td>Motor Controller</td>
            <td><a href="https://coresg.tech/product/evn-alpha/">EVN Alpha</a></td>
            <td><img src="other/evn/evn2.png" alt="evn" width="150"></td>
            <td>168$</td>
        </tr>
            <td>Sensor</td>
            <td><a href="https://www.amazon.com/VKLSVAN-Measurements-Breakout-Accurate-Distance/dp/B099N2JW89/ref=sr_1_21?dib=eyJ2IjoiMSJ9.FHoX1s21bwww8-NUEd8BDmuIcVpW6rD7ehPzn9Nrcnr83wpj7UbUi9nTPdVbzD0BZQBe4NcTkUF81jqL1nH1B1oWyGsGmJvVDI9LizHIMgQa-9x9Kawya7KRBut3eaMHHIsh7hhXHszMiLL41TcW_TsiRXD4baq3nEYucGFwMjmp6Hhz-geVCebnKhqtsht6ni7oUUj8yK9zkh-7uDRcyYCAQC9mr7VNeh2rTVr-RnM.0Bbbq1BQlA3MnEtffctAFpx3Wft-0tIANuMAgv0CXwg&dib_tag=se&keywords=time+of+flight+sensor&qid=1748441943&sr=8-21">Time Of Flight Sensor</a></td>
            <td><img src="other/tof_sensor/tof3.png" alt="time-of-flight" width="79"></td>
            <td>9$</td>
        <tr>
            <td>Camera and Processor</td>
            <td><a href="https://www.amazon.com/SAMSUNG-Smartphone-Unlocked-Android-Battery/dp/B09XP9FX25?th=1">Samsung Galaxy A53 5G</a></td>
            <td><img src="other/phone/samsung.png" alt="samsung-galaxy-a53-5g" width="120"></td>
            <td>142$</td>
        </tr>
        <tr>
            <td colspan="3"><strong>Total cost:</strong></td>
            <td><strong>421$</strong></td>
        </tr>
    </tbody>
</table>

</body>
</html>


## Mobility Management
This section contains information about the vehicle's movement. 

### Chassis and Design


### Locomotion

### Steering
 To control steering we use a 'Tower Pro MG995'. The MG995 servo motor offers an increase in speed, tension and precision over the SG90 and MG90S micro servo motors. This high-speed standard servo motor can rotate 270 degrees.


## Power and Sense Management

### Power and Wiring

### Sensors
Our vehicle uses the `Samsung Galaxy A53 5G`'s cameras for visual input. The code accesses the 64 MP ƒ/1.6 Main Camera with OIS for driving forward and 32 MP ƒ/2.2 Front Camera for going backwards.

<!-- add TOF -->

## Software and Control

### EVN Alpha
For controlling the DC Motor With Encoder and the Servo Motor, our vehicle utilizes an EVN Alpha, based on the [RP2040](https://www.raspberrypi.com/products/rp2040/) microcontroller designed by Raspberry Pi. It features 4 motor drivers with encoder inputs, 2 UART controllers, 16 I2C ports (achieved with multiplexing of the 2 I2C controllers on RP2040), 4 Servo controllers and a USB-C port for charging and data transfer. It can be programmed with the [Arduino IDE](https://www.arduino.cc/en/software/), after installing the [Arduino Pico Core](github.com/earlephilhower/arduino-pico/) and [EVN Library](https://github.com/EVNdevs/EVN-arduino).

### Smarthphone

## Vehicle Assembly  
