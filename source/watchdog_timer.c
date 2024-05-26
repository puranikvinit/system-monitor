#include "watchdog_timer.h"
#include "thread_manager.h"

void init_watchdog_timer(watchdog_timer_t *watchdog_timer) {
    watchdog_timer->accumulator_timer = (app_timer_t *) malloc(sizeof(app_timer_t));
    watchdog_timer->export_timer = (app_timer_t *) malloc(sizeof(app_timer_t));
    watchdog_timer->file_write_timer = (app_timer_t *) malloc(sizeof(app_timer_t));

    init_timer(watchdog_timer->accumulator_timer);
    init_timer(watchdog_timer->export_timer);
    init_timer(watchdog_timer->file_write_timer);
}

int check_if_time_exceeded(watchdog_timer_t *watchdog_timer, thread_manager_t *thread_manager) {
    if(watchdog_timer->accumulator_timer->is_enabled && watchdog_timer->accumulator_timer->start_time >= (ACCUMULATOR_SLEEP_TIME/1000 + THREAD_BUFFER_TIME/1000) && thread_manager->accumulator_thread->can_run) return ACCUMULATOR_THREAD;
    if(watchdog_timer->file_write_timer->is_enabled && watchdog_timer->file_write_timer->start_time >= (FILE_WRITE_SLEEP_TIME/1000 + THREAD_BUFFER_TIME/1000) && thread_manager->file_write_thread->can_run) return FILE_WRITE_THREAD;
    if(watchdog_timer->export_timer->is_enabled && watchdog_timer->export_timer->start_time >= (EXPORT_SLEEP_TIME/1000 + THREAD_BUFFER_TIME/1000) && thread_manager->export_thread->can_run) return EXPORT_THREAD;
    
    return -1;
}