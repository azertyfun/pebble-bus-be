#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <pebble.h>

#include "bus.h"
#include "list_selection_window.h"

#define NUM_MENU_SECTIONS 1

void reload_stops ();
void main_window_init ();
void main_window_deinit ();

#endif
