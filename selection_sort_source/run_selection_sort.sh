#!/bin/bash
cc -c selection_sort.c selection_sort_test.c swap.c
cc -o selection_sort selection_sort.o selection_sort_test.o swap.o
./selection_sort