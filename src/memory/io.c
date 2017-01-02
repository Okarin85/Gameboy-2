/* io.c --- 
 * 
 * Filename: io.c
 * Author: Jules <archjules>
 * Created: Sun Dec 11 20:49:19 2016 (+0100)
 * Last-Updated: Mon Jan  2 11:30:07 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdint.h>
#include "cpu/cpu.h"
#include "gpu/oam.h"
#include "logger.h"

#define SCREEN_WHITE 0x00E0F8D0
#define SCREEN_LGRAY 0x0088C070
#define SCREEN_DGRAY 0x00346856
#define SCREEN_BLACK 0x00081820

static inline uint32_t get_color(int color) {
    switch(color) {
    case 0: return SCREEN_WHITE;
    case 1: return SCREEN_LGRAY;
    case 2: return SCREEN_DGRAY;
    case 3: return SCREEN_BLACK;
    }
}

uint8_t io_handle_read(struct CPU * cpu, uint8_t port) {
    switch(port) {
    case 0x00:
	if (cpu->memory.io[0x00] & 0x20) {
	    return cpu->memory.io[0x00] | cpu->keys.direction;
	} else {
	    return cpu->memory.io[0x00] | cpu->keys.buttons;
	}
    case 0x40:
	return 0x83 |
	    cpu->gpu.bg_map << 3 |
	    cpu->gpu.bg_tile<< 4;
    case 0x41:
	return (cpu->memory.io[0x41] & 0xfc) |
	    cpu->gpu.mode;
    case 0x42:
	return cpu->gpu.scroll_y;
    case 0x43:
	return cpu->gpu.scroll_x;
    case 0x44:
	return cpu->gpu.current_line;
    case 0x47:
	return cpu->memory.io[0x47];
    default:
	return 1;
    }
}

void io_handle_write(struct CPU * cpu, uint8_t port, uint8_t value) {
    int old;
    cpu->memory.io[port] = value;
    
    switch(port) {
    case 0x00:
	cpu->memory.io[port] = value & 0x30;
    case 0x0F:
	break;
    case 0x40:
	old = cpu->gpu.spr_enabled;
	cpu->gpu.spr_enabled= ((value & 0b10)   != 0);
	cpu->gpu.spr_height = ((value & 0b100)  != 0);
	cpu->gpu.bg_map     = ((value & 0b1000) != 0);
	cpu->gpu.bg_tile    = ((value & 0b10000)!= 0);

	if (old != cpu->gpu.spr_enabled) update_cache(cpu);
	break;
    case 0x42:
	cpu->gpu.scroll_y = value;
	break;
    case 0x43:
	cpu->gpu.scroll_x = value;
	break;
    case 0x45:
	log_debug("Writing LYC : %x", value);
	break;
    case 0x46:
        // Handling DMA
	cpu->dma_source = (value << 8);
	cpu->dma_dest   = 0xFE00;
	cpu->dma_ongoing= true;
	break;
    case 0x47:
	log_debug("Writing BG palette : %x", value);
	cpu->gpu.bg_palette[0] = get_color((value & 0b11));
	cpu->gpu.bg_palette[1] = get_color((value & 0b1100) >> 2);
	cpu->gpu.bg_palette[2] = get_color((value & 0b110000) >> 4);
	cpu->gpu.bg_palette[3] = get_color((value & 0b11000000) >> 6);
	break;
    case 0x48:
	log_debug("Writing OPB0 : %x", value);
	cpu->gpu.obp0[0] = get_color((value & 0b11));
	cpu->gpu.obp0[1] = get_color((value & 0b1100) >> 2);
	cpu->gpu.obp0[2] = get_color((value & 0b110000) >> 4);
	cpu->gpu.obp0[3] = get_color((value & 0b11000000) >> 6);
	break;
    case 0x49:
	log_debug("Writing OBP1 : %x", value);
	cpu->gpu.obp1[0] = get_color((value & 0b11));
	cpu->gpu.obp1[1] = get_color((value & 0b1100) >> 2);
	cpu->gpu.obp1[2] = get_color((value & 0b110000) >> 4);
	cpu->gpu.obp1[3] = get_color((value & 0b11000000) >> 6);
	break;
    case 0x50:
	cpu->memory.bios_inplace = false;
	break;
    case 0xFF:
	break;
    default:
	break;
    }
}
