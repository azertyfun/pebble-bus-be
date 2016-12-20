#include "main.h"

void __assert (bool expression, char *file, int line) {
    if (!expression) {
        APP_LOG (APP_LOG_LEVEL_ERROR, "Assert failed at %s:%d", file, line);
        window_stack_pop_all (false);
    }
}

/*
 * Layout
 */

static void window_time_unload (Window *window) {
    free (time_s);
}

static uint16_t menu_get_num_sections_callback (MenuLayer *menu_layer, void *data) {
    return NUM_MENU_SECTIONS;
}

static uint16_t menu_get_num_rows_callback (MenuLayer *menu_layer, uint16_t section_index, void *data) {
    switch (section_index) {
        case 0:
            return n_bus_stops == 0 ? 1 : n_bus_stops;
        default:
            return 0;
    }
}

static int16_t menu_get_header_height_callback (MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback (GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    switch (section_index) {
        case 0:
            menu_cell_basic_header_draw (ctx, cell_layer, "Select bus stop");
            break;
    }
}

static void menu_draw_row_callback (GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
    // Determine which section we're going to draw in
    switch (cell_index->section) {
        case 0:
            if (!began) {
                menu_cell_basic_draw (ctx, cell_layer, "Loading", "Waiting for BT connection...", NULL);
            } else if (!geoloc_done) {
                menu_cell_basic_draw (ctx, cell_layer, "Loading", "Waiting for localization from the phone...", NULL);
            } else if (!data_received) {
                menu_cell_basic_draw (ctx, cell_layer, "Loading", "Waiting for data...", NULL);
            } else if (cell_index->row == 0 && n_bus_stops == 0) {
                menu_cell_basic_draw (ctx, cell_layer, "None", "No bus stops nearby", NULL);
            } else {
                menu_cell_basic_draw (ctx, cell_layer, bus_stops[cell_index->row]->name, bus_stops[cell_index->row]->lines_s, NULL);
            }
            break;
    }
}

static void menu_select_callback (MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
    if (n_bus_stops == 0)
        return;

    /* s_window_time = window_create ();

    window_set_window_handlers (s_window_time, (WindowHandlers){
                                               .load = NULL,
                                               .appear = NULL,
                                               .disappear = NULL,
                                               .unload = window_time_unload,
                                               });

    s_text_layer = scroll_text_layer_create_fullscreen (s_window_time);
    scroll_text_layer_set_system_font (s_text_layer, FONT_KEY_GOTHIC_18);

    char *time1 = malloc (8);
    char *time2 = malloc (8);
    char *time_left = malloc (16);
    if (bus_stops[cell_index->row]->next_bus != 0) {
        strftime (time1, 7, "%H:%M",
                  localtime (&bus_stops[cell_index->row]->next_bus));

        int t = bus_stops[cell_index->row]->next_bus - time (NULL);
        APP_LOG (APP_LOG_LEVEL_DEBUG, "%d (%u - %u)", t,
                 (unsigned int)bus_stops[cell_index->row]->next_bus,
                 (unsigned int)time (NULL));
        snprintf (time_left, 16, "%02d:%02d", t / 60, t % 60);

        if (bus_stops[cell_index->row]->second_next_bus != 0) {
            strftime (time2, 7, "%H:%M",
                      localtime (&bus_stops[cell_index->row]->second_next_bus));
        } else {
            strcpy (time2, "Unknown");
        }
    } else {
        strcpy (time1, "Unknown");
        strcpy (time_left, "--");
    }

    time_s = malloc (256);
    strcpy (time_s, "Stop: ");
    strcat (time_s, bus_stops[cell_index->row]->name);
    strcat (time_s, "\nLine: ");
    strcat (time_s, bus_stops[cell_index->row]->line);
    strcat (time_s, "\n\n");
    strcat (time_s, "Next: ");
    strcat (time_s, time1);
    strcat (time_s, ", ");
    strcat (time_s, time2);
    strcat (time_s, " (");
    strcat (time_s, time_left);
    strcat (time_s, " remaining).");
    scroll_text_layer_set_text (s_text_layer, time_s);

    free (time_left);
    free (time1);
    free (time2);

    scroll_text_layer_add_to_window (s_text_layer, s_window_time);
    window_stack_push (s_window_time, true); */
}

static void createWindow () {
    Layer *window_layer = window_get_root_layer (s_window);
    GRect bounds = layer_get_frame (window_layer);

    s_menu_layer = menu_layer_create (bounds);
    menu_layer_set_click_config_onto_window (s_menu_layer, s_window);
    menu_layer_set_callbacks (s_menu_layer, NULL, (MenuLayerCallbacks){
                                                  .get_num_sections = menu_get_num_sections_callback, .get_num_rows = menu_get_num_rows_callback, .get_header_height = menu_get_header_height_callback, .draw_header = menu_draw_header_callback, .draw_row = menu_draw_row_callback, .select_click = menu_select_callback,
                                                  });
    menu_layer_set_click_config_onto_window (s_menu_layer, s_window);
    layer_add_child (window_layer, menu_layer_get_layer (s_menu_layer));

    window_stack_push (s_window, true);
}

/*
 * App Messages
 */

static void inbox_received_callback (DictionaryIterator *iterator, void *context) {
    APP_LOG (APP_LOG_LEVEL_DEBUG, "Received a message of %lu bytes", (unsigned long)dict_size (iterator));

    DictionaryIterator *iter;
    Tuple *tuple = dict_read_first (iterator);

    while (tuple) {
        switch (tuple->key) {
            case MESSAGE_KEY_MESSAGE:

                if (strcmp (tuple->value->cstring, "BEGIN") == 0) {
                    if (app_message_outbox_begin (&iter) != APP_MSG_OK) {
                        APP_LOG (APP_LOG_LEVEL_DEBUG, "Could not begin message");
                    }

                    if (dict_write_cstring (iter, MESSAGE_KEY_MESSAGE, "GET_STOPS") != DICT_OK) {
                        APP_LOG (APP_LOG_LEVEL_DEBUG, "Could not write message");
                    }

                    app_message_outbox_send ();

                    began = true;
                    menu_layer_reload_data (s_menu_layer);
                } else if (strcmp (tuple->value->cstring, "GEOLOC_DONE") == 0) {
                    geoloc_done = true;
                    menu_layer_reload_data (s_menu_layer);
                } else if (strcmp (tuple->value->cstring, "DATA_RECEIVED") == 0) {
                    data_received = true;
                    menu_layer_reload_data (s_menu_layer);
                } else {
                    APP_LOG (APP_LOG_LEVEL_DEBUG, "Error: received unknown message key '%s'", tuple->value->cstring);
                }

                break;
            case MESSAGE_KEY_ADD_STOP: {
                Tuple *name = dict_find (iterator, MESSAGE_KEY_ADD_STOP_NAME);
                Tuple *n_lines = dict_find (iterator, MESSAGE_KEY_ADD_STOP_N_LINES);
                Tuple *lines_s = dict_find (iterator, MESSAGE_KEY_ADD_STOP_LINES_S);
                assert (name != NULL);
                assert (n_lines != NULL);
                assert (lines_s != NULL);

                Bus_stop *stop = malloc (sizeof (Bus_stop));
                APP_LOG (APP_LOG_LEVEL_DEBUG, "Stop: %x", (unsigned int)stop);

                stop->id = malloc (tuple->length);
                strcpy (stop->id, tuple->value->cstring);
                stop->name = malloc (name->length);
                strcpy (stop->name, name->value->cstring);
                stop->lines_s = malloc (lines_s->length);
                strcpy (stop->lines_s, lines_s->value->cstring);

                stop->n_lines = n_lines->value->uint32;
                APP_LOG (APP_LOG_LEVEL_DEBUG, "n lines: %u", stop->n_lines);

                stop->lines = malloc (sizeof (void *) * stop->n_lines);

                for (unsigned int i = 0; i < stop->n_lines; ++i) {
                    stop->lines[i] = malloc (sizeof (Bus_line));
                    stop->lines[i]->loaded = false;
                }

                n_bus_stops++;

                if (bus_stops == NULL) {
                    bus_stops = malloc (sizeof (void *));
                } else {
                    bus_stops = realloc (bus_stops, sizeof (void *) * n_bus_stops);
                }
                bus_stops[n_bus_stops - 1] = stop;

                menu_layer_reload_data (s_menu_layer);

            } break;
            case MESSAGE_KEY_ADD_LINE: {
                Tuple *stop = dict_find (iterator, MESSAGE_KEY_ADD_LINE_STOP);
                Tuple *next = dict_find (iterator, MESSAGE_KEY_ADD_LINE_NEXT);
                Tuple *second_next = dict_find (iterator, MESSAGE_KEY_ADD_LINE_SECOND_NEXT);
                assert (stop != NULL);
                assert (next != NULL);
                assert (second_next != NULL);

                for (unsigned int i = 0; i < n_bus_stops; ++i) {
                    if (strcmp (bus_stops[i]->id, stop->value->cstring) == 0) {

                        // Find what line to load into
                        int line = 0;
                        for (unsigned int j = 0; j < bus_stops[i]->n_lines; ++j) {
                            if (!bus_stops[i]->lines[j]->loaded) {
                                line = j;
                            }
                        }

                        bus_stops[i]->lines[line]->name = malloc (tuple->length);
                        strcpy (bus_stops[i]->lines[line]->name, tuple->value->cstring);
                        bus_stops[i]->lines[line]->next_bus = next->value->uint32;
                        bus_stops[i]->lines[line]->second_next_bus = second_next->value->uint32;
                        bus_stops[i]->lines[line]->loaded = true;
                    }
                }
            } break;

            default:
                break;
        }

        tuple = dict_read_next (iterator);
    }
}

static void inbox_dropped_callback (AppMessageResult reason, void *context) {
    APP_LOG (APP_LOG_LEVEL_DEBUG, "Dropped a message! Reason: %d", reason);
}

static void outbox_sent_callback (DictionaryIterator *iterator, void *context) {
    APP_LOG (APP_LOG_LEVEL_DEBUG, "Sent a message!");
}

static void outbox_failed_callback (DictionaryIterator *iterator, AppMessageResult reason, void *context) {
    APP_LOG (APP_LOG_LEVEL_DEBUG, "Failed to send a message!");
}

static void init (void) {

    /*
     * Layout
     */

    s_window = window_create ();
    createWindow ();

    /*
     * AppMessages
     */

    app_message_open (255, 255);

    app_message_register_inbox_received (inbox_received_callback);
    app_message_register_inbox_dropped (inbox_dropped_callback);
    app_message_register_outbox_sent (outbox_sent_callback);
    app_message_register_outbox_failed (outbox_failed_callback);
}

static void deinit (void) {
    menu_layer_destroy (s_menu_layer);

    // Destroy the window
    window_destroy (s_window);
    s_window = NULL;

    for (unsigned int i = 0; i < n_bus_stops; ++i) {
        for (unsigned int j = 0; j < bus_stops[i]->n_lines; ++j) {
            free (bus_stops[i]->lines[j]->name);
            free (bus_stops[i]->lines[j]);
        }
        free (bus_stops[i]->lines);

        free (bus_stops[i]->id);
        free (bus_stops[i]->name);
        free (bus_stops[i]->lines_s);
        free (bus_stops[i]);
    }
    free (bus_stops);
}

int main (void) {
    init ();
    app_event_loop ();
    deinit ();
}
