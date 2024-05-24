#include "app_timer.h"

static struct timespec time_spec;

time_t get_current_time() {
    // raw hard‐ware-based time that is not subject to NTP adjustments.
    clock_gettime(CLOCK_MONOTONIC_RAW, &time_spec);
    
    return (time_spec.tv_sec * 1000) + (time_spec.tv_nsec / 1000000);
}

void init_timer(app_timer_t *timer) {
    timer->start_time = get_current_time();
    timer->is_enabled = 1;
}

time_t get_passed_time(app_timer_t *timer) {
    if (!timer->is_enabled) {
        return 0;
    }
    return get_current_time() - timer->start_time;
}

void reset_timer(app_timer_t *timer) {
    timer->start_time = get_current_time();
}