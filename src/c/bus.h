#ifndef BUS_H
#define BUS_H

#include <pebble.h>

#include "comms.h"

typedef struct {
    bool loaded;

    char *name;
    time_t next_bus;
    time_t second_next_bus;
} Bus_line;

typedef struct {
    char *name;
    char *id;
    char *lines_s;

    unsigned int n_lines;
    Bus_line **lines;
} Bus_stop;

extern unsigned int n_bus_stops;
extern Bus_stop **bus_stops;

#include "main_window.h"

#endif
