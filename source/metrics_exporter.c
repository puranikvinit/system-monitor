#include "metrics_exporter.h"
#include "accumulator_queue.h"

void record_metrics(float *cpu_percs, size_t cpu_num, accumulator_queue_t *accumulator_queue) {
    char usage_metrics[100000] = "";

    for (size_t i = 0; i < cpu_num; i++) {
        // printf("CPU %zu Usage: %.2f%%\n", i, cpu_percs[i]);
        char current_cpu_usage[256];
        i == 0 ? sprintf(current_cpu_usage, "#TYPE overall_cpu_usage gauge\noverall_cpu_usage %.2f\n", cpu_percs[i])
            : sprintf(current_cpu_usage, "#TYPE cpu_%zu_usage gauge\ncpu_%zu_usage %.2f\n", i-1, i-1, cpu_percs[i]);
        strcat(usage_metrics, current_cpu_usage);
    }

    // enqueue(&accumulator_queue, usage_metrics);
    if (!isFull(accumulator_queue)) {
        enqueue(accumulator_queue, usage_metrics);
    } else {
        printf("ERROR: Accumulator queue is full!\n");
    }
}

void write_metrics(accumulator_queue_t *accumulator_queue) {
    // strcat(accumulated_metrics, usage_metrics);
    FILE *accumulated_metrics = NULL;
    if ((accumulated_metrics = fopen(ACCUMULATED_METRICS_FILE, "a")) == NULL) {
        accumulated_metrics = fopen(ACCUMULATED_METRICS_FILE, "w");
        // fprintf(accumulated_metrics, "%s", usage_metrics);
        while (!isEmpty(accumulator_queue)) {
            fprintf(accumulated_metrics, "%s", dequeue(accumulator_queue));
        }
        fclose(accumulated_metrics);
    } else {
        // fprintf(accumulated_metrics, "%s", usage_metrics);
        while (!isEmpty(accumulator_queue)) {
            char *dequeued_metrics = dequeue(accumulator_queue);
            fprintf(accumulated_metrics, "%s", dequeued_metrics);
            free(dequeued_metrics);
        }
        fclose(accumulated_metrics);
    }
}

void export_metrics(int new_socket, char* accumulator_metrics) {
    char http_response[100000];
    sprintf(http_response, "HTTP/1.1 200 OK\r\n" "Content-Type: text/plain; version=0.0.4\r\n" "Content-Length: %ld \r\n" "\r\n%s", strlen(accumulator_metrics), accumulator_metrics);

    send(new_socket, http_response, strlen(http_response), 0);
}