#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "thread_manager.h"
#include "socket_manager.h"
#include "monitor_metrics.h"
#include "accumulator_queue.h"
#include "watchdog_timer.h"

#include "signal_handler.h"

accumulator_queue_t accumulator_queue = { .front = 0, .rear = 0 };

thread_manager_t thread_manager;
watchdog_timer_t watchdog_timer;

int FAIL_EXIT = 1;
int SUCCESS_EXIT = 0;

int main() {
    signal(SIGINT, handle_signal);
    
    thread_manager.accumulator_thread = malloc(sizeof(thread_obj_t));
    thread_manager.file_write_thread = malloc(sizeof(thread_obj_t));
    thread_manager.export_thread = malloc(sizeof(thread_obj_t));
    thread_manager.watchdog_thread = malloc(sizeof(thread_obj_t));
    
    thread_manager.accumulator_thread->can_run = 0;
    thread_manager.file_write_thread->can_run = 0;
    thread_manager.export_thread->can_run = 0;
    thread_manager.watchdog_thread->can_run = 0;

    pthread_create(&thread_manager.accumulator_thread->thread, NULL, &accumulator_function, NULL);
    pthread_create(&thread_manager.file_write_thread->thread, NULL, &file_write_function, NULL);
    pthread_create(&thread_manager.export_thread->thread, NULL, &export_function, NULL);
    pthread_create(&thread_manager.watchdog_thread->thread, NULL, &watchdog_function, NULL);

    printf("Threads created!\n");

    pthread_join(thread_manager.accumulator_thread->thread, NULL);
    pthread_join(thread_manager.file_write_thread->thread, NULL);
    pthread_join(thread_manager.export_thread-> thread, NULL);
    pthread_join(thread_manager.watchdog_thread->thread, NULL);

    printf("Threads joined, program ends!\n");

    free(thread_manager.watchdog_thread);
    free(thread_manager.export_thread);
    free(thread_manager.file_write_thread);
    free(thread_manager.accumulator_thread);

    return EXIT_SUCCESS;
}
