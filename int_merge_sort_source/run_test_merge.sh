#!/bin/bash
cc -c int_merge_sort.c int_merge_test.c
cc -o test_merge int_merge_sort.o int_merge_test.o ../int_buffer_source/int_buffer.o
./test_merge