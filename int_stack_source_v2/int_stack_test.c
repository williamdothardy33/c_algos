#include "int_stack.h"
#include <stdio.h>

int index_of_unpaired(char *s, int s_length) {
    int_stack *stack = create_int_stack();
    char *current = s;
    int offset = 0;
    while (offset < s_length) {
        char c = *(current + offset);
        if (c == ')') {
            if (not_empty(stack)) {
                pop(stack);
            }
            else {
                return offset;
            }
        }
        else {
            push(stack, offset);
        }
        offset += 1;
    }

    if (not_empty(stack)) {
        int error_offset = pop(stack);
        return error_offset;
    }
    else {
        return -1;
    }


}

int max_pairs(char *s, int s_length) {
    char *current = s;
    int offset = 0;
    int count = 0;
    int_stack *stack = create_int_stack(0);
    while (offset < s_length) {
        char c = *(current + offset);
        if (c == ')') {
            if (not_empty(stack)) {
                pop(stack);
                count++;
            }
        }
        else {
            push(stack, offset);
        }
        offset++;
    }
    return count;
}

int max_pairs_length(char *s, int s_length) {
    int num_pairs = max_pairs(s, s_length);
    int result = 2 * num_pairs;
    return result;
}

int max_interval(char *s, int s_length) {
    char *current = s;
    int offset = 0;
    int_stack *stack = create_int_stack(0);
    int min_opening = s_length;
    int max_closing = -1;
    while (offset < s_length) {
        char c = *(current + offset);
        if (c == ')') {
            if (not_empty(stack)) {
                int opening_offset = pop(stack);
                if (opening_offset < min_opening) {
                    min_opening = opening_offset;
                }
                if (offset > max_closing) {
                    max_closing = offset;
                }
            }
        }
        else {
            push(stack, offset);
        }
        offset++;
    }

    int result = max_closing - min_opening;
    if (result > 0) {
        return result;
    }
    else {
        return 0;
    }
}

int main(void) {
    int_stack *stack = create_int_stack();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    push(stack, 6);

    while (not_empty(stack)) {
        int next = pop(stack);
        printf("the next element is: %d\n", next);
    }


    char *s0 = "((())())()";
    char *s1 = ")()(";
    char *s2 = "())";
    char *s3 = ")()(())()()))())))(";

    int result0 = index_of_unpaired(s1, 10);
    printf("the string %s has first unpaired brace at index: %d\n", s1, result0);
    printf("\n");
    int result1 = max_pairs(s3, 19);
    printf("the string %s has a maximum of %d paired braces\n", s3, result1);

    int result2 = max_interval(s3, 19);
    printf("the string %s has a maximum paired brace interval of length of %d \n", s3, result2);

}