//
// Created by mazils on 2021. 10. 23..
//
#include "pwm.h"


//duty cycle is changeble
void pwm::send_pwm(int duty_cycle, int period,int channel){
//    system("pwd");
    fs.open(("/sys/class/pwm/pwmchip1/pwm-1:"+std::to_string(channel)+"/duty_cycle").c_str(), std::fstream::out);
    fs << std::to_string(duty_cycle);
    fs.close();
    printf("duty cycle:");
    system(("cat /sys/class/pwm/pwmchip1/pwm-1:"+std::to_string(channel)+"/duty_cycle").c_str());

    fs.open(("/sys/class/pwm/pwmchip1/pwm-1:"+std::to_string(channel)+"/period").c_str(), std::fstream::out);
    fs << std::to_string(period);
    fs.close();
    printf("period:");
    system(("cat /sys/class/pwm/pwmchip1/pwm-1:"+std::to_string(channel)+"/period").c_str());
    fs.open(("/sys/class/pwm/pwmchip1/pwm-1:"+std::to_string(channel)+"/enable").c_str(), std::fstream::out);
    fs << std::to_string(1);
    fs.close();
    printf("enable:");
    system(("cat /sys/class/pwm/pwmchip1/pwm-1:"+std::to_string(channel)+"/enable").c_str());
}

void pwm::send_pwm_percentage(int perc, int period,int channel)
{
    send_pwm(perc*200000,period,channel);
}