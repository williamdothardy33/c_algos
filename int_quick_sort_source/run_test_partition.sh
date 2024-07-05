#!/bin/bash
cc -c int_quick_sort.c partition_test.c
cc -o int_partition_test int_quick_sort.o partition_test.o ../lib_utils/swap.o ../int_buffer_source/int_buffer.o
./int_partition_test