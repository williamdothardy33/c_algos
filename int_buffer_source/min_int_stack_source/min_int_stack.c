#include "min_int_stack.h"

void push(min_int_stack *stack, int n) {
    if (!(not_empty(&(stack->buf)))) {
        stack->min = n;
        append(&(stack->buf), n);

    }
    else {
        if (n < stack->min) {
            stack->min = n;
            int shrunk = from_min_to(stack, n);
            append(&(stack->buf), shrunk);
        }
        else {
            append(&(stack->buf), n);
        }
    }
}

int *pop(min_int_stack *stack) {
    int *next = take_last(&(stack->buf), 1);
    if (*next < stack->min) {
        int previous_min = prev_min_from(stack, *next);
        *next = stack->min;
        stack->min = previous_min;
        return next;
    }
    else {
        return next;
    }
    
}

int *peek(min_int_stack *stack) {
    int *result = peek_last(&(stack->buf));
    return result;
}

int has_next(min_int_stack *stack) {
    return not_empty(&(stack->buf));
}

int from_min_to(min_int_stack *stack, int min) {
    int shrunk = (2 * min) - stack->min;
    return shrunk;
}

int prev_min_from(min_int_stack *stack, int shrunk) {
    int result = (2 * stack->min) - shrunk;
    return result;
}