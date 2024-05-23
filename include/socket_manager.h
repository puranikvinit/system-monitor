#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

typedef struct {
    int server_fd;
    int new_socket;
} socket_manager_t;

// Member APIs

/*! \brief opens socket and binds it to the port 8080 of the localhost 
*   \returns `socket_manager_t` struct containing the opened sockets */
socket_manager_t open_socket(char* accumulated_metrics);

/*! \brief closes all the opened sockets */
void close_socket(socket_manager_t socket_list);

#endif