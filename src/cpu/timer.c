/* timer.c --- 
 * 
 * Filename: timer.c
 * Author: Jules <archjules>
 * Created: Tue Jan  3 18:09:59 2017 (+0100)
 * Last-Updated: Sun Jun 18 23:08:52 2017 (+0200)
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
	if ((cpu->timer_track & mask) == 0) {
	    cpu->timer_tima++;

	    if (cpu->timer_tima == 0) {
		trigger_interruption(cpu, INT_TIMER);
		cpu->timer_tima = cpu->timer_tma;
	    }
	}
    }
}
