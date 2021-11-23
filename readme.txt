--- Build c++ file
arm-linux-gnueabihf-g++ main.cpp tempHum/hih8120.cpp tempHum/hih8120.h I2CDevice.cpp I2CDevice.h photosensor/photoresistor.cpp photosensor/photoresistor.h heater/Heater.cpp heater/Heater.h pwm/pwm.cpp pwm/pwm.h -o greenhouse

--- Before starting node server, run the port forwarding script on the beaglebone

--- Start node server
node server.js

