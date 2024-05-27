#ifndef METRICS_EXPORTER_H
#define METRICS_EXPORTER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#include "accumulator_queue.h"

#define ACCUMULATED_METRICS_FILE "./accumulated_metrics.txt"

// Member APIs

/*! \brief Record the CPU usage metrics into the accumulator queue */
void record_metrics(float *cpu_percs, size_t cpu_num, accumulator_queue_t *accumulator_queue);

/*! \brief Write the metrics from the accumulator queue to a file */
void write_metrics(accumulator_queue_t *accumulator_queue);

/*! \brief exports usage metrics to the opened socket by the `socket_manager` */
void export_metrics(int new_socket, char* accumulated_metrics);

#endif
