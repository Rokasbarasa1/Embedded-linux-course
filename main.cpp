#include "hih8120.h"
#include "photoresistor.h"
#include <iostream>
#include <string.h>

#define ADDR 0x27   //I2C address of temperature sensor

void printTemperatureAndHumidity(){
    greenhouse::hih8120 hih8120(2, ADDR);
    hih8120.readCurrentTemperatureHumidity();

    std::cout << "Humiduty:    " << hih8120.humidity << std::endl;
    std::cout << "Temperature: " << hih8120.temperature << std::endl;
}

void printTemperature(){
    greenhouse::hih8120 hih8120(2, ADDR);
    hih8120.readCurrentTemperatureHumidity();

    std::cout << hih8120.temperature << std::endl;
}

void printHumidity(){
    greenhouse::hih8120 hih8120(2, ADDR);
    hih8120.readCurrentTemperatureHumidity();

    std::cout << hih8120.humidity << std::endl;
}

void printLightLevel(){
    greenhouse::photoresistor photoresistor(2);
    photoresistor.readCurrentLightLevel();

    std::cout << photoresistor.lightLevel << std::endl;
}

int main(int argc, char** argv) {
    if(argc >= 2){
        if(std::string(argv[1]) == "--help"){

            std::cout << std::endl << "Greenhouse device features arguments: " << std::endl << std::endl
            << "readTempAndHumidity - Prints current temperature (C) and humidity (RH%) in greenhouse." << std::endl
            << "readTemp - Prints current temperature (C) in greenhouse." << std::endl
            << "readHumidity - Prints current humidity (RH%)in greenhouse." << std::endl;

        }else if(std::string(argv[1]) == "readTempAndHumidity"){
            
            printTemperatureAndHumidity();

        }else if(std::string(argv[1]) == "readTemp"){
            
            printTemperature();

        }else if(std::string(argv[1]) == "readHumidity"){
            
            printHumidity();

        }else if(std::string(argv[1]) == "readLightLevel"){
            
            printLightLevel();

        }else{
            
            std::cout << "Argument unrecognized see --help" << std::endl;

        }
    }else{

        std::cout << "No arguments unrecognized see --help" << std::endl;

    }

    return 0;
}