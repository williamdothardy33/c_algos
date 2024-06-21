#include <stddef.h>
void swap(void *n1, void *n2, size_t n_size);

void *selection_sort(void *ns, size_t n_size, int ns_length, int (*compare_to)(void *, void *)) {
    char *t = ns;
    int min_offset = 0;
    int start = 0;
    int last_idx = n_size * (ns_length - 1);
    int current_offset = start;

    while (start <= last_idx) {
        if (current_offset > last_idx) {
            if (min_offset == start) {
                start += n_size;
                min_offset = start;
                current_offset = min_offset;
            }
            else {
                swap((t + start), (t + min_offset), n_size);
                start += n_size;
                min_offset = start;
                current_offset = min_offset;
            }
        }
        else {
            int diff = compare_to((t + current_offset), (t + min_offset));
            if (diff < 0) {
                min_offset = current_offset;
                current_offset += n_size;                
            }
            else {
                current_offset += n_size;
            }
        }
    }
    return ns;
}