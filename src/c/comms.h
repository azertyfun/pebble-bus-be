#ifndef COMMS_H
#define COMMS_H

#include <pebble.h>

#include "bus.h"

#define MESSAGE_KEY_MESSAGE 0
#define MESSAGE_KEY_ADD_STOP 1
#define MESSAGE_KEY_ADD_STOP_NAME 2
#define MESSAGE_KEY_ADD_STOP_N_LINES 3
#define MESSAGE_KEY_ADD_STOP_LINES_S 4
#define MESSAGE_KEY_ADD_LINE 5
#define MESSAGE_KEY_ADD_LINE_STOP 6
#define MESSAGE_KEY_ADD_STOP_LINE_NEXT 7
#define MESSAGE_KEY_ADD_STOP_LINE_SECOND_NEXT 8

#define assert(x)                           \
    do {                                    \
        __assert ((x), __FILE__, __LINE__); \
    } while (0);

extern bool began, geoloc_done, data_received;

extern void __assert (bool expression, char *file, int line);

void comms_init ();
void comms_deinit ();

#endif
