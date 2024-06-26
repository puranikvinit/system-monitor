#ifndef MONITOR_THREADS_H
#define MONITOR_THREADS_H

#include <pthread.h>
#include <unistd.h>

// Define the Sleep Times for each thread (in us)
#define ACCUMULATOR_SLEEP_TIME 5000000 // 5s
#define EXPORT_SLEEP_TIME 100000 // 100ms
#define FILE_WRITE_SLEEP_TIME 5000000 // 5s
#define WATCHDOG_SLEEP_TIME 100000 // 100ms

// Additional buffer time to allow completion of clean up operations
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

/*! \brief Thread function for the accumulator thread */
void *accumulator_function();

/*! \brief Thread function for the file write thread */
void *file_write_function();

/*! \brief Thread function for the export thread */
void *export_function();

/*! \brief Thread function for the watchdog timer thread */
void *watchdog_function();

#endif