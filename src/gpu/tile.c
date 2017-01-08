/* tile.c --- 
 * 
 * Filename: tile.c
 * Author: Jules <archjules>
 * Created: Sun Jan  8 11:49:48 2017 (+0100)
 * Last-Updated: Sun Jan  8 12:16:25 2017 (+0100)
 *           By: Jules <archjules>
 */
#include "cpu/cpu.h"

int tile_get_pixel(struct CPU * cpu, int tile_id, int tile_set, int x, int y) {
    uint8_t tile1, tile2;
    
    if(tile_set) {
	tile1 = cpu->memory.gram[tile_id * 16 + y * 2 + 1];
	tile2 = cpu->memory.gram[tile_id * 16 + y * 2];
    } else {
	tile1 = cpu->memory.gram[0x1000 + ((int8_t)tile_id) * 16 + y * 2 + 1];
	tile2 = cpu->memory.gram[0x1000 + ((int8_t)tile_id) * 16 + y * 2];
    }

    return ((tile1 >> (7 - x)) & 0x1) | (((tile2 >> (7 - x)) & 0x1) << 1);
}
