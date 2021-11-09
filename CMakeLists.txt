cmake_minimum_required(VERSION 3.20)
project(greenhouse_temp)

set(CMAKE_CXX_STANDARD 14)

add_executable(greenhouse_temp main.cpp IMU/imu.cpp IMU/imu.h)
