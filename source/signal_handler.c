#include "signal_handler.h"
#include "watchdog_timer.h"

void handle_signal(int signal) {
    extern thread_manager_t thread_manager;

    switch (signal) {
        case SIGINT:
            kill_thread(thread_manager.watchdog_thread);
            break;

        default:
            break;
    }

    printf("Gracefully exiting...\n");
}

void kill_thread(thread_obj_t *thread) {
    extern watchdog_timer_t watchdog_timer;

    thread->can_run = 0;
    while(pthread_mutex_lock(&thread->mutex) != 0) {
        // Wait for the mutex to be unlocked
        usleep(THREAD_BUFFER_TIME);
    }
    
    pthread_cancel(thread->thread);

    free(watchdog_timer.accumulator_timer);
    free(watchdog_timer.export_timer);
    free(watchdog_timer.file_write_timer);
}