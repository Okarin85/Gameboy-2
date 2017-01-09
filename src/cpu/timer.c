/* timer.c --- 
 * 
 * Filename: timer.c
 * Author: Jules <archjules>
 * Created: Tue Jan  3 18:09:59 2017 (+0100)
 * Last-Updated: Sun Jan  8 21:41:10 2017 (+0100)
 *           By: Jules <archjules>
 */
#include "cpu/cpu.h"
#include "cpu/interrupt.h"
#include "logger.h"

void timer_step(struct CPU * cpu) {
    int mask;
    cpu->timer_track++;

    // Handle TIMA
    if (cpu->timer_tima_enabled) {
	mask = (1 << cpu->timer_tima_speed) - 1;
	// printf("%x & %x = %x, %x\n", cpu->timer_track, mask, cpu->timer_track & mask, cpu->timer_tima);
	if ((cpu->timer_track & mask) == 0) {
	    cpu->timer_tima++;

	    if (cpu->timer_tima == 0) {
		provoke_interruption(cpu, INT_TIMER);
		cpu->timer_tima = cpu->timer_tma;
	    }
	}
    }
}

void timer_handle(struct CPU * cpu, int cycles) {
    // printf("Handle ! (%d)\n", cpu->time_last);
    for (int i = 0; i < (cycles * 4); i++) {
	timer_step(cpu);
    }
}
