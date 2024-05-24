#ifndef APP_TIMER_H
#define APP_TIMER_H

#include <time.h>

typedef struct {
    time_t start_time;
    int is_enabled;
} app_timer_t;


// Member APIs

time_t get_current_time();

void init_timer(app_timer_t *timer);

time_t get_passed_time(app_timer_t *timer);

void reset_timer(app_timer_t *timer);

#endif