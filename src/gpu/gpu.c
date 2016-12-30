/* gpu.c --- 
 * 
 * Filename: gpu.c
 * Author: Jules <archjules>
 * Created: Tue Dec 13 00:45:56 2016 (+0100)
 * Last-Updated: Fri Dec 30 01:07:31 2016 (+0100)
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
    for (int i = 0; i < SCREEN_WIDTH; i++) {
	screen_put_pixel(cpu->screen, i, current_line, background_get_color(cpu, i, current_line));
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
