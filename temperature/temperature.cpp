//
// Created by mazils on 2021. 11. 09..
//

#include <string>
#include <iostream>
#include "temperature.h"

float temperature::get_temperature()
{
   unsigned char * bytes = this -> readDevice(4);
//   std::string bytes_string(reinterpret_cast<char*>(bytes));
//   bytes_string.at()
    if (bytes[0] > 63)
    {
        perror("error with bytes");
        exit(-1);
    } else
    {
        int result =  bytes[2]<<8 |  bytes[3];
        std::cout << result <<
    }
}