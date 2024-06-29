#include "char_stack.h"

void push(char_buf *stack, char c) {
    append(stack, c);
}

char *pop(char_buf *stack) {
    char *result = take_last(stack, 1);
    return result;
}

char *peek(char_buf *stack) {
    char *result = peek_last(stack);
    return result;
}

int has_next(char_buf *stack) {
    return not_empty(stack);
}