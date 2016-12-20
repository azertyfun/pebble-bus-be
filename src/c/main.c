#include "main.h"

void __assert (bool expression, char *file, int line) {
    if (!expression) {
        APP_LOG (APP_LOG_LEVEL_ERROR, "Assert failed at %s:%d", file, line);
        window_stack_pop_all (false);
    }
}

static void init (void) {
    ui_init ();
    comms_init ();
}

static void deinit (void) {
    ui_deinit ();
    comms_deinit ();
}

int main (void) {
    init ();
    app_event_loop ();
    deinit ();
}
