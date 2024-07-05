#include <stddef.h>
#include <stdlib.h>
#include <string.h>
void swap(void *n1, void *n2, size_t n_size) {
    char *temp = malloc(n_size);
    memcpy(temp, n1, n_size);
    memcpy(n1, n2, n_size);
    memcpy(n2, temp, n_size);
    free(temp);
}