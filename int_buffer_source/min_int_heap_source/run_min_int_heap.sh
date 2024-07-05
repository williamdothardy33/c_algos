#!/bin/bash
cc -c min_int_heap.c min_int_heap_test.c swap.c
cc -o min_int_heap min_int_heap.o min_int_heap_test.o swap.o ../int_buffer.o 
./min_int_heap

