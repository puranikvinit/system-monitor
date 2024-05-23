#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "thread_manager.h"
#include "socket_manager.h"
#include "monitor_metrics.h"
#include "accumulator_queue.h"

accumulator_queue_t accumulator_queue = { .front = 0, .rear = 0 };

thread_manager_t thread_manager;

int main() {
    thread_manager.accumulator_thread.can_run = 0;
    thread_manager.file_write_thread.can_run = 0;
    thread_manager.export_thread.can_run = 0;

    pthread_create(&thread_manager.accumulator_thread.thread, NULL, accumulator_function, NULL);
    pthread_create(&thread_manager.file_write_thread.thread, NULL, &file_write_function, NULL);
    pthread_create(&thread_manager.export_thread.thread, NULL, &export_function, NULL);

    printf("Threads created!\n");

    pthread_join(thread_manager.accumulator_thread.thread, NULL);
    pthread_join(thread_manager.file_write_thread.thread, NULL);
    pthread_join(thread_manager.export_thread.thread, NULL);

    printf("Threads joined, program ends!\n");

    return EXIT_SUCCESS;
}
