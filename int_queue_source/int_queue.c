#include "int_queue.h"
#include <stdlib.h>

int_queue *create_int_queue() {
    int_queue *queue = malloc(sizeof(int_queue));
    queue->in_offset = 1;
    queue->out_offset = -1;
    for (int i = 1; i <= MAX_SIZE; i++) {
        queue->underlying[i] = 0;
    }
    return queue;
}

void enqueue(int_queue *queue, int data) {
    if (queue->out_offset == -1 && queue->in_offset == 1) {
        queue->underlying[queue->in_offset] = data;
        queue->in_offset++;
        queue->out_offset = 1;
    }
    else if (queue->in_offset + 1 == queue->out_offset) {
            printf("warning queue is full!\n");
    }
    else if (queue->in_offset > MAX_SIZE) {
        if (queue->out_offset == 1) {
            printf("warning queue is full!\n");
        }
        else {
            queue->in_offset = 1;
            enqueue(queue, data);
        }
    }
    else {
        queue->underlying[queue->in_offset] = data;
        queue->in_offset++;
    }
}

int dequeue(int_queue *queue) {
    if (queue->out_offset == -1 && queue->in_offset == 1) {
        printf("warning queue is empty!\n");
        return -1;
    }
    else if (queue->out_offset + 1 == queue->in_offset) {
        int result = queue->underlying[queue->out_offset];
        queue->out_offset = -1;
        queue->in_offset = 1;
        return result;
    }
    else if (queue->out_offset > MAX_SIZE) {
        if (queue->in_offset == 1) {
            queue->out_offset = -1;
            printf("warning queue is empty!\n");
            return -1;
        }
        else {
            queue->out_offset = 1;
            return dequeue(queue);
        }
    }
    else {
        int result = queue->underlying[queue->out_offset];
        queue->out_offset ++;
        return result;
    }
}

int is_empty(int_queue *queue) {
    if (queue->out_offset == -1 && queue->in_offset == 1) {
        return 1;
    }
    else {
        return 0;
    }
}