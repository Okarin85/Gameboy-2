/* oam.c --- 
 * 
 * Filename: oam.c
 * Author: Jules <archjules>
 * Created: Fri Dec 30 01:01:21 2016 (+0100)
 * Last-Updated: Mon Jan  9 10:08:21 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include <string.h>
#include "cpu/cpu.h"
#include "gpu/gpu.h"
#include "gpu/structs.h"
#include "gpu/oam.h"
#include "platform/input.h"
#include "logger.h"

void cache_sprite(struct CPU * cpu, int index) {
    int pos_x = cpu->gpu.oam[index].x_pos;
    int pos_y_start = cpu->gpu.oam[index].y_pos - 16;
    int pos_y_end   = pos_y_start + (cpu->gpu.spr_height ? 16 : 8);
    
    for (int line = pos_y_start; line < pos_y_end; line++) {
	if ((line < 0) || (line > SCREEN_HEIGHT)) continue;
	if (cpu->gpu.line_cache[line][9] != NULL)  continue;

	for (int i = 0; i < 10; i++) {
	    if (cpu->gpu.line_cache[line][i] == NULL) {
		cpu->gpu.line_cache[line][i] = &cpu->gpu.oam[index];
		break;
	    } else if (pos_x < cpu->gpu.line_cache[line][i]->x_pos) {
		memmove(&(cpu->gpu.line_cache[line][i + 1]), &(cpu->gpu.line_cache[line][i]), (9 - i) * sizeof(struct Sprite *));
		cpu->gpu.line_cache[line][i] = &cpu->gpu.oam[index];
		break;
	    }
	}
    }
}

void update_cache(struct CPU * cpu) {
    // Empty cache
    memset(cpu->gpu.line_cache, 0, sizeof(cpu->gpu.line_cache));
    // Rebuild cache
    for (int i = 0; i < 40; i++) {
	cache_sprite(cpu, i);
    }
}

void oam_write_byte(struct CPU * cpu, uint16_t address, uint8_t value) {
    bool update = false;
    uint8_t spr_nb, spr_attr;
    spr_nb   = address / 4;
    spr_attr = address % 4;
    

    switch(spr_attr) {
    case 0: // Y pos
	if (cpu->gpu.oam[spr_nb].y_pos != value) {
	    cpu->gpu.oam[spr_nb].y_pos = value;
	    update = true;
	}
	break;
    case 1: // X pos
	if (cpu->gpu.oam[spr_nb].x_pos != value) {
	    cpu->gpu.oam[spr_nb].x_pos = value;
	    update = true;
	}
	break;
    case 2: // Tile number
	cpu->gpu.oam[spr_nb].tile = value;
	break;
    case 3: // Flags
	cpu->gpu.oam[spr_nb].bg_priority = (value & OAM_BG_PRIORITY) >> 7;
	cpu->gpu.oam[spr_nb].y_flip      = (value & OAM_Y_FLIP) >> 6;
	cpu->gpu.oam[spr_nb].x_flip      = (value & OAM_X_FLIP) >> 5;
	cpu->gpu.oam[spr_nb].palette     = (value & OAM_PALETTE) >> 4;
	break;
    }

    if (update) update_cache(cpu);
    return;
}

uint8_t oam_read_byte(struct CPU * cpu, uint16_t address) {
    int spr_nb, spr_attr;
    spr_nb   = address / 4;
    spr_attr = address % 4;

    switch(spr_attr) {
    case 0: return cpu->gpu.oam[spr_nb].y_pos;
    case 1: return cpu->gpu.oam[spr_nb].x_pos;
    case 2: return cpu->gpu.oam[spr_nb].tile;
    case 3: return
	    cpu->gpu.oam[spr_nb].bg_priority << 7 |
	    cpu->gpu.oam[spr_nb].y_flip      << 6 |
	    cpu->gpu.oam[spr_nb].x_flip      << 5 |
	    cpu->gpu.oam[spr_nb].palette     << 4;
    }
}

uint32_t oam_render_sprite(struct CPU * cpu, int x, int y, int bg_color) {
    int sprite_x, sprite_y, height, tile_id, color;
    
    for (int i = 0; i < 10; i++) {
	if (cpu->gpu.line_cache[y][i] == NULL) break;
	
	sprite_x = x - (cpu->gpu.line_cache[y][i]->x_pos - 8);
	sprite_y = y - (cpu->gpu.line_cache[y][i]->y_pos - 16);
	if (sprite_x >= 8) continue;
	if (sprite_x <  0) break;
	if (cpu->gpu.line_cache[y][i]->bg_priority && (bg_color != 0)) continue;
	
	// Now we have the sprite, we get the colour
	if (cpu->gpu.spr_height) {
	    height  = 15;
	    tile_id = cpu->gpu.line_cache[y][i]->tile & 0xfe;
	} else {
	    height  = 7;
	    tile_id = cpu->gpu.line_cache[y][i]->tile;
	}

	if (cpu->gpu.line_cache[y][i]->x_flip)
	    sprite_x = 7 - sprite_x;

	if (cpu->gpu.line_cache[y][i]->y_flip)
	    sprite_y = height - sprite_y;

	color = tile_get_pixel(cpu, tile_id, 1, sprite_x, sprite_y);
	if (color != 0) {
	    if (cpu->gpu.line_cache[y][i]->palette) {
		return cpu->gpu.obp1[color];
	    } else {
		return cpu->gpu.obp0[color];
	    }
	}
    }

    return cpu->gpu.bg_palette[bg_color];
}
