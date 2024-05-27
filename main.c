#include "thread_manager.h"
#include "socket_manager.h"
#include "monitor_metrics.h"
#include "accumulator_queue.h"
#include "watchdog_timer.h"

#include "signal_handler.h"

accumulator_queue_t accumulator_queue = { .front = 0, .rear = 0 };

thread_manager_t thread_manager;
watchdog_timer_t watchdog_timer;

// Exit code if the thread function fails
int FAIL_EXIT = 1;
// Exit code if the thread function succeeds
int SUCCESS_EXIT = 0;

int main() {
    // Register the signal handler for `SIGINT`
    signal(SIGINT, handle_signal);
    
    // Allocate memory for the threads
    thread_manager.accumulator_thread = malloc(sizeof(thread_obj_t));
    thread_manager.file_write_thread = malloc(sizeof(thread_obj_t));
    thread_manager.export_thread = malloc(sizeof(thread_obj_t));
    thread_manager.watchdog_thread = malloc(sizeof(thread_obj_t));
    
    // Initialize the thread objects
    thread_manager.accumulator_thread->can_run = 0;
    thread_manager.file_write_thread->can_run = 0;
    thread_manager.export_thread->can_run = 0;
    thread_manager.watchdog_thread->can_run = 0;

    // Initialize the watchdog timers
    init_watchdog_timer(&watchdog_timer);

    // Initialize the mutexes
    pthread_mutex_init(&thread_manager.accumulator_thread->mutex, NULL);
    pthread_mutex_init(&thread_manager.file_write_thread->mutex, NULL);
    pthread_mutex_init(&thread_manager.export_thread->mutex, NULL);
    pthread_mutex_init(&thread_manager.watchdog_thread->mutex, NULL);

    // Create the threads
    pthread_create(&thread_manager.accumulator_thread->thread, NULL, &accumulator_function, NULL);
    pthread_create(&thread_manager.file_write_thread->thread, NULL, &file_write_function, NULL);
    pthread_create(&thread_manager.export_thread->thread, NULL, &export_function, NULL);
    pthread_create(&thread_manager.watchdog_thread->thread, NULL, &watchdog_function, NULL);

    printf("Threads created!\n");

    // Join the threads
    pthread_join(thread_manager.accumulator_thread->thread, NULL);
    pthread_join(thread_manager.file_write_thread->thread, NULL);
    pthread_join(thread_manager.export_thread-> thread, NULL);
    pthread_join(thread_manager.watchdog_thread->thread, NULL);

    printf("Threads joined, program ends!\n");

    // Free the memory allocated for the threads
    free(thread_manager.watchdog_thread);
    free(thread_manager.export_thread);
    free(thread_manager.file_write_thread);
    free(thread_manager.accumulator_thread);

    return EXIT_SUCCESS;
}
