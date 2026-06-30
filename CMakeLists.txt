cmake_minimum_required(VERSION 4.2)
project(adc_project C)

set(CMAKE_C_STANDARD 99)

add_executable(adc_project main.c
        adc.h
        filereader.c
        adc.c)
