/* interrupt.c --- 
 * 
 * Filename: interrupt.c
 * Author: Jules <archjules>
 * Created: Tue Dec 20 23:09:01 2016 (+0100)
 * Last-Updated: Thu Jan  5 17:57:23 2017 (+0100)
 *           By: Jules <archjules>
 */
#include "cpu/interrupt.h"
#include "memory/memory.h"
#include "logger.h"

void treat_interruptions(struct CPU * cpu) {
    if (cpu->interrupts) {
	for (int i = 0; i < 5; i++) {
	    // Check if the interrupt was activated, and the IE flag allows it.
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
    cpu->halted = false;
    cpu->memory.io[0x0F] |= interruption;
}
