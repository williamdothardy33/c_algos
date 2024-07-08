#!/bin/bash
cc -c int_stack.c int_stack_test.c
cc -o int_stack int_stack.o int_stack_test.o
./int_stack