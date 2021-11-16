//
// Created by mazils on 2021. 11. 09..
//
#include <glib.h>
#include <glib/gprintf.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifndef GREENHOUSE_TEMP_TEMPERATURE_H
#define GREENHOUSE_TEMP_TEMPERATURE_H

#include  "../I2C_device/I2CDevice.h"
class temperature : public exploringBB::I2CDevice{
public:
    temperature(unsigned int bus, unsigned int device) : I2CDevice(bus, device) {


    }
    float get_temperature();

private:
    int file;
};


#endif //GREENHOUSE_TEMP_TEMPERATURE_H
