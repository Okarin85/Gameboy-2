/* palette.c --- 
 * 
 * Filename: palette.c
 * Author: Jules <archjules>
 * Created: Tue Jun 20 21:58:45 2017 (+0200)
 * Last-Updated: Wed Jun 21 00:01:57 2017 (+0200)
 *           By: Jules <archjules>
 */
#include "gpu/gpu.h"

uint32_t palette_get_color(char * palette, int index, int color) {
    uint8_t color1, color2, red, green, blue;

    color1 = palette[(index << 3) + (color << 1)];
    color2 = palette[(index << 3) + (color << 1) + 1];

    red = color1 & 0x1F;
    green = (color1 >> 5) | ((color2 & 0x3) << 3);
    blue = (color2 & 0x7c) >> 2;

    return (red << 19) | (green << 11) | (blue << 3);
}
