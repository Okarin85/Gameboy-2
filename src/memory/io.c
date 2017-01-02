/* io.c --- 
 * 
 * Filename: io.c
 * Author: Jules <archjules>
 * Created: Sun Dec 11 20:49:19 2016 (+0100)
 * Last-Updated: Mon Jan  2 07:50:13 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdint.h>
#include "cpu/cpu.h"
#include "logger.h"

#define SCREEN_WHITE 0x00FFFFFF
#define SCREEN_LGRAY 0x00AAAAAA
#define SCREEN_DGRAY 0x00555555
#define SCREEN_BLACK 0x00000000

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
    cpu->memory.io[port] = value;
    
    switch(port) {
    case 0x00:
	cpu->memory.io[port] = value & 0x30;
    case 0x0F:
	break;
    case 0x40:
	cpu->gpu.bg_map = ((value & 0b1000) != 0);
	cpu->gpu.bg_tile= ((value & 0b10000)!= 0);
	log_debug("BG_Map = %d", cpu->gpu.bg_map);
	log_debug("BG_Tile = %d", cpu->gpu.bg_tile);
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
    case 0x47:
	log_debug("Writing BG palette : %x", value);
	cpu->gpu.bg_palette[0] = get_color((value & 0b11));
	cpu->gpu.bg_palette[1] = get_color((value & 0b1100) >> 2);
	cpu->gpu.bg_palette[2] = get_color((value & 0b110000) >> 4);
	cpu->gpu.bg_palette[3] = get_color((value & 0b11000000) >> 6);
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
