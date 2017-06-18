/* interrupt.h --- 
 * 
 * Filename: interrupt.h
 * Author: Jules <archjules>
 * Created: Tue Dec 20 23:09:38 2016 (+0100)
 * Last-Updated: Sun Jun 18 23:14:27 2017 (+0200)
 *           By: Jules <archjules>
 */

#ifndef INTERRUPT_H
#define INTERRUPT_H
#define INT_VBLANK (1 << 0)
#define INT_STAT   (1 << 1)
#define INT_TIMER  (1 << 2)
#define INT_SERIAL (1 << 3)
#define INT_JOYPAD (1 << 4)

#include "cpu/cpu.h"

void treat_interruptions(struct CPU *);
void trigger_interruption(struct CPU *, uint8_t);
void remove_interruption(struct CPU *, uint8_t);

#endif /* INTERRUPT_H */
