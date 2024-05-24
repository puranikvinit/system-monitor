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
    extern int SUCCESS_EXIT;
    
    extern thread_manager_t thread_manager;

    pthread_mutex_lock(&thread_manager.export_thread->mutex);

    thread_manager.export_thread->can_run = 1;
    socket_manager_t server_socket_fd = open_socket();
    while (thread_manager.export_thread->can_run) {
        FILE *file = fopen(ACCUMULATED_METRICS_FILE, "r");
        if (file == NULL) {
            // perror("Error while opening the Accumulated Metrics file!\n");
            // pthread_mutex_unlock(&thread_manager.export_thread.mutex);
            // return (void *) &FAIL_EXIT;
            printf("Waiting for the metrics to be recorded...\n");

            // TODO: ADD COMMENT TO JUSTIFY
            usleep((useconds_t)(EXPORT_SLEEP_TIME + FILE_WRITE_SLEEP_TIME));
            continue;
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

        // Move the file pointer behind by 1 character, as `fgetc`
        // auto-increments the file pointer ahead by 1 character
        fseek(file, -1, SEEK_CUR);
        
        // Read and print the last 100 lines
        char line[256];
        char accumulated_metrics[25600] = "";
        while (fgets(line, sizeof(line), file) != NULL) {
            strcat(accumulated_metrics, line);
        }
        fclose(file);

        serve_client_request(&server_socket_fd, accumulated_metrics);

        usleep((useconds_t)EXPORT_SLEEP_TIME);
    }

    close(server_socket_fd.server_socket_fd);
    pthread_mutex_unlock(&thread_manager.export_thread->mutex);

    return (void *) &SUCCESS_EXIT;
}