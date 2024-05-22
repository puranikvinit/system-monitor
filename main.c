#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "usage_calculator.h"

void copy_stats(stat_struct_t *dest, stat_struct_t *src, size_t cpu_num) {
    for (size_t i = 0; i < cpu_num; i++) {
        dest->cpu[i] = src->cpu[i];
    }
}

void print_cpu_usage(float *cpu_percs, size_t cpu_num) {
    for (size_t i = 0; i < cpu_num; i++) {
        printf("CPU %zu Usage: %.2f%%\n", i, cpu_percs[i]);
    }
}


int main() {
    size_t stat_cpu_num;
    if (!scan_proc_stat(&stat_cpu_num) || stat_cpu_num == 0) {
        printf("ERROR: Cannot scan /proc/stat\n");
        return EXIT_FAILURE;
    }

    // Allocate memory for CPU usage calculations
    float *cpu_per_cs = calloc(stat_cpu_num, sizeof(float));
    if (cpu_per_cs == NULL) {
        printf("ERROR: Memory allocation failed\n");
        return EXIT_FAILURE;
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
        return EXIT_FAILURE;
    }

    bool first_iteration = true;

    while (true) { // Main loop
        if (!read_proc_stat(&current_stats)) {
            printf("ERROR: Failed to read /proc/stat\n");
            break; // Exit loop on failure
        }

        if (!first_iteration) {
            // Calculate CPU usage between the current and previous stats
            calculate_all_cpus(&previous_stats, &current_stats, stat_cpu_num, cpu_per_cs);
            // Print the calculated CPU usages
            print_cpu_usage(cpu_per_cs, stat_cpu_num);
        } else {
            first_iteration = false;
        }

        // Update previous stats for the next iteration
        copy_stats(&previous_stats, &current_stats, stat_cpu_num);

        // Simulated delay to match the original threaded behavior
        sleep(1);
    }

    // Clean up
    free(cpu_per_cs);
    free(current_stats.cpu);
    free(previous_stats.cpu);

    return EXIT_SUCCESS;
}
