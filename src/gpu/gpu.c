/* gpu.c --- 
 * 
 * Filename: gpu.c
 * Author: Jules <archjules>
 * Created: Tue Dec 13 00:45:56 2016 (+0100)
 * Last-Updated: Wed Jun 21 03:08:53 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include "cpu/cpu.h"
#include "cpu/interrupt.h"
#include "gpu/gpu.h"
#include "gpu/oam.h"
#include "platform/input.h"
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
 * gpu_render_line_dmg:
 * Render a line on the screen
 */
void gpu_render_line_dmg(struct CPU * cpu, int current_line) {
    int bg_color = 0, color = 0;
    
    for (int i = 0; i < SCREEN_WIDTH; i++) {
	// Getting the background/window pixel
	if (cpu->gpu.wd_enabled && (i >= (cpu->gpu.wd_x - 7)) && (current_line >= cpu->gpu.wd_y)) {
	    bg_color = window_get_color(cpu, i, current_line);
	} else if (cpu->gpu.bg_enabled) {
	    bg_color = background_get_color_dmg(cpu, i, current_line);
	} else {
	    bg_color = 0;
	}
	if (cpu->gpu.spr_enabled)
	    color = oam_render_sprite_dmg(cpu, i, current_line, bg_color);
	else
	    color = cpu->gpu.bg_palette[bg_color];
	screen_put_pixel(cpu->screen, i, current_line, get_color(color));
    }
}

/*
 * gpu_render_line_gbc:
 * Render a line on the screen
 */
void gpu_render_line_gbc(struct CPU * cpu, int current_line) {
    int bg_color = 0, bg_palette = 0, color = 0;
    
    for (int i = 0; i < SCREEN_WIDTH; i++) {
	// Getting the background/window pixel
	if (cpu->gpu.wd_enabled && (i >= (cpu->gpu.wd_x - 7)) && (current_line >= cpu->gpu.wd_y)) {
	    bg_color = window_get_color(cpu, i, current_line);
	} else if (cpu->gpu.bg_enabled) {
	    background_get_color_gbc(cpu, i, current_line, &bg_color, &bg_palette);
	} else {
	    bg_color = 0;
	}
	
	if (cpu->gpu.spr_enabled) {
	    color = oam_render_sprite_gbc(cpu, i, current_line, bg_color);

	    if (color == -1)
		color = palette_get_color(cpu->memory.bgp, bg_palette, bg_color);
	} else
	    color = palette_get_color(cpu->memory.bgp, bg_palette, bg_color);
	
	screen_put_pixel(cpu->screen, i, current_line, color);
    }
}

void gpu_render_line(struct CPU * cpu, int current_line) {
    if (cpu->cgb)
	gpu_render_line_gbc(cpu, current_line);
    else
	gpu_render_line_dmg(cpu, current_line);
}

/*
 * gpu_stat_interrupt:
 * Request a STAT interrupt if enabled
 */
void gpu_stat_interrupt(struct CPU * cpu, uint8_t bit) {
    if (bit) {
	trigger_interruption(cpu, INT_STAT);
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
    if (!cpu->gpu.lcd_on) {
	// If LCD is off, treat events nevertheless, but only once
	// every 9120 cycles (what would be 10 frames if the LCD
	// were on)
	cpu->gpu.clock_off = (cpu->gpu.clock_off + 1) % 9120;
	if (cpu->gpu.clock_off == 0) treat_events(cpu);
	return;
    }
    
    cpu->gpu.clock++;
    
    switch(cpu->gpu.mode) {
    case 0: // Hblank
	if (cpu->gpu.clock >= 456) {
	    gpu_render_line(cpu, cpu->gpu.current_line);
	    hblank_dma_handle(cpu);
	    change_current_line(cpu, cpu->gpu.current_line + 1);
	    
	    if (cpu->gpu.current_line == 144) {
		gpu_stat_interrupt(cpu, cpu->gpu.mode1_enabled);
		trigger_interruption(cpu, INT_VBLANK);
		cpu->gpu.mode = 1;
	    } else {
		cpu->gpu.mode = 2;
		gpu_stat_interrupt(cpu, cpu->gpu.mode2_enabled);
	    }
	    
	    cpu->gpu.clock = 0;
	}
	break;
    case 1: // Vblank
	if (cpu->gpu.clock >= 456) {
	    change_current_line(cpu, cpu->gpu.current_line + 1);
	    
	    if (cpu->gpu.current_line == 154) {
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
	    cpu->gpu.mode = 3;
	    gpu_stat_interrupt(cpu, cpu->gpu.mode1_enabled);
	}
	break;
    case 3: // Reading VRAM
	if (cpu->gpu.clock >= 252) {
	    cpu->gpu.mode = 0;
	    gpu_stat_interrupt(cpu, cpu->gpu.mode0_enabled);
	}
    }
}
