/* structs.h --- 
 * 
 * Filename: structs.h
 * Author: Jules <archjules>
 * Created: Mon Jan  2 07:59:19 2017 (+0100)
 * Last-Updated: Tue Jun 20 02:47:12 2017 (+0200)
 *           By: Jules <archjules>
 */

#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdbool.h>
#include "platform/screen.h"

struct Sprite {
    uint8_t x_pos;
    uint8_t y_pos;
    uint8_t tile;

    // Flags; Stocked on one byte
    bool bg_priority;
    bool x_flip;
    bool y_flip;
    bool palette;
};

struct GPU {
    bool state;
    bool lcd_on;
    uint_fast8_t mode;
    uint_fast8_t current_line;
    uint_fast8_t scroll_x, scroll_y;
    uint_fast16_t clock;
    uint_fast16_t clock_off;

    // LCDC Interrupt
    uint8_t lyc;
    bool coincidence;
    
    bool coincidence_enabled;
    bool mode0_enabled;
    bool mode1_enabled;
    bool mode2_enabled;
    
    // Background
    bool bg_enabled;
    bool bg_map;
    bool bg_tile;
    uint32_t bg_palette[4];

    // Window
    uint8_t wd_x;
    uint8_t wd_y;
    bool wd_map;
    bool wd_enabled;
    
    // OAM
    struct Sprite oam[40];
    struct Sprite * line_cache[SCREEN_HEIGHT][10];
    uint32_t obp0[4], obp1[4]; // Palettes
    bool spr_enabled;
    bool spr_height; // false = 8x8, true = 8x16
};

#endif /* STRUCTS_H */
