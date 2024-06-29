#include "char_stack.h"
#include <stdio.h>

int is_balanced(char *s, int s_length) {
    char_buf *stack = create_char_buf();
    char *current = s;
    int offset = 0;
    while (offset < s_length) {
        char c = *(current + offset);
        if (c == ')') {
            if (not_empty(stack)) {
                pop(stack);
            }
            else {
                return 0;
            }
        }
        else {
            push(stack, c);
        }
        offset += 1;
    }

    if (not_empty(stack)) {
        return 0;
    }
    else {
        return 1;
    }


}

int main(void) {
    char_buf *stack = create_char_buf();
    push(stack, 'c');
    push(stack, 'a');
    push(stack, 'n');
    push(stack, 'c');
    push(stack, 'e');
    push(stack, 'l');

    while (has_next(stack)) {
        char *next = pop(stack);
        printf("the next element is: %c\n", *(next));
    }


    char *s0 = "((())())()";
    char *s1 = ")()(";
    char *s2 = "())";
    

    int result = is_balanced(s2, 10);
    printf("the string %s is balanced: %s\n", s2, result == 0 ? "False" : "True");

}