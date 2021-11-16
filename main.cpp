#include "temperature/hih8120.h"
#include "photosensor/photoresistor.h"
#include "pwm/pwm.h"
#include "heater/Heater.h"
#include <iostream>

#define ADDR 0x27   //I2C address of temperature senso
#define SERVOCHANNEL 0
#define LIGHTCHANNEL 1


void printTemperatureAndHumidity() {
    greenhouse::hih8120 hih8120(2, ADDR);
    hih8120.readCurrentTemperatureHumidity();
    std::cout << "Humidity:    " << hih8120.humidity << std::endl;
    std::cout << "Temperature: " << hih8120.temperature << std::endl;
}

void printTemperature() {
    greenhouse::hih8120 hih8120(2, ADDR);
    hih8120.readCurrentTemperatureHumidity();

    std::cout << hih8120.temperature << std::endl;
}

void controlLightIntensity(int i) {
    pwm pwm_led;
    pwm_led.send_pwm_percentage(i, 20000000, LIGHTCHANNEL);
}

void printHumidity() {
    greenhouse::hih8120 hih8120(2, ADDR);
    hih8120.readCurrentTemperatureHumidity();
    std::cout << hih8120.humidity << std::endl;
}

void controlServo(std::string i) {
    pwm pwm_servo;

    if (i == "open") {
        pwm_servo.send_pwm(2000000, 20000000, SERVOCHANNEL);
    } else if (i == "close") {
        pwm_servo.send_pwm(1000000, 20000000, SERVOCHANNEL);
    }
}

std::string readFile(std::string path) {
    std::ifstream fs;
    std::string data;
    fs.open(path);
    fs >> data;
    fs.close();
    return data;
}


void heaterOnOff(std::string i) {
    Heater heater;
    if (i == "on") {
        heater.turnOnHeater();
    } else if (i == "off") {
        heater.turnOffHeater();
    }

}

void printLightLevel() {
    greenhouse::photoresistor photoresistor(2);
    photoresistor.readCurrentLightLevel();
    std::cout << photoresistor.lightLevel << std::endl;
}


void readWindowPos() {
    std::string wpos = readFile("/sys/class/pwm/pwmchip1/pwm-1:0/duty_cycle");
    if (wpos.compare("2000000") == 0) {
        std::cout << "WindowOpen:    " << std::endl;
    } else if (wpos.compare("1000000") == 0) {
        std::cout << "WindClosed:    " << std::endl;
    } else {
        std::cout << "erro reading window pos" << std::endl;
    }
}

void readHeater() {
    struct stat st;
    if (stat("/sys/class/gpio/gpio50", &st) == 0)
    {
        std::string val = readFile("/sys/class/gpio/gpio50/value");
        std::cout << "heater on:" + val<<std::endl;
    } else
    {
       std::cout << "heater is off";
    }
}

void readLightIntensity() {
    std::string lightDuty = readFile("/sys/class/pwm/pwmchip1/pwm-1:1/duty_cycle");
    std::cout << "light intensity: " + std::to_string(atoi(lightDuty.c_str()) / 200000)<<std::endl;
}

int main(int argc, char **argv) {
    if (argc >= 2) {
        if (std::string(argv[1]) == "--help") {

            std::cout << std::endl << "Greenhouse device features arguments: " << std::endl << std::endl
                      << "readTempAndHumidity - Prints current temperature (C) and humidity (RH%) in greenhouse."
                      << std::endl
                      << "readTemp - Prints current temperature (C) in greenhouse." << std::endl
                      << "readHumidity - Prints current humidity (RH%)in greenhouse." << std::endl
                      << "controlLightIntensity - controls light intensity. Params from 0 to 100 ." << std::endl
                      << "controlWindow - controls window in greenhouse.Params open or close ." << std::endl
                      << "readLightIntensity - reads light intensity from 0% to 100% ." << std::endl
                      << "readWindowPos - reads postition,open or close ." << std::endl
                      << "readHeater - reads status,on or off ." << std::endl
                      << "heater - controls heater in greenhouse.Params on or off ." << std::endl;

        } else if (std::string(argv[1]) == "readTempAndHumidity") {

            printTemperatureAndHumidity();

        } else if (std::string(argv[1]) == "readTemp") {

            printTemperature();

        } else if (std::string(argv[1]) == "readHumidity") {

            printHumidity();

        } else if (std::string(argv[1]) == "readLightLevel") {

            printLightLevel();
        }
        else if(std::string(argv[1]) == "setLightLevel")
        {
            controlLightIntensity(atoi(argv[2]));
        } else if (std::string(argv[1]) == "readLightIntensity") {
            readLightIntensity();
        }
        else if(std::string(argv[1]) == "setWindowStatus")
        {
            controlServo(argv[2]);
        }
        else if(std::string(argv[1]) == "readWindow")
        {
            readWindowPos();
        }
        else if(std::string(argv[1]) == "setHeaterStatus")
        {
            heaterOnOff(argv[2]);
        } else if (std::string(argv[1]) == "readHeater") {
            readHeater();
        } else {
            std::cout << "Argument unrecognized see --help" << std::endl;
        }
    } else {

        std::cout << "No arguments unrecognized see --help" << std::endl;

    }

    return 0;
}





