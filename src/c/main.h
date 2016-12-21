#ifndef MAIN_H
#define MAIN_H

#include <pebble.h>

#include "bus.h"
#include "comms.h"
#include "main_window.h"

#define assert(x)                           \
    do {                                    \
        __assert ((x), __FILE__, __LINE__); \
    } while (0);

extern void __assert (bool expression, char *file, int line);

#endif
