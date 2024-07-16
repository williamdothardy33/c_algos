#include "int_stack.h"
#include <stdlib.h>

int_stack *create_int_stack() {
    int_stack *stack = malloc(sizeof(int_stack));
    stack->in_offset = 1;
    stack->out_offset = -1;
    for (int i = 1; i <= MAX_SIZE; i++) {
        stack->underlying[i] = 0;
    }
    return stack;
}

void push(int_stack *stack, int data) {
    if (stack->out_offset == -1 && stack->in_offset == 1) {
        stack->underlying[stack->in_offset] = data;
        stack->in_offset++;
        stack->out_offset = 1;
    }
    else if (stack->in_offset > MAX_SIZE) {
            printf("warning stack is full!\n");
    }
    else {
        stack->underlying[stack->in_offset] = data;
        stack->in_offset++;
        stack->out_offset = stack->in_offset - 1;
    }
}

int pop(int_stack *stack) {
    if (stack->out_offset == -1 && stack->in_offset == 1) {
        printf("warning stack is empty!\n");
        return -1;
    }
    else if (stack->out_offset == 1) {
        int result = stack->underlying[stack->out_offset];
        stack->out_offset = -1;
        stack->in_offset = 1;
        return result;
    }
    else {
        int result = stack->underlying[stack->out_offset];
        stack->in_offset = stack->out_offset;
        stack->out_offset--;
        return result;
    }
}

int not_empty(int_stack *stack) {
    if (stack->out_offset == -1 && stack->in_offset == 1) {
        return 0;
    }
    else {
        return 1;
    }
}