#!/bin/bash
cc -c combinatorics.c combinatorics_test.c
cc -o combinatorics combinatorics.o combinatorics_test.o ../int_queue_source/int_queue.o ../int_stack_source_v2/int_stack.o ../int_graph_source/int_graph.o
./combinatorics