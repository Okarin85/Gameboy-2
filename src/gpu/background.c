/* background.c --- 
 * 
 * Filename: background.c
 * Author: Jules <archjules>
 * Created: Fri Dec 30 00:58:45 2016 (+0100)
 * Last-Updated: Mon Jan  2 07:50:57 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdint.h>
#include "cpu/cpu.h"
#include "gpu/gpu.h"

/*
 * background_get_color:
 * Get the color of a pixel in the background
 * @return: The color in 32bit RGBA format.
 */
uint32_t background_get_color(struct CPU * cpu, int x, int y) {
    uint8_t tile1, tile2, tile_id;
    int offset, lineset, color, x_tile, y_tile;
    
    // Calculate the offset of the tile to display
    offset =
	(cpu->gpu.bg_map ? 0x1C00 : 0x1800) + ((((y + cpu->gpu.scroll_y) & 0xFF) >> 3) << 5) // Offset of the line
	+ ((cpu->gpu.scroll_x + x) / 8); // Offset within the line

    tile_id = cpu->memory.gram[offset];
   
    x_tile = (cpu->gpu.scroll_x + x) % 8;
    y_tile = (cpu->gpu.scroll_y + y) % 8;

    if(cpu->gpu.bg_tile) {
	tile1 = cpu->memory.gram[tile_id * 16 + y_tile * 2 + 1];
	tile2 = cpu->memory.gram[tile_id * 16 + y_tile * 2];
    } else {
	tile1 = cpu->memory.gram[0x1000 + ((int8_t)tile_id) * 16 + y_tile * 2 + 1];
	tile2 = cpu->memory.gram[0x1000 + ((int8_t)tile_id) * 16 + y_tile * 2];
    }
    
    color = ((tile1 >> (7 - x_tile)) & 0x1) | (((tile2 >> (7 - x_tile)) & 0x1) << 1);

    return cpu->gpu.bg_palette[color];
}
