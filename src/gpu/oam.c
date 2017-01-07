/* oam.c --- 
 * 
 * Filename: oam.c
 * Author: Jules <archjules>
 * Created: Fri Dec 30 01:01:21 2016 (+0100)
 * Last-Updated: Sat Jan  7 19:12:39 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdlib.h>
#include <string.h>
#include "cpu/cpu.h"
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
    uint8_t spr_nb, spr_attr, old;
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
    log_debug("Reading OAM byte %x", address);
}

// Actual rendering functions
struct Sprite * oam_get_sprite(struct CPU * cpu, int x, int y) {
    int diff;
    
    for (int i = 0; i < 10; i++) {
	if(cpu->gpu.line_cache[y][i] == NULL) return NULL;

        diff = x - cpu->gpu.line_cache[y][i]->x_pos + 8;
	if ((diff < 0) || (diff > 7)) continue;
	
	return cpu->gpu.line_cache[y][i];
    }

    return NULL;
}

int oam_get_color(struct CPU * cpu, struct Sprite * sprite, int x, int y) {
    int base_spr, tile_id, x_tile, tile1, tile2;

    base_spr = (sprite->y_pos - 16);
    
    if (cpu->gpu.spr_height) {
	tile_id = sprite->tile & 0xfe;
	if ((y - base_spr) > 7) tile_id++;
    }
    
    tile1 = cpu->memory.gram[(sprite->tile << 4) + ((y - base_spr) << 1) + 1];
    tile2 = cpu->memory.gram[(sprite->tile << 4) + ((y - base_spr) << 1)];

    if (!sprite->x_flip) {
	x_tile = x % 8;
    } else {
	x_tile = 8 - (x % 8);
    }
    
    return ((tile1 >> (7 - x_tile)) & 0x1) | (((tile2 >> (7 - x_tile)) & 0x1) << 1);
}
