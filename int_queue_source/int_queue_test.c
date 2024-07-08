#include "./int_queue.h"
void test_queue() {
    /**original queue test was done with MAX_SIZE = 5*/
    int_queue *queue = create_int_queue();
    printf("state (in_offset, out_offset) when first created is (%d, %d)\n", queue->in_offset, queue->out_offset);
    enqueue(queue, 1);
    printf("state (in_offset, out_offset) after adding 1: (%d, %d)\n", queue->in_offset, queue->out_offset);
    enqueue(queue, 2);
    printf("state (in_offset, out_offset) after adding 2: (%d, %d)\n", queue->in_offset, queue->out_offset);
    enqueue(queue, 3);
    printf("state (in_offset, out_offset) after adding 3: (%d, %d)\n", queue->in_offset, queue->out_offset);
    enqueue(queue, 4);
    printf("state (in_offset, out_offset) after adding 4: (%d, %d)\n", queue->in_offset, queue->out_offset);
    enqueue(queue, 5);
    printf("state (in_offset, out_offset) after adding 5: (%d, %d)\n", queue->in_offset, queue->out_offset);
    
    enqueue(queue, 6);
    printf("state (in_offset, out_offset) after adding 6: (%d, %d)\n", queue->in_offset, queue->out_offset);
    
    int result0 = dequeue(queue);
    printf("result: %d, state (in_offset, out_offset) after removing 1st: (%d, %d)\n", result0, queue->in_offset, queue->out_offset);

    int result1 = dequeue(queue);
    printf("result: %d, state (in_offset, out_offset) after removing 2st: (%d, %d)\n", result1, queue->in_offset, queue->out_offset);

    enqueue(queue, 6);
    printf("state (in_offset, out_offset) after adding 6 again: (%d, %d)\n", queue->in_offset, queue->out_offset);
    enqueue(queue, 7);
    printf("state (in_offset, out_offset) after adding 7: (%d, %d)\n", queue->in_offset, queue->out_offset);

    while (!is_empty(queue)) {
        int result = dequeue(queue);
        printf("result: %d, state (in_offset, out_offset) after removing and element: (%d, %d)\n", result, queue->in_offset, queue->out_offset);
    }
    dequeue(queue);

}

int main(void) {
    test_queue();
}