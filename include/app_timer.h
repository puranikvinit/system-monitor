#ifndef APP_TIMER_H
#define APP_TIMER_H

#include <time.h>

/*! \brief Contains the timer that is used to calculate the time passed since the timer was initialized */
typedef struct {
    time_t start_time;
    int is_enabled;
} app_timer_t;


// Member APIs

/*! \brief Calculate the current time in seconds since the UNIX Epoch
    \return the calculated time in seconds */
time_t get_current_time();

/*! \brief Initialize the timer with the current time, and enable the timer */
void init_timer(app_timer_t *timer);

/*! \brief Get the time passed since the timer was initialized
    \return the calculated time */
time_t get_passed_time(app_timer_t *timer);

/*! \brief Reset the timer with the current time,
        typically to be used after every loop of the thread function */
void reset_timer(app_timer_t *timer);

#endif