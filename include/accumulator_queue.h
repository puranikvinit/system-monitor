#ifndef ACCUMULATOR_QUEUE_H
#define ACCUMULATOR_QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100000

/*! \brief Contains the queue of metrics into which accumulator thread adds the scraped metrics
        and the file write thread writes into a file. */
typedef struct {
    char* queue[MAX_QUEUE_SIZE];
    size_t front;
    size_t rear;
} accumulator_queue_t;

// Member APIs

/*! \brief Add an element of type `accumulator_queue_t` to the queue */
void enqueue(accumulator_queue_t* queue, char* str);

/*! \brief Remove an element of type `accumulator_queue_t` from the queue 
    \return the metrics string of the popped element */
char* dequeue(accumulator_queue_t* queue);

/*! \brief Check if the queue is empty 
    \return `true` if the queue is empty, else `false` */
bool isEmpty(accumulator_queue_t* queue);

/*! \brief Check if the queue is full 
    \return `true` if the queue is full, else `false` */
bool isFull(accumulator_queue_t* queue);

/*! \brief Get the size of the queue 
    \return the size of the queue */
size_t size(accumulator_queue_t* queue);

#endif