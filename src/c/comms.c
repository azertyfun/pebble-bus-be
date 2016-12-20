#include "comms.h"

bool began = false, geoloc_done = false, data_received = false;

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
                    reload_stops ();
                } else if (strcmp (tuple->value->cstring, "GEOLOC_DONE") == 0) {
                    geoloc_done = true;
                    reload_stops ();
                } else if (strcmp (tuple->value->cstring, "DATA_RECEIVED") == 0) {
                    data_received = true;
                    reload_stops ();
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

                reload_stops ();

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

void comms_init () {
    app_message_open (255, 255);

    app_message_register_inbox_received (inbox_received_callback);
    app_message_register_inbox_dropped (inbox_dropped_callback);
    app_message_register_outbox_sent (outbox_sent_callback);
    app_message_register_outbox_failed (outbox_failed_callback);
}

void comms_deinit () {
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
