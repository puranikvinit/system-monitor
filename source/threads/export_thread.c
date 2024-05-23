// Works independently of the accumulator and file write threads

// Read from file -> store in buffer -> open socket -> send HTTP response with `export_metrics`
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "thread_manager.h"
#include "metrics_exporter.h"
#include "socket_manager.h"

void *export_function() {
    int FAIL_EXIT = 1;
    int SUCCESS_EXIT = 0;
    
    extern thread_manager_t thread_manager;

    pthread_mutex_lock(&thread_manager.export_thread.mutex);

    thread_manager.export_thread.can_run = 1;
    while (thread_manager.export_thread.can_run) {
        FILE *file = fopen(ACCUMULATED_METRICS_FILE, "r");
        if (file == NULL) {
            perror("Error while opening the Accumulated Metrics file!\n");
            pthread_mutex_unlock(&thread_manager.export_thread.mutex);
            return (void *) &FAIL_EXIT;
        }
        // Move the file pointer to the end of the file
        fseek(file, 0, SEEK_END);
        
        // Get the current position of the file pointer
        long file_size = ftell(file);
        
        // Set the position to the start of the last 100 lines
        long position = file_size;
        int line_count = 0;
        while (position > 0 && line_count < 100) {
            fseek(file, --position, SEEK_SET);
            if (fgetc(file) == '\n') {
            line_count++;
            }
        }
        
        // Read and print the last 100 lines
        char line[256];
        char accumulated_metrics[25600] = "";
        while (fgets(line, sizeof(line), file) != NULL) {
            strcat(accumulated_metrics, line);
        }
        fclose(file);

        close_socket(open_socket(accumulated_metrics));

        usleep((useconds_t)EXPORT_SLEEP_TIME);
    }

    pthread_mutex_unlock(&thread_manager.export_thread.mutex);

    return (void *) &SUCCESS_EXIT;
}