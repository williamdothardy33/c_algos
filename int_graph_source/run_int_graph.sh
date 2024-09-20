#!/bin/bash
cc -c int_graph.c int_graph_test.c
cc -o int_graph int_graph.o int_graph_test.o ../int_queue_source/int_queue.o ../int_stack_source_v2/int_stack.o
./int_graph