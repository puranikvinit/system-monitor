#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "socket_manager.h"
#include "monitor_metrics.h"

int main() {
    char accumulated_metrics[100000] = ""; // Will use a file and read from it.
    socket_manager_t socket_list = open_socket(accumulated_metrics);

    monitor_metrics(accumulated_metrics);

    close_socket(socket_list);

    return EXIT_SUCCESS;
}
