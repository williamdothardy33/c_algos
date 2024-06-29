#!/bin/bash
cc -c int_buffer.c int_buffer_test.c
cc -o int_buffer int_buffer.o int_buffer_test.o
./int_buffer