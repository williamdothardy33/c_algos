#include "../char_buffer.h"
void push(char_buf *stack, char c);
char *pop(char_buf *stack);
char *peek(char_buf *stack);
int has_next(char_buf *stack);