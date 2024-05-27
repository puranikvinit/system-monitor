#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

typedef struct {
    int server_socket_fd;
    struct sockaddr_in address;
    int addrlen;
} socket_manager_t;

// Member APIs

/*! \brief opens socket and binds it to the port 8080 of the localhost 
*   \returns `socket_manager_t` struct containing the opened sockets */
socket_manager_t open_socket();

void serve_client_request(socket_manager_t *server_socket, char* accumulated_metrics);

/*! \brief closes all the opened sockets */
void close_socket(int server_socket_fd);

#endif