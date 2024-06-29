#include "char_buffer.h"
#include <stdio.h>

int main(void) {
    char_buf *buf = create_char_buf();
    append(buf, 'c');
    append(buf, 'a');
    append(buf, 't');
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf);
    printf("appending another t...\n");
    append(buf, 't');
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf);
    printf("\n");
    printf("after taking 1...\n");
    take_last(buf, 1);
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf);

    printf("\n");
    printf("after taking 2...\n");
    take_last(buf, 2);
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf);
    printf("\n");
    printf("appending another t...\n");
    append(buf, 't');
    printf("current length is %d\n", buf->length);
    printf("current offset is %d\n", buf->offset);
    show_buf(buf);
    

    while (not_empty(buf)) {
        printf("the next char is %c\n", *peek_last(buf));
        take_last(buf, 1);
    }
}