//
// Created by mazils on 2021. 11. 14..
//

#include "Heater.h"

void Heater::turnOnHeater()
{
    fs.open("/sys/class/gpio/gpio50/value", std::fstream::out);
    fs << 1;
    fs.close();
    // system("cat /sys/class/gpio/gpio50/value");
}
void Heater::turnOffHeater()
{
    fs.open("/sys/class/gpio/gpio50/value", std::fstream::out);
    fs << 0;
    fs.close();
    // system("cat /sys/class/gpio/gpio50/value");
}


