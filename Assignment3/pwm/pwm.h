/**
 * @author Rokas Barasa (285047@via.dk)
 * @author Arturas Maziliauskas (285051@via.dk)
 * @date 2021-11-23
 */

#ifndef BEAGLEBONEGREENHOUSE_PWM_H
#define BEAGLEBONEGREENHOUSE_PWM_H
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>

class pwm {
public:
    //Constructor which initializes the pins for pwm leds and servo 
    pwm()
    {
        system("config-pin P9_22 pwm");
        system("config-pin P9_21 pwm");
    }

    void send_pwm(int duty_cycle, int period,int channel);
    void send_pwm_percentage(int perc, int period,int channel);

private:
    std::fstream fs;
};




#endif //BEAGLEBONEGREENHOUSE_PWM_H
