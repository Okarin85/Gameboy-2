/* io.c --- 
 * 
 * Filename: io.c
 * Author: Jules <archjules>
 * Created: Sun Dec 11 20:49:19 2016 (+0100)
 * Last-Updated: Mon Jun 19 21:52:15 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <stdint.h>
#include "cpu/cpu.h"
#include "platform/screen.h"
#include "gpu/oam.h"
#include "logger.h"

uint8_t io_handle_read(struct CPU * cpu, uint8_t port) {
    switch(port) {
    case 0x00:
	if (cpu->joypad_mode) {
	    return 0xE0 | cpu->keys.direction;
	} else {
	    return 0xD0 | cpu->keys.buttons;
	}
    case 0x01:
	return 0;
    case 0x02:
	return 0;
    case 0x04:
	return (uint8_t)(cpu->timer_track >> 8);
    case 0x05:
	return cpu->timer_tima;
    case 0xF:
	return cpu->interrupt_flags;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
	return 0;
	break;
    case 0x40:
	return
	    cpu->gpu.lcd_on     << 7 |
	    cpu->gpu.wd_map     << 6 |
	    cpu->gpu.wd_enabled << 5 |
	    cpu->gpu.bg_tile    << 4 |
	    cpu->gpu.bg_map     << 3 |
	    cpu->gpu.spr_height << 2 |
	    cpu->gpu.spr_enabled<< 1 |
	    cpu->gpu.bg_enabled << 0;
    case 0x41:
	return
	    (cpu->gpu.coincidence_enabled << 6) |
	    (cpu->gpu.mode2_enabled << 5) |
	    (cpu->gpu.mode1_enabled << 4) |
	    (cpu->gpu.mode0_enabled << 3) |
	    (cpu->gpu.coincidence   << 2) |
	    cpu->gpu.mode;
    case 0x42:
	return cpu->gpu.scroll_y;
    case 0x43:
	return cpu->gpu.scroll_x;
    case 0x44:
	return cpu->gpu.current_line;
    case 0x46:
	return (cpu->dma_source >> 8);
    case 0x47:
	return
	    cpu->gpu.bg_palette[0] |
	    cpu->gpu.bg_palette[1] << 2 |
	    cpu->gpu.bg_palette[2] << 4 |
	    cpu->gpu.bg_palette[3] << 6;
    case 0x48:
	return
	    cpu->gpu.obp0[1] << 2 |
	    cpu->gpu.obp0[2] << 4 |
	    cpu->gpu.obp0[3] << 6;
    case 0x49:
	return
	    cpu->gpu.obp1[1] << 2 |
	    cpu->gpu.obp1[2] << 4 |
	    cpu->gpu.obp1[3] << 6;
    case 0x4A:
	return cpu->gpu.wd_y;
    case 0x4B:
	return cpu->gpu.wd_x;
    case 0x4D:
	return 0;
    case 0x4F:
	return cpu->memory.gram_bank;
    case 0x55:
	if (cpu->cgb_mode) {
	    if (cpu->hdma_ongoing) {
		return 0;
	    } else {
		return 0xFF;
	    }
	}
	
	break;
    case 0x68:
	if (cpu->cgb_mode) {
	    return (cpu->bgp_increment) ?
		(0x80 | cpu->bgp_index) : cpu->bgp_index;
	}
	
	break;
    case 0x69:
	if (cpu->cgb_mode) {
	    return cpu->memory.bgp[cpu->bgp_index];
	}

	break;
    case 0x6a:
	if (cpu->cgb_mode) {
	    return (cpu->obp_increment) ?
		(0x80 | cpu->obp_index) : cpu->obp_index;
	}
	
	break;
    case 0x6b:
	if (cpu->cgb_mode) {
	    return cpu->memory.obp[cpu->obp_index];
	}

	break;
    case 0x70:
	if (cpu->cgb_mode) {
	    return cpu->memory.wram_bank;
	}

	break;
    case 0xFF:
	return cpu->interrupt_enable;
    default:
	log_warn("Reading unmapped register : 0xff%x", port);
        break;
    }

    return 0xFF;
}

void io_handle_write(struct CPU * cpu, uint8_t port, uint8_t value) {
    int old;
    switch(port) {
    case 0x00: // JOYP
	cpu->joypad_mode = (value & 0x20) != 0;
	break;
    case 0x04: // DIV
	cpu->timer_track = 0;
	break;
    case 0x05: // TIMA
	cpu->timer_tima= value;
	break;
    case 0x06: // TMA
	cpu->timer_tma = value;
	break;
    case 0x07: // TAC
	cpu->timer_tima_enabled = (value & 0x04);
	switch(value & 0x03) {
	case 0x00:
	    cpu->timer_tima_speed = 10;
	    break;
	case 0x01:
	    cpu->timer_tima_speed = 4;
	    break;
	case 0x02:
	    cpu->timer_tima_speed = 6;
	    break;
	case 0x03:
	    cpu->timer_tima_speed = 8;
	}
	break;
    case 0x0F: // IF
	cpu->interrupt_flags = value;
	break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
    case 0x3e:
    case 0x3f:
	break;
    case 0x40:
	old = cpu->gpu.spr_enabled;
	cpu->gpu.bg_enabled = ((value & (1 << 0)) != 0);
	cpu->gpu.spr_enabled= ((value & (1 << 1)) != 0);
	cpu->gpu.spr_height = ((value & (1 << 2)) != 0);
	cpu->gpu.bg_map     = ((value & (1 << 3)) != 0);
	cpu->gpu.bg_tile    = ((value & (1 << 4)) != 0);
	cpu->gpu.wd_enabled = ((value & (1 << 5)) != 0);
	cpu->gpu.wd_map     = ((value & (1 << 6)) != 0);
	cpu->gpu.lcd_on     = ((value & (1 << 7)) != 0);

	if (!cpu->gpu.lcd_on) {
	    cpu->gpu.mode = 0;
	    cpu->gpu.clock = 0;
	    cpu->gpu.current_line = 0;
	}
	
	if (old != cpu->gpu.spr_enabled) update_cache(cpu);
	break;
    case 0x41:
	cpu->gpu.coincidence_enabled = (value & 0x40) != 0;
	cpu->gpu.mode2_enabled       = (value & 0x20) != 0;
	cpu->gpu.mode1_enabled       = (value & 0x10) != 0;
	cpu->gpu.mode0_enabled       = (value & 0x08) != 0;
	break;
    case 0x42:
	cpu->gpu.scroll_y = value;
	break;
    case 0x43:
	cpu->gpu.scroll_x = value;
	break;
    case 0x45:
	cpu->gpu.lyc = value;
	break;
    case 0x46:
        // Handling DMA
	cpu->dma_source = (value << 8);
	cpu->dma_dest   = 0xFE00;
	cpu->dma_ongoing= true;
	break;
    case 0x47:
	cpu->gpu.bg_palette[0] = (value & 0b11);
	cpu->gpu.bg_palette[1] = (value & 0b1100) >> 2;
	cpu->gpu.bg_palette[2] = (value & 0b110000) >> 4;
	cpu->gpu.bg_palette[3] = (value & 0b11000000) >> 6;
	break;
    case 0x48:
	cpu->gpu.obp0[1] = (value & 0b1100) >> 2;
	cpu->gpu.obp0[2] = (value & 0b110000) >> 4;
	cpu->gpu.obp0[3] = (value & 0b11000000) >> 6;
	break;
    case 0x49:
	cpu->gpu.obp1[1] = (value & 0b1100) >> 2;
	cpu->gpu.obp1[2] = (value & 0b110000) >> 4;
	cpu->gpu.obp1[3] = (value & 0b11000000) >> 6;
	break;
    case 0x4A:
	cpu->gpu.wd_y = value;
	break;
    case 0x4B:
	cpu->gpu.wd_x = value;
	break;
    case 0x4C:
	break;
    case 0x4F:
	cpu->memory.gram_bank = (value & 1);
	break;
    case 0x50:
	cpu->memory.bios_inplace = false;
	break;
    case 0x51:
	if (cpu->cgb_mode) {
	    cpu->hdma_source &= 0xFF;
	    cpu->hdma_source |= (value << 8);
	}

	break;
    case 0x52:
	if (cpu->cgb_mode) {
	    cpu->hdma_source &= 0xFF00;
	    cpu->hdma_source |= (value & 0xF0);
	}

	break;
    case 0x53:
	if (cpu->cgb_mode) {
	    cpu->hdma_dest &= 0xFF;
	    cpu->hdma_dest |= (value << 8);
	}

	break;
    case 0x54:
	if (cpu->cgb_mode) {
	    cpu->hdma_dest &= 0xFF00;
	    cpu->hdma_dest |= (value & 0xF0);
	}

	break;
    case 0x55:
	if (cpu->cgb_mode) {
	    if (value & 0x80) {
		log_warn("H-Blank DMA is not yet implemented");
		cpu->hdma_ongoing = true;
	    } else {
		general_dma_handle(cpu, value & 0x7F);
	    }
	}
	
	break;
    case 0x68:
	if (cpu->cgb_mode) {
	    cpu->bgp_index = value & 0x3f;
	    cpu->bgp_increment = (value & 0x80) != 0;
	}

	break;
    case 0x69:
	if (cpu->cgb_mode) {
	    cpu->memory.bgp[cpu->bgp_index] = value;
	    
	    if (cpu->bgp_increment) {
		cpu->bgp_index++;
	    }
	}

	break;
    case 0x6a:
	if (cpu->cgb_mode) {
	    cpu->obp_index = value & 0x3f;
	    cpu->obp_increment = (value & 0x80) != 0;
	}

	break;
    case 0x6b:
	if (cpu->cgb_mode) {
	    cpu->memory.obp[cpu->obp_index] = value;
	    
	    if (cpu->obp_increment) {
		cpu->obp_index++;
	    }
	}

	break;
    case 0x70:
	if(cpu->cgb_mode) {
	    if (value == 0) value |= 1;
	    cpu->memory.wram_bank = value;
	}
	
	break;
    case 0xFF:
	cpu->interrupt_enable = value;
	break;
    default:
	log_warn("Writing unmapped register : 0xff%x (%x)", port, value);
	break;
    }
}
