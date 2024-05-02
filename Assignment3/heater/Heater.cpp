/**
 * @author Rokas Barasa (285047@via.dk)
 * @author Arturas Maziliauskas (285051@via.dk)
 * @date 2021-11-23
 */
#include "Heater.h"

// function to turn on heater by writing to gpio pin
void Heater::turnOnHeater()
{
    fs.open("/sys/class/gpio/gpio50/value", std::fstream::out);
    fs << 1;
    fs.close();
}

// function to turn off heater by writing to gpio pin
void Heater::turnOffHeater()
{
    fs.open("/sys/class/gpio/gpio50/value", std::fstream::out);
    fs << 0;
    fs.close();
}


