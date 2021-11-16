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

    void photoresistor::readCurrentLightLevel(){
        ifstream indata;
        char data[4];
        indata.open("/sys/bus/iio/devices/iio\:device0/in_voltage0_raw");
        indata >> data;        
        indata.close();

        int value = atoi(data);
        //READ SOME FILE 
        this->lightLevel = this->mapVoltsToPercentage(value);
    }

    float photoresistor::mapVoltsToPercentage(unsigned int value){
        int min = 0;
        float max = 3700;
        //Also rounds the value to single decimal
        return floor((value/max * 100.0) * 10) / 10;
    }
}