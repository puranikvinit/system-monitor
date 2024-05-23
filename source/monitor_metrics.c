#include <stdlib.h>
#include <unistd.h>

#include "usage_calculator.h"
#include "monitor_metrics.h"
#include "metrics_exporter.h"

void monitor_metrics(stat_struct_t *current_stats, stat_struct_t *previous_stats, bool is_first_iteration, size_t stat_cpu_num, float *cpu_per_cs) {
        if (!read_proc_stat(current_stats)) {
            printf("ERROR: Failed to read /proc/stat\n");
            return EXIT_FAILURE; // Exit loop on failure
        }

        if (!is_first_iteration) {
            // Calculate CPU usage between the current and previous stats
            calculate_all_cpus(previous_stats, current_stats, stat_cpu_num, cpu_per_cs);
        }

        // Update previous stats for the next iteration
        _copy_stats(previous_stats, current_stats, stat_cpu_num);
}

void _copy_stats(stat_struct_t *dest, stat_struct_t *src, size_t cpu_num) {
    for (size_t i = 0; i < cpu_num; i++) {
        dest->cpu[i] = src->cpu[i];
    }
}