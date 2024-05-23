#ifndef MONITOR_METRICS_H
#define MONITOR_METRICS_H

#include <stdio.h>

#include "stat_parser.h"

// Member APIs

/*! \brief calculates CPU usage */
void monitor_metrics(stat_struct_t *current_stats, stat_struct_t *previous_stats, bool is_first_iteration, size_t stat_cpu_num, float *cpu_per_cs);

void _copy_stats(stat_struct_t *dest, stat_struct_t *src, size_t cpu_num);

#endif