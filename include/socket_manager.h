#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/*! \brief contains all the details about the opened socket listening to client connections */
typedef struct {
    int server_socket_fd;
    struct sockaddr_in address;
    int addrlen;
} socket_manager_t;

// Member APIs

/*! \brief opens socket and binds it to the port 8080 of the host machine 
*   \returns `socket_manager_t` struct containing details about the opened socket */
socket_manager_t open_socket();

/*! \brief listens to the opened socket and accepts new connections to the socket */
void serve_client_request(socket_manager_t *server_socket, char* accumulated_metrics);

/*! \brief closes all the opened sockets */
void close_socket(int server_socket_fd);

#endif