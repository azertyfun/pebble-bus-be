#ifndef LIST_SELECTION_WINDOW_H
#define LIST_SELECTION_WINDOW_H

#include <pebble.h>

#include "bus.h"

#define NUM_MENU_SECTIONS 1

void list_selection_window_init (Bus_stop* stop);
void list_selection_window_deinit ();

#endif
