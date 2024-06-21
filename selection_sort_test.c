#include <stddef.h>
#include <stdio.h>
int int_compare(void *i1, void *i2) {
    int *n1 = i1;
    int *n2 = i2;
    
    if (*n1 < *n2) {
        return -1;
    }
    else if (*n1 == *n2) {
        return 0;
    }
    else {
        return 1;
    }
}

int char_compare(void *i1, void *i2) {
    char *c1 = i1;
    char *c2 = i2;
    
    if (*c1 < *c2) {
        return -1;
    }
    else if (*c1 == *c2) {
        return 0;
    }
    else {
        return 1;
    }
}

void show_int(int *ns, int ns_length) {
    int last_idx = ns_length - 1;
    int ns_offset = 0;
    printf("[");
    while (ns_offset < last_idx) {
        printf("%d, ", *(ns + ns_offset));
        ns_offset++;
    }
    printf("%d]\n", *(ns + ns_offset));
}

void show_char(char *cs, int cs_length) {
    int last_idx = cs_length - 1;
    int cs_offset = 0;
    printf("[");
    while (cs_offset < last_idx) {
        printf("%c, ", *(cs + cs_offset));
        cs_offset++;
    }
    printf("%c]\n", *(cs + cs_offset));
}

void *selection_sort(void *ns, size_t n_size, int ns_length, int (*compare_to)(void *, void *));

int main(void) {
    int ns_length = 9;
    int ns[9] = {32, 8, 11, 1, 3, 5, 25, 9, 11};
    size_t n_size = sizeof(int);
    
    printf("before...\n");
    show_int(ns, ns_length);

    selection_sort(ns, n_size, ns_length, int_compare);

    printf("after...\n");
    show_int(ns, ns_length);

    int cs_length = 9;
    char cs[9] = {'z','a','m','t','c','v','x','b','c'};
    size_t c_size = sizeof(char);

    printf("before...\n");
    show_char(cs, cs_length);

    selection_sort(cs, c_size, cs_length, char_compare);

    printf("after...\n");
    show_char(cs, ns_length);
}