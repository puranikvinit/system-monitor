#include "accumulator_queue.h"

void enqueue(accumulator_queue_t* queue, char* str) {
    if (queue->rear == MAX_QUEUE_SIZE) {
        return; // Queue is full
    }
    queue->queue[queue->rear] = strdup(str);
    queue->rear++;
}

char* dequeue(accumulator_queue_t* queue) {
    if (queue->front == queue->rear) {
        return NULL; // Queue is empty
    }
    char* str = queue->queue[queue->front];
    queue->front++;
    return str;
}

bool isEmpty(accumulator_queue_t* queue) {
    return queue->front == queue->rear;
}

bool isFull(accumulator_queue_t* queue) {
    return queue->rear == MAX_QUEUE_SIZE;
}

size_t size(accumulator_queue_t* queue) {
    return queue->rear - queue->front;
}