// Implement watchdog timer
#include <unistd.h>

#include "watchdog_timer.h"
#include "thread_manager.h"

void *watchdog_function() {
    extern int SUCCESS_EXIT;

    extern watchdog_timer_t watchdog_timer;
    extern thread_manager_t thread_manager;

    init_watchdog_timer(&watchdog_timer);

    pthread_mutex_lock(&thread_manager.watchdog_thread->mutex);

    thread_manager.watchdog_thread->can_run = 1;
    while (thread_manager.watchdog_thread->can_run) {
        int exceeded_thread = check_if_time_exceeded(&watchdog_timer, &thread_manager);
        if(exceeded_thread != -1) {
            pthread_cancel(thread_manager.accumulator_thread->thread);
            pthread_cancel(thread_manager.file_write_thread->thread);
            pthread_cancel(thread_manager.export_thread->thread);
        }
        
        usleep((useconds_t)WATCHDOG_SLEEP_TIME);
    }

    pthread_mutex_unlock(&thread_manager.watchdog_thread->mutex);

    return (void *) &SUCCESS_EXIT;
}
