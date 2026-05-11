// Include the main display functions so we don't have to initialize the display again
#include "hlc_tft_display/hlc_tft_display.h"
#include "layers.h"

// Fonts mono2
#include "hlc_tft_display/graphics/fonts/Retron2000-27.qff.h"
#include "hlc_tft_display/graphics/fonts/Retron2000-underline-27.qff.h"
// images
#include "graphics/arrow-all.qgf.h"
#include "graphics/keyboard.qgf.h"
#include "graphics/keyboard.qgf.h"
#include "graphics/monitor.qgf.h"
#include "graphics/mouse.qgf.h"
#include "graphics/numeric.qgf.h"
#include "graphics/script-outline.qgf.h"
#include "graphics/symbol.qgf.h"
#include "graphics/tools.qgf.h"

//static const char *text_zero = "ZERO";
//static const char *text_adj = "ADJ";
static const char *text_lalt =  "LALT";
static const char *text_ralt =  "RALT";
static const char *text_lctrl = "LCTRL";
static const char *text_rctrl = "RCTRL";
static const char *text_wheel = "WHEEL";
// NOTE: strings are padded to ensure previous value is overwritten
static const char *text_0 = "0 ";
static const char *text_1 = "1 ";
static const char *text_2 = "2 ";
static const char *text_3 = "3 ";
static const char *text_4 = "4 ";
static const char *text_5 = "5 ";
static const char *text_6 = "6 ";
static const char *text_7 = "7 ";
static const char *text_undef = "? ";

// copied from HSV_LAYER_0
#define HSV_DEFAULT_IMAGE 0, 0, 160
// copied from HSV_SCROLL_OFF
#define HSV_DEFAULT_TEXT 202, 104, 77

// Setup painter devices
painter_device_t lcd;
painter_device_t lcd_surface;

static painter_font_handle_t Retron27;
static painter_font_handle_t Retron27_underline;
static painter_image_handle_t layer_image;

static int last_layer = 0;
static uint8_t last_oneshot_mods;

extern bool trackpad_scroll_mode;
static bool last_trackpad_scroll_mode = false;

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
        bool no_image = false;
        switch (layer) {
        case _QWERTY:
            layer_image = qp_load_image_mem(gfx_keyboard);
            break;
        case _LMIRROR:
            layer_image = qp_load_image_mem(gfx_symbol);
            break;
        case _RMIRROR:
            layer_image = qp_load_image_mem(gfx_numeric);
            break;
        case _MOUSE:
            layer_image = qp_load_image_mem(gfx_mouse);
            break;
        case _NAV:
            layer_image = qp_load_image_mem(gfx_arrow_all);
            break;
        case _SWAY:
            layer_image = qp_load_image_mem(gfx_monitor);
            break;
        case _ADJUST:
            layer_image = qp_load_image_mem(gfx_tools);
            break;
        case _SCROLL:
            layer_image = qp_load_image_mem(gfx_script_outline);
            break;
        default:
            no_image = true;
        }
        if (!no_image) {
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_image, HSV_DEFAULT_IMAGE, HSV_BLACK);
            qp_close_image(layer_image);
        }
        // write layer number as well
        uint16_t text_y_pos = no_image ? 5 : 5 + layer_image->height + 5;
        switch (layer) {
        case 0:
            qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_0, HSV_LAYER_0, HSV_BLACK);
            break;
        case 1:
            qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_1, HSV_LAYER_1, HSV_BLACK);
            break;
        case 2:
            qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_2, HSV_LAYER_2, HSV_BLACK);
            break;
        case 3:
            qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_3, HSV_LAYER_3, HSV_BLACK);
            break;
        case 4:
            qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_4, HSV_LAYER_4, HSV_BLACK);
            break;
        case 5:
            qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_5, HSV_LAYER_5, HSV_BLACK);
            break;
        case 6:
            qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_6, HSV_LAYER_6, HSV_BLACK);
            break;
        case 7:
            qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_7, HSV_LAYER_7, HSV_BLACK);
            break;
        default:
            qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_undef, HSV_LAYER_UNDEF, HSV_BLACK);
        }

        last_layer = layer;
    }

    if (trackpad_scroll_mode != last_trackpad_scroll_mode) {
        uint16_t text_y_pos = LCD_HEIGHT - 2*(Retron27->line_height + 5);
        if (trackpad_scroll_mode) {
           qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_wheel, HSV_DEFAULT_TEXT, HSV_BLACK);
        }
        else {
            qp_rect(lcd_surface, 5, text_y_pos, LCD_WIDTH, text_y_pos + Retron27->line_height + 5, HSV_OFF, true);
        }
        last_trackpad_scroll_mode = trackpad_scroll_mode;
    }

    uint8_t oneshot_mods = get_oneshot_mods() | get_oneshot_locked_mods();
    if (oneshot_mods != last_oneshot_mods || is_first_run) {
        uint16_t text_y_pos = LCD_HEIGHT - Retron27->line_height - 5;
        if (oneshot_mods & MOD_BIT(KC_LALT)) {
           qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_lalt, HSV_ORANGE, HSV_BLACK);
        }
        else if (oneshot_mods & MOD_BIT(KC_RALT)) {
           qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_ralt, HSV_ORANGE, HSV_BLACK);
        }
        else if (oneshot_mods & MOD_BIT(KC_LCTL)) {
           qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_lctrl, HSV_ORANGE, HSV_BLACK);
        }
        else if (oneshot_mods & MOD_BIT(KC_RCTL)) {
           qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_rctrl, HSV_ORANGE, HSV_BLACK);
        }
        else {
            // clear text by overwriting with rectangle
            qp_rect(lcd_surface, 5, text_y_pos, LCD_WIDTH, LCD_HEIGHT, HSV_OFF, true);
        }
        last_oneshot_mods = oneshot_mods;
    }

    // Move surface to lcd, this actually writes the content to the physical display
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    qp_flush(lcd);

    is_first_run = false;

    return false;
}
