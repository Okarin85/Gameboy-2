/* cpu.c --- 
 * 
 * Filename: cpu.c
 * Author: Jules <archjules>
 * Created: Thu Dec  8 13:04:19 2016 (+0100)
 * Last-Updated: Mon Jun 19 01:24:03 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpu/cpu.h"
#include "cpu/dma.h"
#include "cpu/timer.h"
#include "cpu/interrupt.h"
#include "cpu/instruction.h"
#include "rom/mbc.h"
#include "gpu/gpu.h"
#include "memory/memory.h"
#include "debug/debug.h"
#include "logger.h"

/*
 * General functions
 */
static inline uint16_t interpret_opcode(struct CPU * cpu, struct Instruction opcode) {
    uint16_t operand;
    if (opcode.operand == 1) {
	operand = fetch_byte(cpu, cpu->registers.pc);
    } else if (opcode.operand == 2) {
	operand = fetch_word(cpu, cpu->registers.pc);
    }

    cpu->registers.pc += opcode.operand;
    return operand;
}

void cpu_init(struct CPU * cpu) {
    bzero(cpu, sizeof(struct CPU));
    
    cpu->memory.gram = malloc(0x4000);
    if (cpu->memory.gram == NULL) {
	log_fatal("Couldn't allocate memory for GRAM.");
	exit(EXIT_FAILURE);
    }

    cpu->memory.wram = malloc(0x20000);
    if (cpu->memory.wram == NULL) {
	log_fatal("Couldn't allocate memory for WRAM.");
	exit(EXIT_FAILURE);
    }

    cpu->memory.zram = malloc(0x80);
    if (cpu->memory.zram == NULL) {
	log_fatal("Couldn't allocate memory for ZRAM.");
	exit(EXIT_FAILURE);
    }
    cpu->memory.bios_inplace = true;
    cpu->memory.wram_bank = 1;
    cpu->memory.gram_bank = 0;
	
    cpu->timer_tima_speed = 10;
    cpu->keys.buttons   = 0x0F;
    cpu->keys.direction = 0x0F;
    cpu->gpu.mode = 2;

    cpu->registers.pc = 0;
    cpu->debug.next = -1;
}

void cpu_destroy(struct CPU * cpu) {
    free(cpu->memory.gram);
    free(cpu->memory.wram);
    free(cpu->memory.zram);
    if (cpu->rom.free) cpu->rom.free(cpu);
}

void cpu_delay(struct CPU * cpu, int m_cycles) {
    for (int i = 0; i < (m_cycles << 2); i++) {
	dma_oam_handle(cpu);
	gpu_next(cpu);
	timer_step(cpu);
    }
}

void cpu_next_instruction(struct CPU * cpu) {
    uint8_t op;
    uint16_t operand;
    
    struct Instruction instruction;
    
    if (cpu->halted) {
	cpu_delay(cpu, 1);
    } else {
	handle_debug_run(cpu);
	
	op = fetch_byte(cpu, cpu->registers.pc++);
	instruction = instructions[op];
	operand = interpret_opcode(cpu, instruction);

	if (instruction.function == NULL) {
	    log_warn("%#04x : Instruction invalid ! (%#02x)", cpu->registers.pc - 1 - instruction.operand, op);
	    sleep(10);
	} else {
	    switch(instruction.operand) {
	    case 0:
		((void (*)(struct CPU *))instruction.function)(cpu);
		break;
	    case 1:
		((void (*)(struct CPU *, uint8_t))instruction.function)(cpu, (uint8_t)operand);
		break;
	    case 2:
	        ((void (*)(struct CPU *, uint16_t))instruction.function)(cpu, operand);
		break;
	    }
	}
    }

    if((cpu->interrupt_flags & cpu->interrupt_enable) != 0)
	treat_interruptions(cpu);
}
