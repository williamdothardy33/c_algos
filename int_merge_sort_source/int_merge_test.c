#include "int_merge_sort.h"

int main(void) {
    int_buf *ns = create_int_buf(0);
    //[1,7,8,10,13,2,3,4,6,8,9]
    append(ns, 1);
    append(ns, 7);
    append(ns, 8);
    append(ns, 10);
    append(ns, 13);
    append(ns, 2);
    append(ns, 3);
    append(ns, 4);
    append(ns, 6);
    append(ns, 8);
    append(ns, 9);
    show_buf(ns, 0);
    printf("\n");
    int_merge(ns, 0, 4, 10);
    show_buf(ns, 0);

}