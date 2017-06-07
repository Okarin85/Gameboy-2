/* gpu.c --- 
 * 
 * Filename: gpu.c
 * Author: Jules <archjules>
 * Created: Tue Dec 13 00:45:56 2016 (+0100)
 * Last-Updated: Tue Jun  6 21:34:33 2017 (+0200)
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

static inline uint32_t get_color(int color) {
    switch(color) {
    case 0: return SCREEN_WHITE;
    case 1: return SCREEN_LGRAY;
    case 2: return SCREEN_DGRAY;
    case 3: return SCREEN_BLACK;
    default: return 0;
    }
}

/*
 * gpu_render_line:
 * Render a line on the screen
 */
void gpu_render_line(struct CPU * cpu, int current_line) {
    int bg_color = 0, color = 0;
    
    for (int i = 0; i < SCREEN_WIDTH; i++) {
	// Getting the background/window pixel
	if (cpu->gpu.wd_enabled && (i >= (cpu->gpu.wd_x - 7)) && (current_line >= cpu->gpu.wd_y)) {
	    bg_color = window_get_color(cpu, i, current_line);
	} else if (cpu->gpu.bg_enabled) {
	    bg_color = background_get_color(cpu, i, current_line);
	} else {
	    bg_color = 0;
	}
	if (cpu->gpu.spr_enabled)
	    color = oam_render_sprite(cpu, i, current_line, bg_color);
	else
	    color = cpu->gpu.bg_palette[bg_color];
	screen_put_pixel(cpu->screen, i, current_line, get_color(color));
    }
}

/*
 * gpu_stat_interrupt:
 * Request a STAT interrupt if enabled
 */
void gpu_stat_interrupt(struct CPU * cpu, uint8_t bit) {
    if (bit) {
	provoke_interruption(cpu, INT_STAT);
    }
}

/*
 * change_current_line:
 * Change the current line, and sets the coincidence flag if new_line == LYC
 */
static inline void change_current_line(struct CPU * cpu, int new_line) {
    cpu->gpu.current_line = new_line;
    if (new_line == cpu->gpu.lyc) {
	cpu->gpu.coincidence = true;
	gpu_stat_interrupt(cpu, cpu->gpu.coincidence_enabled);
    }
}

/*
 * gpu_next:
 * Execute a step for the GPU.
 */
void gpu_next(struct CPU * cpu) {
    if (cpu->gpu.lcd_off) return;
    
    cpu->gpu.clock++;
    
    switch(cpu->gpu.mode) {
    case 0: // Hblank
	if (cpu->gpu.clock >= 204) {
	    gpu_render_line(cpu, cpu->gpu.current_line);
	    
	    if (cpu->gpu.current_line == 143) {
		gpu_stat_interrupt(cpu, cpu->gpu.mode1_enabled);
		provoke_interruption(cpu, INT_VBLANK);
		cpu->gpu.mode = 1;
	    } else {
		change_current_line(cpu, cpu->gpu.current_line + 1);
		cpu->gpu.mode = 2;
		gpu_stat_interrupt(cpu, cpu->gpu.mode2_enabled);
	    }
	    
	    cpu->gpu.clock = 0;
	}
	break;
    case 1: // Vblank
	if (cpu->gpu.clock >= 456) {
	    change_current_line(cpu, cpu->gpu.current_line + 1);
	    if (cpu->gpu.current_line == 153) {
		// Now that a frame is complete, we do all we have to do
		handle_new_frame(cpu);
	        change_current_line(cpu, 0);
		cpu->gpu.mode  = 2;
		gpu_stat_interrupt(cpu, cpu->gpu.mode2_enabled);
	    }
	    cpu->gpu.clock = 0;
	}
	break;
    case 2: // Reading OAM
	if (cpu->gpu.clock >= 80) {
	    cpu->gpu.clock = 0;
	    cpu->gpu.mode = 3;
	    gpu_stat_interrupt(cpu, cpu->gpu.mode1_enabled);
	}
	break;
    case 3: // Reading VRAM
	if (cpu->gpu.clock >= 172) {
	    cpu->gpu.clock = 0;
	    cpu->gpu.mode = 0;
	    gpu_stat_interrupt(cpu, cpu->gpu.mode0_enabled);
	}
    }
}
