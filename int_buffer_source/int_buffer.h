#include <stdio.h>

struct int_buf {
    int length;
    int offset;
    int *data;
    int start;
};

typedef struct int_buf int_buf;

int_buf *create_int_buf(int start);
void append(int_buf *buf, int n);
int *take_last(int_buf *buf, int count);
void show_buf(int_buf *buf, int start);
int *peek_last(int_buf *buf);
int not_empty(int_buf *buf);