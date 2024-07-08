#include <stdio.h>
#define MAX_SIZE 20

struct int_queue {
    int out_offset;
    int in_offset;
    int underlying[MAX_SIZE + 1];
};

typedef struct int_queue int_queue;

int_queue *create_int_queue();
void enqueue(int_queue *queue, int data);
int dequeue(int_queue *queue);
int is_empty(int_queue *queue);