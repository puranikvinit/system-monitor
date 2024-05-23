#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "metrics_exporter.h"

void record_metrics(float *cpu_percs, size_t cpu_num, char* accumulated_metrics) {
    char usage_metrics[100000] = "";

    for (size_t i = 0; i < cpu_num; i++) {
        printf("CPU %zu Usage: %.2f%%\n", i, cpu_percs[i]);
        char current_cpu_usage[256];
        sprintf(current_cpu_usage, "CPU %zu Usage: %.2f%%\n", i, cpu_percs[i]);
        strcat(usage_metrics, current_cpu_usage);
    }
    strcat(accumulated_metrics, usage_metrics);
}

void export_metrics(int new_socket, char* usage_metrics) {
    char* http_response[100000];
    sprintf(http_response, "HTTP/1.1 200 OK\r\n" "Content-Type: text/plain\r\n" "Content-Length: %d \r\n" "\r\n%s", strlen(usage_metrics), usage_metrics);

    send(new_socket, http_response, strlen(http_response), 0);
}