#ifndef STAT_STRUCT_H
#define STAT_STRUCT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*! \brief Contains data aquired when reading the cpuN data from `/proc/stat`*/
typedef struct {
    // Units in USER_HZ

    // Total time spent by user mode processes
    unsigned long long int user;

    // Total time spent by niced user mode processes
    unsigned long long int nice;

    // Total time spent by system mode processes
    unsigned long long int system;

    // Total time spent by idle processes
    unsigned long long int idle;

    // Total time spent waiting for I/O to complete
    unsigned long long int io_wait;

    // Total time spent servicing hardware interrupts
    unsigned long long int irq;

    // Total time spent servicing software interrupts
    unsigned long long int soft_irq;

    // Total time spent in other Operating Systems when running in a virtualized environment
    unsigned long long int steal;

    // Total time spent running a virtual CPU for guest Operating Systems
    unsigned long long int guest;

    // Total time spent running a niced guest operating system
    unsigned long long int guest_nice;
} cpu_struct_t;


/*! \brief Contains data from a whole reading of `/proc/stat` file*/
typedef struct {
    // time_t sampleTimeMS;
    size_t cpu_num;
    cpu_struct_t *cpu;
} stat_struct_t;


// Member APIs

/*! \brief Scans the contents of `/proc/stat` to determine number of CPUs 
    \return `true` if successfully calculated number of CPU cores, else `false` */
bool scan_proc_stat(size_t *cpu_num);

/*! \brief Reads the most important contents of the `/proc/stat` file
    \return `true` if successfully scraped metrics from `/proc/stat`, else `false` */
bool read_proc_stat(stat_struct_t *stat);

/*! \brief internal API; prints the contents of `stat_struct_t` to the terminal, for debugging */
void _print_proc_stat(stat_struct_t *stat);

#endif
