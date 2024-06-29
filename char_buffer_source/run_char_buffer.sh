#!/bin/bash
cc -c char_buffer.c char_buffer_test.c
cc -o char_buffer char_buffer.o char_buffer_test.o
./char_buffer