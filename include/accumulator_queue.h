#ifndef ACCUMULATOR_QUEUE_H
#define ACCUMULATOR_QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    char* queue[MAX_QUEUE_SIZE];
    size_t front;
    size_t rear;
} accumulator_queue_t;

// Member APIs

void enqueue(accumulator_queue_t* queue, char* str);

char* dequeue(accumulator_queue_t* queue);

bool isEmpty(accumulator_queue_t* queue);

bool isFull(accumulator_queue_t* queue);

size_t size(accumulator_queue_t* queue);

#endif