#include "main_window.h"

static Window *s_window;
static MenuLayer *s_menu_layer;

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

    list_selection_window_init(bus_stops[cell_index->row]);
}

void main_window_init () {
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

void main_window_deinit () {
    menu_layer_destroy (s_menu_layer);

    window_destroy (s_window);
    s_window = NULL;
}

void reload_stops () {
    menu_layer_reload_data (s_menu_layer);
}
