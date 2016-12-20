#ifndef UI_H
#define UI_H

#include <@smallstoneapps/scroll-text-layer/scroll-text-layer.h>
#include <pebble.h>

#include "bus.h"

#define NUM_MENU_SECTIONS 1

void reload_stops ();
void ui_init ();
void ui_deinit ();

#endif
