#ifndef CPU_ANALYSER_H
#define CPU_ANALYSER_H

#include <stdlib.h>

#include "stat_parser.h"

// Member APIs

/*! \brief calculates CPU usage
 *  \returns usage in percentage */
float calculate_cpu_use_per_c(cpu_struct_t prev_cpu, cpu_struct_t cur_cpu);

/*! \brief calculates CPU usage of all CPUs in `/proc/stat`; puts it on the logQueue
    \returns false if the cpuN changes between two consecutive reads */
bool calculate_all_cpus(stat_struct_t *prev_stat, stat_struct_t *cur_stat, size_t cpu_num, float *cpu_per_cs);

#endif
