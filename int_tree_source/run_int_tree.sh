#!/bin/bash
cc -c int_tree.c int_tree_test.c
cc -o int_tree int_tree.o int_tree_test.o
./int_tree