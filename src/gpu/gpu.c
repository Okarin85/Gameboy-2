/* gpu.c --- 
 * 
 * Filename: gpu.c
 * Author: Jules <archjules>
 * Created: Tue Dec 13 00:45:56 2016 (+0100)
 * Last-Updated: Mon Jan  2 11:33:04 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include "cpu/cpu.h"
#include "cpu/interrupt.h"
#include "gpu/gpu.h"
#include "gpu/oam.h"
#include "platform/screen.h"
#include "logger.h"

/*
 * gpu_render_line:
 * Render a line on the screen
 */
void gpu_render_line(struct CPU * cpu, int current_line) {
    int bg_color = 0;
    struct Sprite * obj = NULL;
    for (int i = 0; i < SCREEN_WIDTH; i++) {
	bg_color = background_get_color(cpu, i, current_line);
	if (cpu->gpu.spr_enabled) obj = oam_get_sprite(cpu, i, current_line);
	
	if ((obj != NULL) && ((obj->bg_priority == 0) || (bg_color == 0))) {
	    screen_put_pixel(cpu->screen,
			     i,
			     current_line,
			     (obj->palette ? cpu->gpu.obp1 : cpu->gpu.obp0)[oam_get_color(cpu, obj, i, current_line)]
		);
	} else {
	    screen_put_pixel(cpu->screen, i, current_line, cpu->gpu.bg_palette[bg_color]);
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
