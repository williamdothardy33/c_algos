#!/bin/bash
cc -c int_quick_sort.c int_quick_sort_test.c
cc -o int_quick_sort int_quick_sort.o int_quick_sort_test.o ../lib_utils/swap.o ../int_buffer_source/int_buffer.o
./int_quick_sort