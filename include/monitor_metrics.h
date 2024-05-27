#ifndef MONITOR_METRICS_H
#define MONITOR_METRICS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "stat_parser.h"

// Member APIs

/*! \brief calculates CPU usage 
    \return `0` if the metrics has been scraped and usage has been calculated appropriately, else `1` */
int monitor_metrics(stat_struct_t *current_stats, stat_struct_t *previous_stats, bool is_first_iteration, size_t stat_cpu_num, float *cpu_per_cs);

/*! \brief internal API; used to copy current stats into previous stats */
void _copy_stats(stat_struct_t *dest, stat_struct_t *src, size_t cpu_num);

#endif