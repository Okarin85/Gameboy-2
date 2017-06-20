/* dma.c --- 
 * 
 * Filename: dma.c
 * Author: Jules <archjules>
 * Created: Mon Jan  2 08:25:32 2017 (+0100)
 * Last-Updated: Mon Jun 19 17:01:42 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <stdbool.h>
#include "cpu/cpu.h"
#include "gpu/oam.h"
#include "memory/memory.h"
#include "logger.h"

void dma_oam_handle(struct CPU * cpu) {
    uint8_t byte;

    if (cpu->dma_ongoing) {
	byte = read_byte(cpu, cpu->dma_source);
	oam_write_byte(cpu, cpu->dma_dest & 0xFF, byte);

	cpu->dma_source++;
	cpu->dma_dest++;

	if (cpu->dma_dest > 0xFEA0) {
	    cpu->dma_ongoing = false;
	}
    }
}

void hblank_dma_handle(struct CPU * cpu) {
    
}

void general_dma_handle(struct CPU * cpu, uint8_t value) {
    uint8_t byte;
    
    for (int i = 0; i < ((value + 1) << 4); i++) {
	byte = read_byte(cpu, cpu->hdma_source + i);
	write_byte(cpu, cpu->hdma_dest + i, byte);
    }
}
