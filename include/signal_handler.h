#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "thread_manager.h"

// Member APIs

/*! \brief Handle the Termination signals received by the application's primary thread */
void handle_signal(int signal);

/*! \brief Kill the thread gracefully, avoiding potential memory leaks */
void kill_thread(thread_obj_t *thread);

#endif