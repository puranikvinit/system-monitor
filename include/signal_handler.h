#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "thread_manager.h"

// Member APIs
void handle_signal(int signal);

void kill_thread(thread_obj_t *thread);

#endif