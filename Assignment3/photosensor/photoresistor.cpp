/**
 * @author Rokas Barasa (285047@via.dk)
 * @author Arturas Maziliauskas (285051@via.dk)
 * @date 2021-11-23
 */
#include "photoresistor.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <bitset>
#include <iomanip>  
#include <fstream>

using namespace std;

namespace greenhouse {

    
    //Constructor
    photoresistor::photoresistor(unsigned int I2CBus){
        this->lightLevel = I2CBus;
    }

    // Readd corrent value from photoresistor
    void photoresistor::readCurrentLightLevel(){
        // Read from file and take only 4 character
        ifstream indata;
        char data[4];
        indata.open("/sys/bus/iio/devices/iio\:device0/in_voltage0_raw");
        indata >> data;        
        indata.close();

        //Convert to int and map the value to be 0-100 percentage, then set it as the stored light level variable
        int value = atoi(data);
        this->lightLevel = this->mapVoltsToPercentage(value);
    }

    float photoresistor::mapVoltsToPercentage(unsigned int value){
        int min = 0;
        float max = 3700;
        //Also rounds the value to single decimal
        return floor((value/max * 100.0) * 10) / 10;
    }
}