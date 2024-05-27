// Pop from accumulator queue -> write to file

#include "accumulator_queue.h"
#include "thread_manager.h"
#include "metrics_exporter.h"
#include "app_timer.h"
#include "watchdog_timer.h"

void *file_write_function() {
    extern int SUCCESS_EXIT;

    extern accumulator_queue_t accumulator_queue;
    extern thread_manager_t thread_manager;
    extern watchdog_timer_t watchdog_timer;

    pthread_mutex_lock(&thread_manager.file_write_thread->mutex);

    thread_manager.file_write_thread->can_run = 1;
    while (thread_manager.file_write_thread->can_run) {
        reset_timer(watchdog_timer.file_write_timer);
        write_metrics(&accumulator_queue);
        usleep((useconds_t)FILE_WRITE_SLEEP_TIME);
    }

    pthread_mutex_unlock(&thread_manager.file_write_thread->mutex);

    return (void *) &SUCCESS_EXIT;
}