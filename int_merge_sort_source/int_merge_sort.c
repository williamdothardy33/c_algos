#include "int_merge_sort.h"
#include <stdlib.h>

void int_merge(int_buf *target, int start, int mid, int end) {
    int offset1 = start;
    int offset2 = mid + 1;
    int offset = start;
    int_buf *result = create_int_buf(0);

    while (offset1 <= mid || offset2 <= end) {
        if (offset1 > mid && offset2 <= end) {
            int next2 = *(target->data + offset2);
            append(result, next2);
            offset2++;

        }
        else if (offset2 > end && offset1 <= mid) {
            int next1 = *(target->data + offset1);
            append(result, next1);
            offset1++;
        }
        else {
            int next1 = *(target->data + offset1);
            int next2 = *(target->data + offset2);
            if (next1 <= next2) {
                append(result, next1);
                offset1++;
            }
            else {
                append(result, next2);
                offset2++;
            }

        }
    }
    while (offset <= end) {
        *(target->data + offset) = *(result->data + (offset - start));
        offset++;
    }
    free(result);
}

void int_merge_sort(int_buf *target, int start, int end) {
    if ((start < end)) {
        int mid = (start + end) / 2;
        int_merge_sort(target, start, mid);
        int_merge_sort(target, mid + 1, end);
        int_merge(target, start, mid, end);
    }
}