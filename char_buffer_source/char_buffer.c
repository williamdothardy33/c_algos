#include "char_buffer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char_buf *create_char_buf() {
    char_buf *buf = malloc(sizeof(char_buf) + 4);
    buf->length = 4;
    buf->offset = 0;
    return buf;
}

void append(char_buf *buf, char c) {
    if (buf->offset == buf->length) {
        buf->length *= 2;
        char_buf *new_buf = realloc(buf, (sizeof(char_buf) +buf->length));
        buf = new_buf;
    }
        *(buf->data + buf->offset) = c;
        buf->offset++;
}

char *take_last(char_buf *buf, int count) {
    char *result = NULL;
    if (buf->offset - count >= 0) {
        result = malloc(count);
        int new_offset = buf->offset - count;
        memcpy(result, (buf->data + new_offset), count);
        int current = new_offset;
        buf->offset = new_offset;
    }
    return result;
}



void show_buf(char_buf *buf) {
    int offset = 0;
    while (offset < buf->offset) {
        printf("char %c at offset %d\n", *(buf->data + offset), offset);
        offset++;
    }
}

int not_empty(char_buf *buf) {
    int result = buf->offset;
    return result;
}

char *peek_last(char_buf *buf) {
    char *result = NULL;
    if (not_empty(buf)) {
        result = (buf->data + buf->offset - 1);
    }
    return result;
}


