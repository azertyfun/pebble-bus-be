#include "ui.h"

static Window *s_window, *s_window_time;
static MenuLayer *s_menu_layer;
static ScrollTextLayer *s_text_layer;
static char *time_s;


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

void ui_init () {
    s_window = window_create ();

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

void ui_deinit () {
    menu_layer_destroy (s_menu_layer);

    window_destroy (s_window);
    s_window = NULL;
}

void reload_stops () {
    menu_layer_reload_data (s_menu_layer);
}
