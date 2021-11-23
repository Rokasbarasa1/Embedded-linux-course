/**
 * @author Rokas Barasa (285047@via.dk)
 * @author Arturas Maziliauskas (285051@via.dk)
 * @date 2021-11-23
 */

#ifndef GREENHOUSE_TEMP_HEATER_H
#define GREENHOUSE_TEMP_HEATER_H


#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include <sys/stat.h>


class Heater {
public:
    Heater() {
//
        //todo check if the pin is already innitialized
//        system("sudo sh -c \"echo 50 > /sys/class/gpio/export\"");
//        system("sudo sh -c \"echo out > /sys/class/gpio/gpio50/direction\"");
        struct stat st;
        if(!stat("/sys/class/gpio/gpio50",&st) == 0)
        {
            fs.open("/sys/class/gpio/export", std::fstream::out);
            fs << 50;
            fs.close();
        }
        fs.open("/sys/class/gpio/gpio50/direction", std::fstream::out);
        fs << "out";
        fs.close();
    }
    void turnOnHeater();
    void turnOffHeater();
    void isHeaterOn();

private:
    std::fstream fs;
};


#endif //GREENHOUSE_TEMP_HEATER_H
