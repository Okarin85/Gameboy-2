/* gpu.c --- 
 * 
 * Filename: gpu.c
 * Author: Jules <archjules>
 * Created: Tue Dec 13 00:45:56 2016 (+0100)
 * Last-Updated: Fri Jan  6 17:24:30 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include "cpu/cpu.h"
#include "cpu/interrupt.h"
#include "gpu/gpu.h"
#include "gpu/oam.h"
#include "platform/screen.h"
#include "platform/general.h"
#include "logger.h"

/*
 * gpu_render_line:
 * Render a line on the screen
 */
void gpu_render_line(struct CPU * cpu, int current_line) {
    int bg_color = 0, color = 0;
    struct Sprite * obj = NULL;
    for (int i = 0; i < SCREEN_WIDTH; i++) {
	bg_color = background_get_color(cpu, i, current_line);
	if (cpu->gpu.spr_enabled) obj = oam_get_sprite(cpu, i, current_line);
	
	if (obj != NULL) {
	    color = oam_get_color(cpu, obj, i, current_line);
	    if (((obj->bg_priority == 0) || (bg_color == 0)) && (color != 0)) {
		screen_put_pixel(cpu->screen,
				 i,
				 current_line,
				 (obj->palette ? cpu->gpu.obp1 : cpu->gpu.obp0)[color]
		    );
		continue;
	    }
	}
	screen_put_pixel(cpu->screen, i, current_line, cpu->gpu.bg_palette[bg_color]);
    }
}

/*
 * gpu_stat_interrupt:
 * Request a STAT interrupt if enabled
 */
void gpu_stat_interrupt(struct CPU * cpu, uint8_t bit) {
    if (bit)
	provoke_interruption(cpu, INT_STAT);
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
		gpu_stat_interrupt(cpu, cpu->gpu.mode1_enabled);
		provoke_interruption(cpu, INT_VBLANK);
		cpu->gpu.mode = 1;
	    } else {
		cpu->gpu.current_line++;
		if (cpu->gpu.current_line == cpu->gpu.lyc) {
		    cpu->gpu.coincidence = true;
		    gpu_stat_interrupt(cpu, cpu->gpu.coincidence_enabled);
		}
		cpu->gpu.mode = 2;
		gpu_stat_interrupt(cpu, cpu->gpu.mode2_enabled);
	    }
	    
	    cpu->gpu.clock = 0;
	}
	break;
    case 1: // Vblank
	if (cpu->gpu.clock >= 114) {
	    cpu->gpu.current_line++;
	    if (cpu->gpu.current_line == 153) {
		// Now that a frame is complete, we do all we have to do
		handle_new_frame(cpu);
		cpu->gpu.current_line = 0;
		cpu->gpu.mode  = 2;
		gpu_stat_interrupt(cpu, cpu->gpu.mode2_enabled);
	    }
	    cpu->gpu.clock = 0;
	}
	break;
    case 2: // Reading OAM
	if (cpu->gpu.clock >= 20) {
	    cpu->gpu.clock = 0;
	    cpu->gpu.mode = 3;
	    gpu_stat_interrupt(cpu, cpu->gpu.mode1_enabled);
	}
	break;
    case 3: // Reading VRAM
	if (cpu->gpu.clock >= 43) {
	    cpu->gpu.clock = 0;
	    cpu->gpu.mode = 0;
	    gpu_stat_interrupt(cpu, cpu->gpu.mode0_enabled);
	}
    }
}
