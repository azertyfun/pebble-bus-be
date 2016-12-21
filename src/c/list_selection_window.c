#include "list_selection_window.h"

static Window *s_window;
static MenuLayer *s_menu_layer;

static Bus_stop *bus_stop;

static AppTimer *reload_timer;

static void reload_timer_callback(void* data) {
    reload_timer = app_timer_register(1000, reload_timer_callback, NULL);

    menu_layer_reload_data (s_menu_layer);
}

static void list_selection_window_unload () {
    menu_layer_destroy (s_menu_layer);

    window_destroy (s_window);
    s_window = NULL;

    app_timer_cancel(reload_timer);
}

static uint16_t menu_get_num_sections_callback (MenuLayer *menu_layer, void *data) {
    return NUM_MENU_SECTIONS;
}

static uint16_t menu_get_num_rows_callback (MenuLayer *menu_layer, uint16_t section_index, void *data) {
    switch (section_index) {
        case 0:
            return bus_stop->n_lines == 0 ? 1 : bus_stop->n_lines;
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
            menu_cell_basic_header_draw (ctx, cell_layer, "Select line");
            break;
    }
}

static void menu_draw_row_callback (GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
    // Determine which section we're going to draw in
    switch (cell_index->section) {
        case 0:
            if (cell_index->row == 0 && bus_stop->n_lines == 0) {
                menu_cell_basic_draw (ctx, cell_layer, "None", "No lines for this stop", NULL);
            } else {
                // Display the next bus
                // TODO: Show the second next bus, in a fancier fashion (multiline?)

                char *time1 = malloc (8);
                //char *time2 = malloc (8);
                char *time_left = malloc (16);
                if (bus_stop->lines[cell_index->row]->next_bus != 0) {
                    strftime (time1, 7, "%H:%M",
                              localtime (&bus_stop->lines[cell_index->row]->next_bus));

                    int t = bus_stop->lines[cell_index->row]->next_bus - time (NULL);
                    if(t > 0) {
                        snprintf (time_left, 16, "in %02d:%02d", t / 60, t % 60);
                    } else {
                        snprintf (time_left, 16, "%02d:%02d ago", -t / 60, -t % 60);
                    }

                    /*if (bus_stop->lines[cell_index->row]->second_next_bus != 0) {
                        strftime (time2, 7, "%H:%M", localtime (&bus_stop->lines[cell_index->row]->second_next_bus));
                    } else {
                        strcpy (time2, "?");
                    } */
                } else {
                    menu_cell_basic_draw (ctx, cell_layer, bus_stop->lines[cell_index->row]->name, "Next: Unknown", NULL);
                    break;
                }

                char* time_s = malloc (128);
                strcat (time_s, "Next: ");
                strcat (time_s, time1);
                strcat (time_s, ", ");
                strcat (time_s, time_left);

                free (time_left);
                free (time1);
                //free (time2);
                menu_cell_basic_draw (ctx, cell_layer, bus_stop->lines[cell_index->row]->name, time_s, NULL);
            }
            break;
    }
}

static void menu_select_callback (MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
}

void list_selection_window_init (Bus_stop* stop) {
    bus_stop = stop;

    s_window = window_create ();

    window_set_window_handlers (s_window, (WindowHandlers){
                                               .load = NULL,
                                               .appear = NULL,
                                               .disappear = NULL,
                                               .unload = list_selection_window_unload,
                                               });

    Layer *window_layer = window_get_root_layer (s_window);
    GRect bounds = layer_get_frame (window_layer);

    s_menu_layer = menu_layer_create (bounds);
    menu_layer_set_click_config_onto_window (s_menu_layer, s_window);
    menu_layer_set_callbacks (s_menu_layer, NULL, (MenuLayerCallbacks){
                                                  .get_num_sections = menu_get_num_sections_callback, .get_num_rows = menu_get_num_rows_callback, .get_header_height = menu_get_header_height_callback, .draw_header = menu_draw_header_callback, .draw_row = menu_draw_row_callback, .select_click = menu_select_callback,
                                                  });
    menu_layer_set_click_config_onto_window (s_menu_layer, s_window);
    layer_add_child (window_layer, menu_layer_get_layer (s_menu_layer));

    reload_timer = app_timer_register(1000, reload_timer_callback, NULL);

    window_stack_push (s_window, true);
}

