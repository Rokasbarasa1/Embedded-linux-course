This archive contains updated device driver source files for I2C, and an example binary to test the HIH8120 temperature and humidity sensor.

The following two files replace the files with same names in Derek Molloy's Exploring Beaglebone GIT repository in the folder: chp08/i2c/cpp/
The original files address the i2c bus incorrect for the latest Debian image.
> I2CDevice.cpp
> I2CDevice.h

The file Humidity19 is a compiled program, using this driver, to demonstrate the HIH8120 sensor.
1) Turn off the Beaglebone and connect the sensor pcb.
2) Turn on the Beaglebone again and download the file: Humidity19
3) Set X-permissions on the file to make it executable.
4) Run with ./Humidity19
It should show an output simmilar to this:
Humidity (%)        :58.3
Temperature (deg. C):23.2

ERL/2020.10.25