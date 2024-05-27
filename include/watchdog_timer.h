#ifndef WATCHDOG_TIMER_H
#define WATCHDOG_TIMER_H

#include <stdlib.h>
#include <stdio.h>

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

/*! \brief Initialize the watchdog timer with the current time, and enable the timer */
void init_watchdog_timer(watchdog_timer_t *watchdog_timer);

/*! \brief Check if the time has exceeded the threshold for any of the threads
    \return the thread index that has exceeded the time threshold, `-1` if none of the threads
        exceeded the time threshold */
int check_if_time_exceeded(watchdog_timer_t *watchdog_timer, thread_manager_t *thread_manager);

// NOTE: The export thread is not used in the current implementation, as the `accept()` function 
//      blocks the thread function execution untill an incoming connection is received. Hence, the
//      export thread is not required to be monitored by the watchdog timer.

#endif