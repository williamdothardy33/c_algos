#!/bin/bash
cc -c int_linkedlist.c int_linkedlist_test.c
cc -o int_linked_list int_linkedlist.o int_linkedlist_test.o
./int_linked_list