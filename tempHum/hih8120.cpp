#include "hih8120.h"
/**
 * @author Rokas Barasa (285047@via.dk)
 * @author Arturas Maziliauskas (285051@via.dk)
 * @date 2021-11-23
 */
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <bitset>
#include <iomanip>  

using namespace std;

namespace greenhouse {

    
    //Constructor
    hih8120::hih8120(unsigned int I2CBus, unsigned int I2CAddress):
        I2CDevice(I2CBus, I2CAddress){   // this member initialisation list calls the parent constructor
        this->I2CAddress = I2CAddress;
        this->I2CBus = I2CBus;
        this->temperature = -100;
        this->humidity = -100;

    }

    void hih8120::readCurrentTemperatureHumidity(){
        unsigned char* response = this->readDevice(4);

        //Check status bits from response[0][0], response[0][1]
        if (response[0] > 127){
            //Means the bits are set
            cout << "Bad status" << std::endl;
        }

        // if status 01 adjust it
        int adjustedRes0 = response[0];

        if (response[0] > 63){
            adjustedRes0 = response[0] & ~(0x01 << 6);
        }

        //Concatenate most significant and least significant byte of humidity
        //Humidity
        unsigned int humidity = adjustedRes0 << 8 | response[1];

        //Temperature
        //Concatenate the first as most significant byte with least significant byte. 
        //Shift least significant byte to right by two because last two bits do are not important.
        unsigned int temperature = response[2] << 6 | response[3] >> 2;

        this->humidity = this->map14bitValueHumidity(humidity);
        this->temperature = this->map14bitValueTemperature(temperature);
    }

    float hih8120::map14bitValueHumidity(unsigned int value){
        //Also rounds the value to single decimal
        return floor((value/16383.0 * 100.0) * 10) / 10;
    }

    float hih8120::map14bitValueTemperature(unsigned int value){
        //Also rounds the value to single decimal
        return floor((value/16383.0 * 165.0 - 40.0) * 10) / 10;
    }
}