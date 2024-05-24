#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "socket_manager.h"
#include "metrics_exporter.h"

#define PORT 8080

socket_manager_t open_socket() {
    int server_fd;

    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind socket to port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    socket_manager_t server_socket = {server_fd, address, addrlen};
    return server_socket;
}

void serve_client_request(socket_manager_t *server_socket, char* accumulated_metrics) {
    int new_socket;
    // Accept incoming connection
    if ((new_socket = accept(server_socket->server_socket_fd, (struct sockaddr *)&server_socket->address, (socklen_t*)&server_socket->addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    export_metrics(new_socket, accumulated_metrics);

    close(new_socket);
}

void close_socket(int server_socket_fd) {
    close(server_socket_fd);
}