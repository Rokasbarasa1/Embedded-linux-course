# Assignment 3 of embedded operating systems course

The project is a greenhouse monitoring system that tracks temperature, humidity and light level. The system is hosted on a Beaglebone Black running Debian OS with changes meant for the Beaglebone black hardware. The environment is monitored with sensors connected to the Beaglebone. The Beaglebone hosts a Node.js server that serves a website with the sensor data displayed and some controls for led light, window open position with a servo or a heater being on or off. The node.js server has a socket connection to the website client and constantly updates the values on the client.

Bellow is how the website looks like.

![alt text](img/image.png)

Please look at the "EOS Assignment 3 Report.pdf" for more details.

# Some compilation stuff bellow:

--- Build c++ file
arm-linux-gnueabihf-g++ main.cpp tempHum/hih8120.cpp tempHum/hih8120.h I2CDevice.cpp I2CDevice.h photosensor/photoresistor.cpp photosensor/photoresistor.h heater/Heater.cpp heater/Heater.h pwm/pwm.cpp pwm/pwm.h -o greenhouse

--- Before starting node server, run the port forwarding script on the beaglebone

--- Start node server
node server.js

