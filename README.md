#  Automated Home Security System - a simulated home security system project #
 Made by (Name - Student ID):
  1) Chaini Mitrsatit - 6310506528
  2) Yatawee Samanawattana - 6310506536
  3) Theewara Madtharad - 6310506617
  4) Wongree Samutpoonpaisal - 6310506765

 Computer Engineering (CPE) Faculty, Kasetsart University, Bangkok
 This project was made for 01204322 Embedded System.
 
------------------------------------------------------------------------

Source code: 
 1)ldr-sensor-to-line.ino
 2)pir.ino
 3)led-ldr.ino
 4)temp-time.ino
 4)index.js


------------------------------------------------------------------------

Libraries used:

 1) WiFi.h
 2) HTTPClient.h
 3) Adafruit_GFX.h
 4) Adafruit_SSD1306.h
 5) Wire.h
 6) WiFiServer.h
 7) WiFiUdp.h
 8) ESPAsyncWebServer.h
 9) NTPClient.h

------------------------------------------------------------------------

Components used:

 1) NodeMCU-32S microcontrollers
 2) SSD1306 128x64 I2C OLED display
 3) white LEDs
 4) 120Ω ,10kΩ ,and 330Ω resistors
 5) Buzzer
 6) LDR
 7) Laser Head Sensor Module KY-008
 8) PIR Sensor
 
------------------------------------------------------------------------ 

Details:

This project is a home security system that includes various systems such as Laser Fence, which uses laser light to detect intruders around the house, Temperature Checking system that monitors and displays the temperature inside the house and sends an alert when the temperature is higher than normal, Motion Sensor system that uses PIR to detect burglary inside the house and turn on the lights when the owner is at home, and Automatic Light system that helps to turn on and off the lights automatically when there is insufficient light.

------------------------------------------------------------------------ 

Background:

Currently, home security is important because homes often store valuable items and can be vulnerable to theft, as well as potential accidents such as fires. Therefore, having a good security system is crucial to provide peace of mind for the occupants and ensure their safety. A reliable security system can also provide convenience, especially if it can be controlled through Line. This allows easy management of various security systems, even when the owner is away from home, as long as they have a mobile device connected to the internet. Therefore, the project developers decided to create a project related to an internal home security system that can be controlled through Line.