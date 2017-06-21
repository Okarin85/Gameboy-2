/* background.c --- 
 * 
 * Filename: background.c
 * Author: Jules <archjules>
 * Created: Fri Dec 30 00:58:45 2016 (+0100)
 * Last-Updated: Tue Jun 20 23:46:23 2017 (+0200)
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
    uint8_t tile_id, px, py;
    int offset, x_tile, y_tile;

    px = x - (cpu->gpu.wd_x - 7);
    py = y - cpu->gpu.wd_y;
    
    // Calculate the offset of the tile to display
    offset =
	(cpu->gpu.wd_map ? 0x1C00 : 0x1800) + ((py >> 3) << 5) // Offset of the line
	+ (px / 8); // Offset within the line

    tile_id = cpu->memory.gram[offset];
   
    x_tile = px % 8;
    y_tile = py % 8;

    return tile_get_pixel(cpu, 0, tile_id, cpu->gpu.bg_tile, x_tile, y_tile);
}

/*
 * background_get_color_dmg:
 * Get the color of a pixel in the background in non-CGB mode
 */
int background_get_color_dmg(struct CPU * cpu, int x, int y) {
    uint8_t tile_id;
    int offset, x_tile, y_tile;
    
    // Calculate the offset of the tile to display
    offset =
	(cpu->gpu.bg_map ? 0x1C00 : 0x1800) + ((((y + cpu->gpu.scroll_y) & 0xFF) >> 3) << 5) // Offset of the line
	+ (((cpu->gpu.scroll_x + x) & 0xff) / 8); // Offset within the line

    tile_id = cpu->memory.gram[offset];
   
    x_tile = (cpu->gpu.scroll_x + x) % 8;
    y_tile = (cpu->gpu.scroll_y + y) % 8;

    return tile_get_pixel(cpu, 0, tile_id, cpu->gpu.bg_tile, x_tile, y_tile);
}

/*
 * background_get_color_gbc:
 * Get the color of a pixel in the background in CGB mode
 */
int background_get_color_gbc(struct CPU * cpu, int x, int y, int *color, int *pal) {
    uint8_t tile_id, tile_attr;
    int offset, x_tile, y_tile, bank;
    
    // Calculate the offset of the tile to display
    offset =
	(cpu->gpu.bg_map ? 0x1C00 : 0x1800) + ((((y + cpu->gpu.scroll_y) & 0xFF) >> 3) << 5) // Offset of the line
	+ (((cpu->gpu.scroll_x + x) & 0xff) / 8); // Offset within the line

    tile_id   = cpu->memory.gram[offset];
    tile_attr = cpu->memory.gram[0x2000 + offset];
    
    x_tile = (cpu->gpu.scroll_x + x) % 8;
    y_tile = (cpu->gpu.scroll_y + y) % 8;

    bank   = (tile_attr & 0x8) ? 1 : 0;
    
    (*color) = tile_get_pixel(cpu, bank, tile_id, cpu->gpu.bg_tile, x_tile, y_tile);
    (*pal)   = tile_attr & 7;
}
