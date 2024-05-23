#ifndef MONITOR_METRICS_H
#define MONITOR_METRICS_H

#include <stdio.h>

#include "stat_parser.h"

// Member APIs

/*! \brief calculates CPU usage */
void monitor_metrics(char* accumulated_metrics);

void _copy_stats(stat_struct_t *dest, stat_struct_t *src, size_t cpu_num);

#endif