//
// Created by mazils on 2021. 10. 23..
//
#include "pwm.h"


//duty cycle is changeble
void pwm::send_pwm(int duty_cycle, int period, int channel){

    // Write to file to set the duty cycle for pwm
    fs.open(("/sys/class/pwm/pwmchip1/pwm-1:"+std::to_string(channel)+"/duty_cycle").c_str(), std::fstream::out);
    fs << std::to_string(duty_cycle);
    fs.close();
    
    // Write to file to set the period for pwm
    fs.open(("/sys/class/pwm/pwmchip1/pwm-1:"+std::to_string(channel)+"/period").c_str(), std::fstream::out);
    fs << std::to_string(period);
    fs.close();
    
    // Write to file to enable pwm 
    fs.open(("/sys/class/pwm/pwmchip1/pwm-1:"+std::to_string(channel)+"/enable").c_str(), std::fstream::out);
    fs << std::to_string(1);
    fs.close();
}

// Pwm for controlling led light
// Percentage is multiplied by 200000 which is 1% of the period
void pwm::send_pwm_percentage(int perc, int period,int channel)
{
    send_pwm(perc*200000,period,channel);
}