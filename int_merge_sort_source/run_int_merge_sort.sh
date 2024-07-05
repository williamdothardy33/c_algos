#!/bin/bash
cc -c int_merge_sort.c int_merge_sort_test.c
cc -o int_merge_sort int_merge_sort.o int_merge_sort_test.o ../int_buffer_source/int_buffer.o
./int_merge_sort