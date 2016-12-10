/* memory.h --- 
 * 
 * Filename: memory.h
 * Author: Jules <archjules>
 * Created: Thu Dec  8 14:48:41 2016 (+0100)
 * Last-Updated: Sat Dec 10 22:07:11 2016 (+0100)
 *           By: Jules <archjules>
 */

#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>
#include "cpu.h"

uint8_t read_byte(struct CPU *, uint16_t);
uint16_t read_word(struct CPU *, uint16_t);
void write_byte(struct CPU *, uint16_t, uint8_t);
void write_word(struct CPU *, uint16_t, uint16_t);
uint16_t pop_word(struct CPU *);
void push_word(struct CPU *, uint16_t);

#endif /* MEMORY_H */
