#include "int_stack.h"

void push(int_buf *stack, int c) {
    append(stack, c);
}

int *pop(int_buf *stack) {
    int *result = take_last(stack, 1);
    return result;
}

int *peek(int_buf *stack) {
    int *result = peek_last(stack);
    return result;
}

int has_next(int_buf *stack) {
    return not_empty(stack);
}