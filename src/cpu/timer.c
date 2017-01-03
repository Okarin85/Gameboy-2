/* timer.c --- 
 * 
 * Filename: timer.c
 * Author: Jules <archjules>
 * Created: Tue Jan  3 18:09:59 2017 (+0100)
 * Last-Updated: Tue Jan  3 19:15:25 2017 (+0100)
 *           By: Jules <archjules>
 */
#include "cpu/cpu.h"
#include "cpu/interrupt.h"
#include "logger.h"

void timer_handle(struct CPU * cpu) {
    // Handle DIV
    cpu->timer_track_div += cpu->time_last;
    if (cpu->timer_track_div >= 64) {
	cpu->timer_track_div -= 64;
	cpu->timer_div++;
    }

    // Handle TIMA
    if (cpu->timer_tima_enabled) {
	cpu->timer_track_tima += cpu->time_last;
	if (cpu->timer_track_tima >= cpu->timer_tima_speed) {
	    cpu->timer_track_tima -= cpu->timer_tima_speed;
	    cpu->timer_tima++;

	    if (cpu->timer_tima == 0) {
		provoke_interruption(cpu, INT_TIMER);
		cpu->timer_tima = cpu->timer_tma;
	    }
	}
    }
}
