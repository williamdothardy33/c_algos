#include "../int_buffer.h"

int parent_offset(int child_offset);
int child_offset(int parent_offset);
void sink(int_buf *buf, int current_offset);
void bubble(int_buf *buf, int current_offset);
void heap_from(int_buf *buf);
void insert(int_buf *buf, int data);
int delete_min(int_buf *buf);
int heap_empty(int_buf *buf);
void swap(void *n1, void *n2, size_t n_size);
int max_k_t(int_buf *buf, int current_offset, int threshold, int k_count, int t_value);