// Monitor metrics -> record_metrics (push to accumulator queue)

#include "accumulator_queue.h"
#include "monitor_metrics.h"
#include "metrics_exporter.h"
#include "thread_manager.h"
#include "app_timer.h"
#include "watchdog_timer.h"

void *accumulator_function() {
    extern int FAIL_EXIT;
    extern int SUCCESS_EXIT;

    extern accumulator_queue_t accumulator_queue;
    extern thread_manager_t thread_manager;
    extern watchdog_timer_t watchdog_timer;

    pthread_mutex_lock(&thread_manager.accumulator_thread->mutex);

    size_t stat_cpu_num;
    if (!scan_proc_stat(&stat_cpu_num) || stat_cpu_num == 0) {
        printf("ERROR: Cannot scan /proc/stat\n");
        return (void *) &FAIL_EXIT;
    }

    // Allocate memory for CPU usage calculations
    float *cpu_per_cs = calloc(stat_cpu_num, sizeof(float));
    if (cpu_per_cs == NULL) {
        printf("ERROR: Memory allocation failed\n");
        return (void *) &FAIL_EXIT;
    }

    // Initialize structures for current and previous CPU stats
    stat_struct_t current_stats, previous_stats;
    current_stats.cpu = calloc(stat_cpu_num, sizeof(cpu_struct_t));
    previous_stats.cpu = calloc(stat_cpu_num, sizeof(cpu_struct_t));

    if (current_stats.cpu == NULL || previous_stats.cpu == NULL) {
        printf("ERROR: Memory allocation failed\n");
        free(cpu_per_cs);
        if (current_stats.cpu) free(current_stats.cpu);
        if (previous_stats.cpu) free(previous_stats.cpu);
        return (void *) &FAIL_EXIT;
    }

    bool first_iteration = true;

    thread_manager.accumulator_thread->can_run = 1;
    while (thread_manager.accumulator_thread->can_run) {
        reset_timer(watchdog_timer.accumulator_timer);
        monitor_metrics(&current_stats, &previous_stats, first_iteration, stat_cpu_num, cpu_per_cs);
        if(!first_iteration) record_metrics(cpu_per_cs, stat_cpu_num, &accumulator_queue);
        first_iteration = false;

        usleep((useconds_t)ACCUMULATOR_SLEEP_TIME);
    }

    // Clean up
    free(cpu_per_cs);
    free(current_stats.cpu);
    free(previous_stats.cpu);

    pthread_mutex_unlock(&thread_manager.accumulator_thread->mutex);

    return (void *) &SUCCESS_EXIT;
}