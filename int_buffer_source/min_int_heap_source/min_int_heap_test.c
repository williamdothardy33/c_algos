#include "min_int_heap.h"
int main(void) {
    int_buf *buf = create_int_buf(1);
    append(buf, 16);
    append(buf, 8);
    append(buf, 7);
    append(buf, 9);
    append(buf, 11);
    append(buf, 4);
    append(buf, 3);
    append(buf, 2);
    append(buf, 1);
    heap_from(buf);
    show_buf(buf, 1);
    printf("\n");

    int max_4_8 = max_k_t(buf, buf->start, 4, 0, 8);

    printf("8 is bigger than %d elements in the heap counting a maximum of 4 elements\n", max_4_8);
    /*while(!(heap_empty(buf))) {
        int min = delete_min(buf);
        printf("the current min is: %d\n", min);
    }*/
}