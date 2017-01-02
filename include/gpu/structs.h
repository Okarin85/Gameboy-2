/* structs.h --- 
 * 
 * Filename: structs.h
 * Author: Jules <archjules>
 * Created: Mon Jan  2 07:59:19 2017 (+0100)
 * Last-Updated: Mon Jan  2 08:16:56 2017 (+0100)
 *           By: Jules <archjules>
 */

#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdbool.h>
#include "platform/screen.h"

struct Sprite {
    bool present;
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
    uint_fast8_t mode;
    uint_fast8_t current_line;
    uint_fast8_t scroll_x, scroll_y;
    uint_fast16_t clock;

    // Background
    bool bg;
    bool bg_map;
    bool bg_tile;
    uint32_t bg_palette[4];

    // OAM
    struct Sprite oam[40];
    struct Sprite * line_cache[10][SCREEN_HEIGHT];
};

#endif /* STRUCTS_H */
