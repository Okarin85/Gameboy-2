/* cpu.c --- 
 * 
 * Filename: cpu.c
 * Author: Jules <archjules>
 * Created: Thu Dec  8 13:04:19 2016 (+0100)
 * Last-Updated: Mon Jan  9 19:26:06 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpu/cpu.h"
#include "cpu/timer.h"
#include "cpu/instruction.h"
#include "memory/memory.h"
#include "logger.h"

/*
 * General functions
 */
void print_registers(struct CPU * cpu) {
    log_debug("AF : 0x%04x (Z : %x, N : %x, H : %x, C : %x)",
	      cpu->registers.af,
	      cpu->registers.f & CPU_FLAG_Z,
	      cpu->registers.f & CPU_FLAG_N,
	      cpu->registers.f & CPU_FLAG_H,
	      cpu->registers.f & CPU_FLAG_C
	);
    log_debug("BC : 0x%04x", cpu->registers.bc);
    log_debug("DE : 0x%04x", cpu->registers.de);
    log_debug("HL : 0x%04x", cpu->registers.hl);
    log_debug("PC : 0x%04x", cpu->registers.pc);
    log_debug("SP : 0x%04x", cpu->registers.sp);
    log_debug("IF : 0x%02x", cpu->memory.io[0xF]);
    log_debug("IE : 0x%02x", cpu->memory.io[0xFF]);
    log_debug("TAC: 0x%02x", cpu->memory.io[0x07]);
    log_debug("TIM: 0x%02x", cpu->timer_tima);
    log_debug("Clock : %ld ticks", cpu->clock);
}

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
    
    cpu->memory.gram = malloc(0x2000);
    if (cpu->memory.gram == NULL) {
	log_fatal("Couldn't allocate memory for GRAM.");
	exit(EXIT_FAILURE);
    }

    cpu->memory.wram = malloc(0x8000);
    if (cpu->memory.wram == NULL) {
	log_fatal("Couldn't allocate memory for WRAM.");
	exit(EXIT_FAILURE);
    }

    cpu->memory.zram = malloc(0xFF);
    if (cpu->memory.zram == NULL) {
	log_fatal("Couldn't allocate memory for ZRAM.");
	exit(EXIT_FAILURE);
    }
    cpu->memory.bios_inplace = true;
    cpu->timer_tima_speed = 10;
    cpu->keys.buttons   = 0x0F;
    cpu->keys.direction = 0x0F;
    cpu->gpu.mode = 3;

    cpu->registers.pc = 0;
}

void cpu_destroy(struct CPU * cpu) {
    free(cpu->memory.gram);
    free(cpu->memory.wram);
    free(cpu->memory.zram);
}

void cpu_delay(struct CPU * cpu, int m_cycles) {
    for (int i = 0; i < (4 * m_cycles); i++) {
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
	op = read_byte(cpu, cpu->registers.pc++);
	instruction = instructions[op];
	operand = interpret_opcode(cpu, instruction);
	
	if (instruction.function == NULL) {
	    log_warn("%#04x : Instruction invalid ! (%#02x)", cpu->registers.pc - 1 - instruction.operand, op);
	    print_registers(cpu);
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

	    cpu_delay(cpu, 1);
	    treat_interruptions(cpu);
	}
    }
}
