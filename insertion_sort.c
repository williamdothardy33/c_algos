#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void *insertion_sort(void *ns, size_t n_size, int ns_length, int (*compare_to)(void *, void *)) {
    char *t = ns;
    size_t last_idx = n_size * (ns_length - 1);
    size_t current_offset = n_size;
    size_t previous_offset = 0;
    char *current = malloc(n_size);
    memcpy(current, (t + current_offset), n_size);

    while (current_offset <= last_idx) {
        char *previous = t + previous_offset;
        int diff = compare_to(previous, current);
        if (diff <= 0) {
            memcpy((previous + n_size), current, n_size);
            previous_offset = current_offset;
            current_offset += n_size;
            if (current_offset <=last_idx) {
                memcpy(current, (t + current_offset), n_size);
            }
        }
        else {
            if (previous_offset == 0) {
                memcpy((previous + n_size), previous, n_size);
                memcpy(previous, current, n_size);
                previous_offset = current_offset;
                current_offset += n_size;
                if (current_offset <=last_idx) {
                    memcpy(current, (t + current_offset), n_size);
                }          
            }
            else {
                memcpy((previous + n_size), previous, n_size);
                previous_offset -= n_size;
            }
        }
        
        
    }

    free(current);
    return ns;
}