// Include the main display functions so we don't have to initialize the display again
#include "hlc_tft_display/hlc_tft_display.h"
#include "layers.h"

// Fonts mono2
#include "hlc_tft_display/graphics/fonts/Retron2000-27.qff.h"
#include "hlc_tft_display/graphics/fonts/Retron2000-underline-27.qff.h"

static const char *text_zero = "ZERO";
static const char *text_adj = "ADJ";

// copied from HSV_SCROLL_OFF
#define HSV_DEFAULT_TEXT 202, 104, 77

// Setup painter devices
painter_device_t lcd;
painter_device_t lcd_surface;

static painter_font_handle_t Retron27;
static painter_font_handle_t Retron27_underline;

static int last_layer = 0;

// This function is ran on bootup of the keyboard
bool module_post_init_user(void) {
    // TODO: load images??

    return false;
}

// This function runs after every matrix scan
bool display_module_housekeeping_task_user(bool second_display) {
    // don't support second display
    if (second_display) {
        return true;
    }

    static bool is_first_run = true;

    if (is_first_run) {
        // Load fonts
        Retron27 = qp_load_font_mem(font_Retron2000_27);
        Retron27_underline = qp_load_font_mem(font_Retron2000_underline_27);
    }

    int layer = get_highest_layer(layer_state);
    if (layer != last_layer || is_first_run) {
        switch (layer) {
        case _QWERTY:
            qp_drawtext_recolor(lcd_surface, 5, 5, Retron27, text_zero, HSV_DEFAULT_TEXT, HSV_BLACK);
            break;
        case _ADJUST:
            qp_drawtext_recolor(lcd_surface, 5, 5, Retron27, text_adj, HSV_DEFAULT_TEXT, HSV_BLACK);
            break;
        }
        last_layer = layer;
    }

    // Create checks to see if the displays are set. We don't need to keep updating the display with the same image so this will save some CPU time.
    /*static bool display_set = false;
    static bool second_display_set = false;

    // When the display isn't set, do the following
    if (!display_set) {
        // If it's the main display
        if (!second_display) {
            // Create text to write
            static const char *text = "This is a user display!";

            // Draw text on top left corner
            qp_drawtext_recolor(lcd_surface, 0, 0, thintel, text, HSV_WHITE, HSV_BLACK);

            // Make sure to not run this again.
            display_set = true;
        // If it's the secundairy display
        } else {
            // Create text to write
            static const char *text = "This is a second user display!";

            // Read width from text
            int16_t width = qp_textwidth(thintel, text);

            // Draw text on bottom right corner
            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - width), (LCD_HEIGHT - thintel->line_height), thintel, text, HSV_WHITE, HSV_BLACK);

            // Make sure to not run this again.
            display_set = true;
            second_display_set = true;
        }
    }

    // Make sure that the second display loads correctly, sometimes it takes a little while for the keyboard to know it has a second display.
    // So we reset the state and make it run again until the secondary display is drawn correctly
    if(second_display && !second_display_set) {
        display_set = false;
    }*/

    // Move surface to lcd, this actually writes the content to the physical display
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    qp_flush(lcd);

    is_first_run = false;

    return false;
}
