[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](/COPYING.gpl)

# Team BACK TO THE FUTURE - WRO® 2025 Future Engineers

<table border="0">
  <tr border="0">
    <td  border="0" colspan="2">
      <img src="t-photos/logo/Banner.png" alt="Banner" width="100%">
    </td>
  </tr>
  <tr border="0">
    <td width="65%"  border="0">
      <img src="t-photos/TeamOfficial.jpg" alt="Official Photo" width="48%">
      <img src="t-photos/TeamFunny.jpg" alt="Funny Photo" width="48%">
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
- [Vehicle](#Vehicle)
- [Hardware Components](#Hardware)
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
Our robot integrates LEGO components with custom 3D-printed hardware, designed to maximize stability and durability. It features a 3D-printed motor mount and camera holder, integrated with a LEGO-based chassis. For steering, we implemented a simplified Ackermann setup without linkage geometry (reckless steering), allowing the robot to turn easily while keeping the design compact. Our robot is powerized by a [GA12-N20 200RPM](https://www.handsontec.com/dataspecs/GA12-N20.pdf) dc motor and controlled by an [EVNAlpha](https://evn.readthedocs.io/). It uses [OpenMV RT1062](https://openmv.io/products/openmv-cam-rt?srsltid=AfmBOorMjCmNBP1AZA_3V53JQMS-8N7Mg5ljP10ljHe4SLFoCauGWzZN) to locate obstacles, lines and walls. Steering was managed by [GeekServo 2KG Motor](https://kittenbothk-eng.readthedocs.io/en/latest/motors/2kgMotor.html).



## V-Photos <a class="anchor" id="Vphotos"></a>
| <img src="v-photos/front.jpg" width="90%" /> | <img src="v-photos/back.jpg" width="85%" /> | 
| :--: | :--: | 
| *Front* | *Back* |
| <img src="v-photos/left.jpg" width="90%" /> | <img src="v-photos/right.jpg" width="85%" /> | 
| *Left* | *Right* |
| <img src="v-photos/top.jpg" width="90%" /> | <img src="v-photos/bottom.jpg" width="85%" /> | 
| *Top* | *Bottom* |

<br>

# Hardware Components <a class="anchor" id="Hardware"></a>
This section discusses ...
## Mobility Management
Our robot’s mobility depends on the coordination of its powertrain, steering system, and chassis. Together, these components provide stability, control, and efficiency, enabling smooth and reliable movement.
### Powertrain
#### Motor
html <table> <tr> <!-- Görsel Kısmı --> <td> <img width="813" height="722" alt="motor" src="https://github.com/user-attachments/assets/cbc7350e-6660-4c34-99db-c2983fde7c3f" /> </td> <!-- Metin Kısmı --> <td valign="top" style="padding-left: 15px;"> <b>Specifications:</b><br> Rated Voltage: 6~12V <br> Weight: 10g <br> Revolving Speed: 100RPM @ 6V <br> Load Speed: 80RPM <br> Rated Torque: 2 kg.cm <br> Stall Torque: 16 kg.cm <br><br> This <b>DC Mini Metal Gear Motor</b> is the one we used in our robot. Its <b>light weight</b> and <b>compact size</b> make it suitable for small robotic platforms, while the <b>high torque</b> and <b>low RPM</b> ensure powerful and controlled movement. <br><br> Thanks to its <b>excellent stall characteristics</b>, the motor provides enough force to climb slopes or overcome obstacles, which is highly beneficial for mobile robots. Additionally, the <b>durable metal gears</b> extend the lifetime of the motor, making it reliable for long-term use. <br><br> Another important advantage is that a wheel can be easily mounted on the motor’s output shaft, allowing for simple integration with the robot’s chassis. </td> </tr> </table>
<p style="margin:0;"> Below, we have included the diagram of our motor for clarity. </p> <img width="571" height="207" alt="Ekran Alıntısı" src="https://github.com/user-attachments/assets/c8769703-f8e3-4611-8122-a4f2439efcb6" style="display:block; margin:0 auto;" />


     

### Steering
#### Servo Motor
<table> <tr> <!-- Görsel Kısmı --> <td> <img width="735" height="616" alt="output-onlinetools" src="https://github.com/user-attachments/assets/ae1580ef-0944-4630-b2ee-5670c99bc04d" />
 </td> <!-- Metin Kısmı --> <td valign="top" style="padding-left: 15px;"> <b>Specifications:</b><br> Operating Voltage: 3.3V~6V<br> Rated Voltage: 4.8V<br> Rotational range: 360°<br> Maximum Torque: 1.6kg±0.2kg/cm (4.8V)<br> Maximum Speed: 45rpm (3V)<br> Weight: 20g<br><br> For steering we selected the <b>GeekServo</b>. This motor is compatible with Lego Technic parts and offers a higher speed compared to 9g motors. The output shaft features a Lego Technic axle connector, making it ideal for applications that require a high-power drive. </td> </tr> </table>

### Chassis



## Software Components <a class="anchor" id="Software"></a>

## Robot Construction Guide <a class="anchor" id="robot-construction-guide-"></a>

## Resources <a class="anchor" id="Resources"></a>

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

```
