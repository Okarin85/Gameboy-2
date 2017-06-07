/* instruction.h --- 
 * 
 * Filename: instruction.h
 * Author: Jules <archjules>
 * Created: Thu Dec  8 12:54:40 2016 (+0100)
 * Last-Updated: Wed Jun  7 06:53:06 2017 (+0200)
 *           By: Jules <archjules>
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

struct Instruction {
    char * disasm;
    int    operand;
    void * function;
};

void cb_prefix(struct CPU *, uint8_t);
extern struct Instruction instructions[];

#endif /* INSTRUCTION_H */
