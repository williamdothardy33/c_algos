#!/bin/bash
cc -c char_stack.c char_stack_test.c 
cc -o char_stack char_stack.o char_stack_test.o ../char_buffer.o
./char_stack