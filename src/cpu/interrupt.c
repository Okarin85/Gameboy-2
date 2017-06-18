/* interrupt.c --- 
 * 
 * Filename: interrupt.c
 * Author: Jules <archjules>
 * Created: Tue Dec 20 23:09:01 2016 (+0100)
 * Last-Updated: Sun Jun 18 23:08:22 2017 (+0200)
 *           By: Jules <archjules>
 */
#include "cpu/timer.h"
#include "cpu/interrupt.h"
#include "memory/memory.h"
#include "logger.h"

void treat_interruptions(struct CPU * cpu) {
    for (int i = 0; i < 5; i++) {
	// Check if the interrupt was activated, and the IE flag allows it.
	if ((cpu->interrupt_flags & (1 << i)) && (cpu->interrupt_enable & (1 << i))) {
	    cpu->halted = false;
	    
	    if (cpu->interrupts) {
		remove_interruption(cpu, 1 << i);
		
		// Calling the interruption vector
		cpu->interrupts = false;
		push_word(cpu, cpu->registers.pc);
		cpu_delay(cpu, 6);
		cpu->registers.pc = (0x40 + (i << 3));
		
		return;
	    }
	}
    }
}

/*
 * remove_interruption:
 * Remove an interruption from IF
 */
void remove_interruption(struct CPU * cpu, uint8_t interruption) {
    cpu->interrupt_flags &= ~interruption;
}

/*
 * trigger_interruption:
 * Sets halted to false, and sets a bit if 
 */
void trigger_interruption(struct CPU * cpu, uint8_t interruption) {
    cpu->interrupt_flags |= interruption;
}
