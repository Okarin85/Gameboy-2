/* gpu.c --- 
 * 
 * Filename: gpu.c
 * Author: Jules <archjules>
 * Created: Tue Dec 13 00:45:56 2016 (+0100)
 * Last-Updated: Wed Dec 28 12:22:26 2016 (+0100)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include "interrupt.h"
#include "screen.h"
#include "logger.h"
#include "cpu.h"

/*
 * gpu_render_line:
 * Render a line on the screen
 */
void gpu_render_line(struct CPU * cpu, int current_line) {
    uint8_t tile1, tile2, tile_id;
    int offset, lineset, color, x_tile, y_tile;
    // Calculate the offset of the tile to display
    offset = (cpu->gpu.bg_map ? 0x1C00 : 0x1800) + ((((current_line + cpu->gpu.scroll_y) & 0xFF) >> 3) << 5);
    lineset= (cpu->gpu.scroll_x / 8);

    tile_id = cpu->memory.gram[offset + lineset];
   
    x_tile = (cpu->gpu.scroll_x) % 8;
    y_tile = (current_line + cpu->gpu.scroll_y) % 8;
    
    for (int i = 0; i < SCREEN_WIDTH; i++) {
	// Getting the data of the tile
	if(cpu->gpu.bg_tile) {
	    tile1 = cpu->memory.gram[tile_id * 16 + y_tile * 2 + 1];
	    tile2 = cpu->memory.gram[tile_id * 16 + y_tile * 2];
	} else {
	    tile1 = cpu->memory.gram[0x1000 + ((int8_t)tile_id) * 16 + y_tile * 2 + 1];
	    tile2 = cpu->memory.gram[0x1000 + ((int8_t)tile_id) * 16 + y_tile * 2];
	}
	color = ((tile1 >> (7 - x_tile)) & 0x1) | (((tile2 >> (7 - x_tile)) & 0x1) << 1);
	
	screen_put_pixel(cpu->screen, i, current_line, cpu->gpu.palette[color]);

	// Go on
	x_tile++;
	if (x_tile == 8) {
	    lineset = (lineset + 1) % 32;
	    tile_id = cpu->memory.gram[offset + lineset];
	    x_tile = 0;
	}
    }
}

/*
 * gpu_next:
 * Execute a step for the GPU.
 */
int gpu_next(struct CPU * cpu) {
    cpu->gpu.clock += cpu->time_last;
    
    switch(cpu->gpu.mode) {
    case 0: // Hblank
	if (cpu->gpu.clock >= 51) {
	    gpu_render_line(cpu, cpu->gpu.current_line);
	    
	    if (cpu->gpu.current_line == 143) {
		provoke_interruption(cpu, INT_VBLANK);
		cpu->gpu.mode = 1;
	    } else {
		cpu->gpu.current_line++;
		cpu->gpu.mode = 2;
	    }
	    
	    cpu->gpu.clock = 0;
	}
	break;
    case 1: // Vblank
	if (cpu->gpu.clock >= 114) {
	    cpu->gpu.current_line++;
	    if (cpu->gpu.current_line == 153) {
		screen_flip(cpu->screen);
		cpu->gpu.current_line = 0;
		cpu->gpu.mode  = 2;
	    }
	    cpu->gpu.clock = 0;
	}
	break;
    case 2: // Reading OAM
	if (cpu->gpu.clock >= 20) {
	    cpu->gpu.clock = 0;
	    cpu->gpu.mode = 3;
	}
	break;
    case 3: // Reading VRAM
	if (cpu->gpu.clock >= 43) {
	    cpu->gpu.clock = 0;
	    cpu->gpu.mode = 0;
	}
    }
}
