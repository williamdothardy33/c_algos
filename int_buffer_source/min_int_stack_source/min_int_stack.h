#include "../int_buffer.h"
struct min_int_stack {
    int_buf buf;
    int min;
};

typedef struct min_int_stack min_int_stack;


void push(min_int_stack *stack, int n);
int *pop(min_int_stack *stack);
int *peek(min_int_stack *stack);
int has_next(min_int_stack *stack);
int find_min(min_int_stack *stack);
int from_min_to(min_int_stack *stack, int n);
int prev_min_from(min_int_stack *stack, int n);

