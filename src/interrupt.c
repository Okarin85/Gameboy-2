/* interrupt.c --- 
 * 
 * Filename: interrupt.c
 * Author: Jules <archjules>
 * Created: Tue Dec 20 23:09:01 2016 (+0100)
 * Last-Updated: Fri Dec 23 19:02:58 2016 (+0100)
 *           By: Jules <archjules>
 */
#include "logger.h"
#include "memory.h"
#include "interrupt.h"

void treat_interruptions(struct CPU * cpu) {
    if (cpu->interrupts) {
	for (int i = 0; i < 5; i++) {
	    // Check if the interrupt was actitaved, and the IE flag allows it.
	    if ((cpu->memory.io[0x0F] & (1 << i)) && (cpu->memory.io[0xFF] & (1 << i))) {
		remove_interruption(cpu, 1 << i);

		// Calling the interruption vector
		cpu->interrupts = false;
		push_word(cpu, cpu->registers.pc);
		cpu->registers.pc = (0x40 + i * 0x8);
	    }
	}
    }
}

void remove_interruption(struct CPU * cpu, uint8_t interruption) {
    cpu->memory.io[0x0F] &= ~interruption;
}

void provoke_interruption(struct CPU * cpu, uint8_t interruption) {
    cpu->memory.io[0x0F] |= interruption;
}
