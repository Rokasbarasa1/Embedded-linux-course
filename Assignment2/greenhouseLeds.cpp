//Authors:
//Rokas Barasa
//Arturas Maziliauskas


#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include <string> 
#include <fstream>
using namespace std;

bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool IsNegativeNumber(char* string){
    if(string[0] == '-' ){
        string[0] = '1';
        if (isNumber(string)){
            string[0] = '-';
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv){
    if(argc == 2){
        if(isNumber(argv[1]) || IsNegativeNumber(argv[1])){

            stringstream intValue(argv[1]);
            int duty_cycle = 10;
            intValue >> duty_cycle;

            if(duty_cycle > -1 && duty_cycle < 101){
                std::fstream fs;

                system("config-pin P9_21 pwm");

                fs.open("/sys/class/pwm/pwmchip1/pwm-1:1/duty_cycle", std::fstream::out);
                fs << to_string(duty_cycle*200000);
                fs.close();

                fs.open("/sys/class/pwm/pwmchip1/pwm-1:1/period", std::fstream::out);
                fs << to_string(20000000);
                fs.close();

                if(duty_cycle != 0){
                    fs.open("/sys/class/pwm/pwmchip1/pwm-1:1/enable", std::fstream::out);
                    fs << to_string(1);
                    fs.close();
                }else{
                    fs.open("/sys/class/pwm/pwmchip1/pwm-1:1/enable", std::fstream::out);
                    fs << to_string(0);
                    fs.close();
                }
                std::cout << "PWM enabled!" << std::endl;
            }else{
                std::cout << "Variable is outisde range of 0-100!" << std::endl;
            }
        }else{
            std::cout << "Variable is not a number!" << std::endl;
        }
    }else{
        std::cout << "Need at least one variable that is integer 0-100!" << std::endl;
    }
    return 0;
}
