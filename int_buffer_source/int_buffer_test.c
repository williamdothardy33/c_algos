#include "int_buffer.h"
#include <stdio.h>

int main(void) {
    int_buf *buf = create_int_buf(2);
    append(buf, 1);
    append(buf, 2);
    append(buf, 3);
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf, 0);
    printf("appending another number...\n");
    append(buf, 4);
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf, 0);
    printf("\n");
    printf("appending another number...\n");
    append(buf, 5);
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf, 0);
    printf("\n");

    printf("after taking a number...\n");
    take_last(buf, 1);
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf, 0);

    printf("\n");
    printf("after taking 2 numbers...\n");
    take_last(buf, 2);
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf, 0);
    printf("\n");

    printf("appending another number...\n");
    append(buf, 6);
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf, 0);
    

    while (not_empty(buf)) {
        printf("the next number is %d\n", *peek_last(buf));
        take_last(buf, 1);
    }
}