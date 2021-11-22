//
// Created by mazils on 2021. 11. 14..
//

#ifndef GREENHOUSE_TEMP_HEATER_H
#define GREENHOUSE_TEMP_HEATER_H


#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include <sys/stat.h>


class Heater {
public:

    //COnstructro that initializes gpio50 if it is not initialized and then sets it to output
    Heater() {

        struct stat st;
        //Check if gpio50 already exists 
        if(!stat("/sys/class/gpio/gpio50",&st) == 0)
        {
            //Create the file
            fs.open("/sys/class/gpio/export", std::fstream::out);
            fs << 50;
            fs.close();
        }

        // Set it to output
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
