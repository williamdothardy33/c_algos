#include "../int_buffer.h"
void push(int_buf *stack, int n);
int *pop(int_buf *stack);
int *peek(int_buf *stack);
int has_next(int_buf *stack);