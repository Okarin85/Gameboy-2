/* disasm.c --- 
 * 
 * Filename: disasm.c
 * Author: Jules <archjules>
 * Created: Fri Jun  9 22:14:25 2017 (+0200)
 * Last-Updated: Sat Jun 17 20:05:07 2017 (+0200)
 *           By: Jules <archjules>
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "memory/memory.h"
#include "cpu/cpu.h"
#include "cpu/instruction.h"

char * disasm(struct CPU * cpu, uint16_t addr) {
    char * dis = NULL;
    uint8_t opcode = read_byte(cpu, addr);
    uint16_t operand;
    
    if (opcode == 0xcb) {
	opcode = read_byte(cpu, addr + 1);
	
	struct Instruction instr = cb_instructions[opcode];
	asprintf(&dis, instr.disasm);
    } else {
	struct Instruction instr = instructions[opcode];
	switch(instr.operand) {
	case 0:
	    asprintf(&dis, instr.disasm);
	    break;
	case 1:
	    operand = read_byte(cpu, addr + 1);
	    asprintf(&dis, instr.disasm, operand);
	    break;
	case 2:
	    operand = read_word(cpu, addr + 1);
	    asprintf(&dis, instr.disasm, operand);
	    break;
	}
    }

    return dis;
}
