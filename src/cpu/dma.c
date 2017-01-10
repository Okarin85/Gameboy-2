/* dma.c --- 
 * 
 * Filename: dma.c
 * Author: Jules <archjules>
 * Created: Mon Jan  2 08:25:32 2017 (+0100)
 * Last-Updated: Tue Jan 10 13:28:41 2017 (+0100)
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
	if (cpu->dma_dest == 0xFEA0) {
	    cpu->dma_ongoing = false;
	}
    }
}
