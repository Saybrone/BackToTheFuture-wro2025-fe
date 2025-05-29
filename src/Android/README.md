# Flux Android App – WRO 2025

This project is an Android application developed using Kotlin and OpenCV for real-time camera processing and robot control via USB serial communication. 
It takes in images from the 0.5x zoom camera for better FOV. Then filters and simplifies the image until its ready to process. The clean image is used to identify the color and distance of the traffic signs. This data is then transfered to the EVN via the serial port using a direct usb connection.

---

## Folder Structure
```
AndroidStudio/
├── app/
  └──src
    └──main
      └──java
        └──com
          └──howthe
            └──flux
              └──Mainactivity.kt  #main code
├── build.gradle.kts
├── settings.gradle.kts
└── README.md
```
The main body of the code is in this directory:
[src/Android/AndroidStudio/app/src/main/java/com/howthe/flux/MainActivity.kt](https://github.com/OzzyBozy/BackToTheFuture-wro2025-fe)

---
## Camera Processing Example
![ProcessGif](examples/process.gif)

