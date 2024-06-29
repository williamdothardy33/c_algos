#!/bin/bash
cc -c greet.c greet_driver.c
cc -o greet greet.o greet_driver.o
./greet