// Pop from accumulator queue -> write to file
#include <pthread.h>
#include <unistd.h>

#include "accumulator_queue.h"
#include "thread_manager.h"
#include "metrics_exporter.h"

void *file_write_function() {
    int FAIL_EXIT = 1;
    int SUCCESS_EXIT = 0;

    extern accumulator_queue_t accumulator_queue;
    extern thread_manager_t thread_manager;

    pthread_mutex_lock(&thread_manager.file_write_thread.mutex);

    thread_manager.file_write_thread.can_run = 1;
    while (thread_manager.file_write_thread.can_run) {
        write_metrics(&accumulator_queue);
        usleep((useconds_t)FILE_WRITE_SLEEP_TIME);
    }

    pthread_mutex_unlock(&thread_manager.file_write_thread.mutex);

    return (void *) &SUCCESS_EXIT;
}