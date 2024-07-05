#include "int_quick_sort.h"

int partition(int_buf *target, int start, int end) {
    int pivot_offset = end;
    int pivot_value = *(target->data + end);
    int cut_offset = start;
    for (int current_offset = start; current_offset < end; current_offset++) {
        int current = *(target->data + current_offset);
        if (current < pivot_value) {
            swap(target->data + cut_offset, target->data + current_offset, sizeof(int));
            cut_offset++;
        }
    }
    swap(target->data + cut_offset, target->data + pivot_offset, sizeof(int));
    return cut_offset;
}

void int_quick_sort(int_buf *target, int start, int end) {
    if (start < end) {
        int pivot_offset = partition(target, start, end);
        int_quick_sort(target, start, pivot_offset - 1);
        int_quick_sort(target, pivot_offset + 1, end);
    }
}