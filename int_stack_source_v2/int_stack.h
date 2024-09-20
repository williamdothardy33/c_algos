#include <stdio.h>
#define MAX_SIZE 20

struct int_stack {
    int out_offset;
    int in_offset;
    int underlying[MAX_SIZE + 1];
};

typedef struct int_stack int_stack;

int_stack *create_int_stack();
void push(int_stack *stack, int data);
int pop(int_stack *stack);
int not_empty(int_stack *stack);
void show_stack(int_stack *stack);