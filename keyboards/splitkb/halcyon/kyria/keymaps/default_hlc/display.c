// Include the main display functions so we don't have to initialize the display again
#include "hlc_tft_display/hlc_tft_display.h"
#include "layers.h"

// Fonts mono2
#include "hlc_tft_display/graphics/fonts/Retron2000-27.qff.h"
#include "hlc_tft_display/graphics/fonts/Retron2000-underline-27.qff.h"
// Numbers mono2
#include "hlc_tft_display/graphics/numbers/0.qgf.h"
#include "hlc_tft_display/graphics/numbers/1.qgf.h"
#include "hlc_tft_display/graphics/numbers/2.qgf.h"
#include "hlc_tft_display/graphics/numbers/3.qgf.h"
#include "hlc_tft_display/graphics/numbers/4.qgf.h"
#include "hlc_tft_display/graphics/numbers/5.qgf.h"
#include "hlc_tft_display/graphics/numbers/6.qgf.h"
#include "hlc_tft_display/graphics/numbers/7.qgf.h"
#include "hlc_tft_display/graphics/numbers/8.qgf.h"
#include "hlc_tft_display/graphics/numbers/9.qgf.h"
#include "hlc_tft_display/graphics/numbers/undef.qgf.h"

//static const char *text_zero = "ZERO";
//static const char *text_adj = "ADJ";
// NOTE: strings are padded to have consistent length
static const char *text_lalt =  "LALT ";
static const char *text_ralt =  "RALT ";
static const char *text_lctrl = "LCTRL";
static const char *text_rctrl = "RCTRL";
static const char *text_blank = "     ";

// copied from HSV_SCROLL_OFF
#define HSV_DEFAULT_TEXT 202, 104, 77

// Setup painter devices
painter_device_t lcd;
painter_device_t lcd_surface;

static painter_font_handle_t Retron27;
static painter_font_handle_t Retron27_underline;

static int last_layer = 0;
static uint8_t last_oneshot_mods;

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
        /* case _QWERTY: */
        /*     qp_drawtext_recolor(lcd_surface, 5, 5, Retron27, text_zero, HSV_DEFAULT_TEXT, HSV_BLACK); */
        /*     break; */
        /* case _ADJUST: */
        /*     qp_drawtext_recolor(lcd_surface, 5, 5, Retron27, text_adj, HSV_DEFAULT_TEXT, HSV_BLACK); */
        /*     break; */
        case 0:
            layer_number = qp_load_image_mem(gfx_0);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_0, HSV_BLACK);
            break;
        case 1:
            layer_number = qp_load_image_mem(gfx_1);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_1, HSV_BLACK);
            break;
        case 2:
            layer_number = qp_load_image_mem(gfx_2);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_2, HSV_BLACK);
            break;
        case 3:
            layer_number = qp_load_image_mem(gfx_3);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_3, HSV_BLACK);
            break;
        case 4:
            layer_number = qp_load_image_mem(gfx_4);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_4, HSV_BLACK);
            break;
        case 5:
            layer_number = qp_load_image_mem(gfx_5);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_5, HSV_BLACK);
            break;
        case 6:
            layer_number = qp_load_image_mem(gfx_6);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_6, HSV_BLACK);
            break;
        case 7:
            layer_number = qp_load_image_mem(gfx_7);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_7, HSV_BLACK);
            break;
        default:
            layer_number = qp_load_image_mem(gfx_undef);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_UNDEF, HSV_BLACK);
        }
        last_layer = layer;
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
        else if (oneshot_mods & MOD_BIT(KC_LCTRL)) {
           qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_lctrl, HSV_ORANGE, HSV_BLACK);
        }
        else if (oneshot_mods & MOD_BIT(KC_RCTRL)) {
           qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_rctrl, HSV_ORANGE, HSV_BLACK);
        }
        else {
           qp_drawtext_recolor(lcd_surface, 5, text_y_pos, Retron27, text_blank, HSV_ORANGE, HSV_BLACK);
        }
        last_oneshot_mods = oneshot_mods;
    }

    // Move surface to lcd, this actually writes the content to the physical display
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    qp_flush(lcd);

    is_first_run = false;

    return false;
}
