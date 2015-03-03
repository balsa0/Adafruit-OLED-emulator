# Adafruit-OLED-emulator
![alt icon](https://raw.githubusercontent.com/balsa0/Adafruit-OLED-emulator/master/emulator.png)

License: GPLv2
Adafruit SSD1306 OLED emulator for development
It's a development tool for this library: https://github.com/hallard/ArduiPi_SSD1306
More info: http://hallard.me/adafruit-ssd1306-oled-display-driver-for-raspberry-pi/

# Requirements
Uses Qt version 5.4 (Qt creator is optional)

# In action
https://www.youtube.com/watch?v=OHbGzgvjZ9w

# How to use:
- Simply write your normal code after "/***PUT YOUR CODE HERE***/" tag in main.cpp
- Compile and run to test if the screen content is OK for you
- When you finished coding, simply port it into your Raspberry pi, delete '#define development_on' in main.cpp and compile like normal. Your code should work fine on the real device.

# Features
- Screen is emulated in a window
- You can magnify your emulated screen
- The program simulates the I/O speed of the real device
- WARNING! Some functions from Adafruit_GFX.cpp are not yet implemented. If you miss something, look back later! :)

https://www.youtube.com/watch?v=OHbGzgvjZ9w
