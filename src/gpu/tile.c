/* tile.c --- 
 * 
 * Filename: tile.c
 * Author: Jules <archjules>
 * Created: Sun Jan  8 11:49:48 2017 (+0100)
 * Last-Updated: Tue Jun 20 09:29:01 2017 (+0200)
 *           By: Jules <archjules>
 */
#include "cpu/cpu.h"

int tile_get_pixel(struct CPU * cpu, int bank, int id, int set, int x, int y) {
    uint8_t tile1, tile2;
    int offset = bank << 13;
    
    if(set) {
	tile1 = cpu->memory.gram[offset + id * 16 + y * 2 + 1];
	tile2 = cpu->memory.gram[offset + id * 16 + y * 2];
    } else {
	tile1 = cpu->memory.gram[offset + 0x1000 + ((int8_t)id) * 16 + y * 2 + 1];
	tile2 = cpu->memory.gram[offset + 0x1000 + ((int8_t)id) * 16 + y * 2];
    }

    return (((tile1 >> (7 - x)) & 0x1) << 1) | ((tile2 >> (7 - x)) & 0x1);
}
