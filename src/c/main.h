#ifndef MAIN_H
#define MAIN_H

#include <@smallstoneapps/scroll-text-layer/scroll-text-layer.h>
#include <pebble.h>

#define NUM_MENU_SECTIONS 1

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

void __assert (bool expression, char *file, int line);

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


static unsigned int n_bus_stops = 0;
static Bus_stop **bus_stops = NULL;

static Window *s_window, *s_window_time;
static MenuLayer *s_menu_layer;
static ScrollTextLayer *s_text_layer;
static char *time_s;

static bool began = false, geoloc_done = false, data_received = false;

#endif
