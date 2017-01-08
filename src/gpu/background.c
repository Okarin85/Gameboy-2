/* background.c --- 
 * 
 * Filename: background.c
 * Author: Jules <archjules>
 * Created: Fri Dec 30 00:58:45 2016 (+0100)
 * Last-Updated: Sun Jan  8 12:18:17 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdint.h>
#include "cpu/cpu.h"
#include "gpu/gpu.h"

/*
 * background_get_color:
 * Get the color of a pixel in the background
 */
int background_get_color(struct CPU * cpu, int x, int y) {
    uint8_t tile1, tile2, tile_id;
    int offset, lineset, color, x_tile, y_tile;
    
    // Calculate the offset of the tile to display
    offset =
	(cpu->gpu.bg_map ? 0x1C00 : 0x1800) + ((((y + cpu->gpu.scroll_y) & 0xFF) >> 3) << 5) // Offset of the line
	+ ((cpu->gpu.scroll_x + x & 0xff) / 8); // Offset within the line

    tile_id = cpu->memory.gram[offset];
   
    x_tile = (cpu->gpu.scroll_x + x) % 8;
    y_tile = (cpu->gpu.scroll_y + y) % 8;

    return tile_get_pixel(cpu, tile_id, cpu->gpu.bg_tile, x_tile, y_tile);
}
