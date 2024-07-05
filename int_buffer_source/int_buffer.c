#include "int_buffer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int_buf *create_int_buf(int start) {
    int_buf *buf = malloc(sizeof(int_buf));
    int *new_buf = calloc(4, sizeof(int));
    buf->start = start;
    buf->offset = start;
    buf->data = new_buf;
    buf->length = 4;
    return buf;
}

void append(int_buf *buf, int n) {
    if (buf->offset == buf->length) {
        buf->length *= 2;
        int *new_buf = realloc(buf->data, sizeof(int) * buf->length);
        buf->data = new_buf;
    }
    *(buf->data + buf->offset) = n;
    buf->offset++;
}

int *take_last(int_buf *buf, int count) {
    int *result = NULL;
    if (buf->offset - count >= buf->start) {
        result = malloc(count * sizeof(int));
        int new_offset = buf->offset - count;
        memcpy(result, buf->data + new_offset, count * sizeof(int));
        buf->offset = new_offset;
    }
    return result;
}



void show_buf(int_buf *buf, int start) {
    int offset = start;
    while (offset < buf->offset) {
        printf("number %d at offset %d\n", *(buf->data + offset), offset);
        offset++;
    }
}

int not_empty(int_buf *buf) {
    int result = buf->offset - buf->start;
    return result;
}

int *peek_last(int_buf *buf) {
    int *result = NULL;
    if (not_empty(buf)) {
        result = (buf->data + (buf->offset - 1));
    }
    return result;
}


