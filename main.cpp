/**
 * @author Rokas Barasa (285047@via.dk)
 * @author Arturas Maziliauskas (285051@via.dk)
 * @date 2021-11-23
 */
#include "tempHum/hih8120.h"
#include "photosensor/photoresistor.h"
#include "pwm/pwm.h"
#include "heater/Heater.h"
#include <iostream>

#define ADDR 0x27   //I2C address of temperature senso
#define SERVOCHANNEL 0
#define LIGHTCHANNEL 1

/**
 * @brief Read the temperature and humidity form the hih8180 
 * and print it using the values form the object.
 * 
 */
void printTemperatureAndHumidity() {
    greenhouse::hih8120 hih8120(2, ADDR);
    hih8120.readCurrentTemperatureHumidity();
    std::cout << "Temperature: " << hih8120.temperature << "     " << std::endl;
    std::cout << "Humidity:    " << hih8120.humidity << "     " << std::endl;
}

/**
 * @brief Read the temperature form the hih8180 
 * and print it using the values form the object.
 * 
 */
void printTemperature() {
    greenhouse::hih8120 hih8120(2, ADDR);
    hih8120.readCurrentTemperatureHumidity();

    std::cout << "Temperature: " << hih8120.temperature << "     " << std::endl;
}


/**
 * @brief Control the light intensity of the led light 
 * 
 * @param i 0-100 integer value 
 */
void controlLightIntensity(int i) {
    pwm pwm_led;
    pwm_led.send_pwm_percentage(i, 20000000, LIGHTCHANNEL);
}

/**
 * @brief Read the humidity form the hih8180 
 * and print it using the values form the object.
 * 
 */
void printHumidity() {
    greenhouse::hih8120 hih8120(2, ADDR);
    hih8120.readCurrentTemperatureHumidity();
    std::cout << "Humidity:    " << hih8120.humidity << "     " << std::endl;
}

/**
 * @brief Control window on or off depending if a correct string is passed.
 * 
 * @param i 
 */
void controlServo(std::string i) {
    pwm pwm_servo;

    if (i == "open") {
        pwm_servo.send_pwm(2000000, 20000000, SERVOCHANNEL);
    } else if (i == "close") {
        pwm_servo.send_pwm(1000000, 20000000, SERVOCHANNEL);
    }
}

/**
 * @brief Helper function to read text from files
 * 
 * @param path path to file.
 * @return std::string text from file
 */
std::string readFile(std::string path) {
    std::ifstream fs;
    std::string data;
    fs.open(path);
    fs >> data;
    fs.close();
    return data;
}

/**
 * @brief Turns heater on or off depending if a correct string is passed.
 * 
 * @param i = string which indicates if to turn on heater or turn off
 */
void heaterOnOff(std::string i) {
    Heater heater;
    if (i == "on") {
        heater.turnOnHeater();
    } else if (i == "off") {
        heater.turnOffHeater();
    }

}

/**
 * @brief Prints light level in the room after reading it from the photoresistor
 * 
 */
void printLightLevel() {
    greenhouse::photoresistor photoresistor(2);
    photoresistor.readCurrentLightLevel();
    std::cout << "Light level: " << photoresistor.lightLevel << "     " << std::endl;
}

/**
 * @brief Read the position of a window by reading pwm value of servo motor
 * 
 * Reads a file and if the value is 2000000 it is open, if it is 1000000 it is closed
 */
void readWindowPos() {
    std::string wpos = readFile("/sys/class/pwm/pwmchip1/pwm-1:0/duty_cycle");
    if (wpos.compare("2000000") == 0) {
        std::cout << "Window:      open" << "     " << std::endl;
    } else if (wpos.compare("1000000") == 0) {
        std::cout << "Window:      closed" << "     " << std::endl;
    } else {
        std::cout << "error reading window pos" << std::endl;
    }
}

/**
 * @brief Read the status of the heater: on or off
 * 
 * Reads a file to check if it is on or off
 * 1 is on, 0 is off
 * 
 */
void readHeater() {
    struct stat st;
    if (stat("/sys/class/gpio/gpio50", &st) == 0){
        std::string val = readFile("/sys/class/gpio/gpio50/value");
        if(val[0] == '1'){
            std::cout << "Heater:      on" << "    " << std::endl;
        }else{
            std::cout << "Heater:      off" << "    " << std::endl;
        }
    } else{
        std::cout << "Heater:      off" << "    " << std::endl;
    }
}

/**
 * @brief Read the percentage of power going to led lamp
 * 
 * Read directly form a file that stores the duty_cycle
 * The duty cycle is then divided by the period to get percentage
 * 
 */
void readLightIntensity() {
    std::string lightDuty = readFile("/sys/class/pwm/pwmchip1/pwm-1:1/duty_cycle");
    std::cout << "Led light:   " + std::to_string(atoi(lightDuty.c_str()) / 200000)<< "     " << std::endl;
}

int main(int argc, char **argv) {
    //Check that there are enough variables
    if (argc >= 2) {

        //Check what functionality the user wants to 
        //perform and directs it to the appropriate function

        //Functions either scan a peripheral and print the details to console or just read some file and print to console prints.
        if (std::string(argv[1]) == "--help") {

            std::cout << std::endl << "Greenhouse device features arguments: " << std::endl << std::endl
                      << "readTempAndHumidity - Prints current temperature (C) and humidity (RH%) in greenhouse."<< std::endl
                      << "readTemp - Prints current temperature (C) in greenhouse." << std::endl
                      << "readHumidity - Prints current humidity (RH%)in greenhouse." << std::endl
                      << "readLightLevel - Prints current light level in greenhouse." << std::endl
                      << "setLedLight - controls led light intensity. Params from 0 to 100 ." << std::endl
                      << "readLedLight - Prints led light intensity. From 0% to 100%" << std::endl
                      << "setWindowStatus - controls window in greenhouse.Params open or close ." << std::endl
                      << "readWindow - reads postition,open or close ." << std::endl
                      << "readHeater - reads status,on or off ." << std::endl
                      << "setHeaterStatus - controls heater in greenhouse.Params on or off ." << std::endl;

        } else if (std::string(argv[1]) == "readTempAndHumidity") {

            printTemperatureAndHumidity();

        } else if (std::string(argv[1]) == "readTemp") {

            printTemperature();

        } else if (std::string(argv[1]) == "readHumidity") {

            printHumidity();

        } else if (std::string(argv[1]) == "readLightLevel") {

            printLightLevel();

        }else if(std::string(argv[1]) == "setLedLight"){

            controlLightIntensity(atoi(argv[2]));

        } else if (std::string(argv[1]) == "readLedLight") {

            readLightIntensity();

        }else if(std::string(argv[1]) == "setWindowStatus"){
            
            controlServo(argv[2]);
        
        }else if(std::string(argv[1]) == "readWindow"){
            
            readWindowPos();

        }else if(std::string(argv[1]) == "setHeaterStatus"){
            
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