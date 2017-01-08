/* background.c --- 
 * 
 * Filename: background.c
 * Author: Jules <archjules>
 * Created: Fri Dec 30 00:58:45 2016 (+0100)
 * Last-Updated: Sun Jan  8 14:37:33 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdint.h>
#include "cpu/cpu.h"
#include "gpu/gpu.h"

/*
 * window_get_color:
 * Get the color of a pixel in the window display
 */
int window_get_color(struct CPU * cpu, int x, int y) {
    uint8_t tile_id;
    int offset, offset_x, offset_y, x_tile, y_tile;

    offset_x = cpu->gpu.wd_x - 7;
    
    // Calculate the offset of the tile to display
    offset =
	(cpu->gpu.wd_map ? 0x1C00 : 0x1800) + (((uint8_t)(y - cpu->gpu.wd_y) >> 3) << 5) // Offset of the line
	+ ((uint8_t)(x - offset_x) / 8); // Offset within the line

    tile_id = cpu->memory.gram[offset];
   
    x_tile = (offset_x + x) % 8;
    y_tile = (offset_y + y) % 8;

    return tile_get_pixel(cpu, tile_id, cpu->gpu.bg_tile, x_tile, y_tile);
}

/*
 * background_get_color:
 * Get the color of a pixel in the background
 */
int background_get_color(struct CPU * cpu, int x, int y) {
    uint8_t tile_id;
    int offset, x_tile, y_tile;
    
    // Calculate the offset of the tile to display
    offset =
	(cpu->gpu.bg_map ? 0x1C00 : 0x1800) + ((((y + cpu->gpu.scroll_y) & 0xFF) >> 3) << 5) // Offset of the line
	+ ((cpu->gpu.scroll_x + x & 0xff) / 8); // Offset within the line

    tile_id = cpu->memory.gram[offset];
   
    x_tile = (cpu->gpu.scroll_x + x) % 8;
    y_tile = (cpu->gpu.scroll_y + y) % 8;

    return tile_get_pixel(cpu, tile_id, cpu->gpu.bg_tile, x_tile, y_tile);
}
