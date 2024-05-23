#ifndef METRICS_EXPORTER_H
#define METRICS_EXPORTER_H

#include "accumulator_queue.h"

#define ACCUMULATED_METRICS_FILE "./accumulated_metrics.txt"

// Member APIs

void record_metrics(float *cpu_percs, size_t cpu_num, accumulator_queue_t *accumulator_queue);

void write_metrics(accumulator_queue_t *accumulator_queue);

/*! \brief exports usage metrics to the opened socket by the socket_manager */
void export_metrics(int new_socket, char* accumulated_metrics);

#endif
