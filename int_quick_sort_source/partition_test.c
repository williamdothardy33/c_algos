#include "int_quick_sort.h"
int main(void) {
    int_buf *target = create_int_buf(0);
    append(target, 8);
    append(target, 7);
    append(target, 6);
    append(target, 4);
    append(target, 3);
    append(target, 2);
    append(target, 1);
    append(target, 5);
    printf("before partitioning with pivot 5...\n");
    printf("\n");
    show_buf(target, 0);
    int pivot = partition(target, 0, 7);
    printf("\n");
    printf("after partition with pivot 5...\n");
    printf("pivot is now located at offset: %d\n", pivot);
    printf("\n");
    show_buf(target, 0);
}