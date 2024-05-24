#ifndef WATCHDOG_TIMER_H
#define WATCHDOG_TIMER_H

#include "app_timer.h"
#include "thread_manager.h"

enum thread_type {
    ACCUMULATOR_THREAD,
    FILE_WRITE_THREAD,
    EXPORT_THREAD
};

/*! \brief Contains the timers required for the watchdog thread */
typedef struct {
    app_timer_t *accumulator_timer;
    app_timer_t *file_write_timer;
    app_timer_t *export_timer;
} watchdog_timer_t;


// Member APIs

void init_watchdog_timer(watchdog_timer_t *watchdog_timer);

int check_if_time_exceeded(watchdog_timer_t *watchdog_timer, thread_manager_t *thread_manager);

#endif