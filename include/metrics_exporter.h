#ifndef METRICS_EXPORTER_H
#define METRICS_EXPORTER_H


// Member APIs

void record_metrics(float *cpu_percs, size_t cpu_num, char* accumulated_metrics);

/*! \brief exports usage metrics to the opened socket by the socket_manager */
void export_metrics(int new_socket, char* accumulated_metrics);

#endif
