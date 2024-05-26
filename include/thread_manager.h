#ifndef MONITOR_THREADS_H
#define MONITOR_THREADS_H

#include <pthread.h>

// Define the Sleep Times for each thread (in us)
#define ACCUMULATOR_SLEEP_TIME 5000000 // 5s
#define EXPORT_SLEEP_TIME 100000 // 100ms
#define FILE_WRITE_SLEEP_TIME 5000000 // 5s
#define WATCHDOG_SLEEP_TIME 100000 // 100ms

#define THREAD_BUFFER_TIME 100000 // 100ms


/*! \brief Contains `pthread_t` objects and other flags required for thread execution */
typedef struct {
    pthread_t thread;
    pthread_mutex_t mutex;
    int can_run;
} thread_obj_t;

/*! \brief Contains the thread objects for all the threads required for the application */
typedef struct {
    thread_obj_t *accumulator_thread;
    thread_obj_t *export_thread;
    thread_obj_t *file_write_thread;
    thread_obj_t *watchdog_thread;
} thread_manager_t;


// Member APIs

void *accumulator_function();

void *file_write_function();

void *export_function();

void *watchdog_function();

#endif