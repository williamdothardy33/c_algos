#include "min_int_heap.h"
#include <threads.h>

int parent_offset(int child_offset) {
    if (child_offset == 1) {
        return -1;
    }
    return child_offset / 2;
}

int child_offset(int parent_offset) {
    return 2 * parent_offset;
}
void sink(int_buf *buf, int current_offset) {
    int last_offset = buf->offset - 1;
    int first_offset;
    int i;
    int min_offset;

    first_offset = child_offset(current_offset);
    min_offset = current_offset;

    for (i = 0; i <= 1; i++) {
        if ((first_offset + i) <= last_offset) {
            if (*(buf->data + min_offset) > *(buf->data + (first_offset + i))) {
                min_offset = first_offset + i;
            }
        }
    }

    if (min_offset != current_offset) {
        swap(buf->data + current_offset, buf->data + min_offset, sizeof(int));
        sink(buf, min_offset);
    }
}

void heap_from(int_buf *buf) {
    for (int current_offset = (buf->offset - 1) / 2; current_offset >= buf->start; current_offset--) {
        sink(buf, current_offset);
    }
}

void bubble(int_buf *buf, int current_offset) {
    if (parent_offset(current_offset) == -1) {
        return;
    }
    if (*(buf->data + parent_offset(current_offset)) > *(buf->data + current_offset)) {
        swap(buf->data + parent_offset(current_offset), buf->data + current_offset, sizeof(int));
        bubble(buf, parent_offset(current_offset));
    }

}

void insert(int_buf *buf, int data) {
    append(buf, data);
    bubble(buf, buf->offset - 1);
}

int delete_min(int_buf *buf) {
    int min = -1;
    if (buf->offset <= buf->start) {
        printf("buffer is empty!\n");
    }
    else {
        min = *(buf->data + buf->start);
        int last = *take_last(buf, 1);
        *(buf->data + buf->start) = last;
        sink(buf, 1);
    }
    return min;
}

int heap_empty(int_buf *buf) {
    if (buf->offset <= buf->start) {
        return 1;
    }
    else {
        return 0;
    }
}

int max_k_t(int_buf *buf, int current_offset, int threshold, int k_count, int t_value) {
    if (k_count >= threshold || current_offset > buf->offset - 1) {
        return k_count;
    }
    if (*(buf->data + current_offset) < t_value) {
        k_count = max_k_t(buf, child_offset(current_offset), threshold, k_count + 1, t_value);
        k_count = max_k_t(buf, child_offset(current_offset) + 1, threshold, k_count, t_value);
    }
    return k_count;
}