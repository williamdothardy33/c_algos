#!/bin/bash
cc -c insertion_sort.c insertion_sort_test.c
cc -o insertion_sort insertion_sort.o insertion_sort_test.o
./insertion_sort