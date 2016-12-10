/* cpu.c --- 
 * 
 * Filename: cpu.c
 * Author: Jules <archjules>
 * Created: Thu Dec  8 13:04:19 2016 (+0100)
 * Last-Updated: Sat Dec 10 23:04:55 2016 (+0100)
 *           By: Jules <archjules>
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "logger.h"
#include "cpu.h"
#include "memory.h"
#include "instruction.h"

/*
 * General functions
 */
static inline void print_registers(struct CPU * cpu) {
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
}

static inline uint16_t interpret_opcode(struct CPU * cpu, struct Instruction opcode, char ** str) {
    uint16_t operand;
    if (opcode.operand == 1) {
	operand = read_byte(cpu, cpu->registers.pc + 1);
    } else if (opcode.operand == 2) {
	operand = read_word(cpu, cpu->registers.pc + 1);
    }

    cpu->registers.pc += opcode.operand;
    asprintf(str, opcode.disasm, operand);
    return operand;
}

void cpu_load_rom(struct CPU * cpu, char * filename) {
    int size;
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
	log_fatal("Couldn't open %s", filename);
	exit(EXIT_FAILURE);
    }
    
    // Getting the size
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    cpu->memory.rom = malloc(size);
    if (cpu->memory.rom == NULL) {
	log_fatal("Couldn't allocate memory for the ROM.");
	exit(EXIT_FAILURE);
    }

    fread(cpu->memory.rom, 1, size, fp);

    cpu->memory.gram = malloc(0x2000);
    if (cpu->memory.gram == NULL) {
	log_fatal("Couldn't allocate memory for GRAM.");
	exit(EXIT_FAILURE);
    }

    cpu->memory.eram = malloc(0x8000);
    if (cpu->memory.rom == NULL) {
	log_fatal("Couldn't allocate memory for ERAM.");
	exit(EXIT_FAILURE);
    }

    cpu->memory.wram = malloc(0x8000);
    if (cpu->memory.wram == NULL) {
	log_fatal("Couldn't allocate memory for WRAM.");
	exit(EXIT_FAILURE);
    }

    cpu->memory.zram = malloc(0x80);
    if (cpu->memory.zram == NULL) {
	log_fatal("Couldn't allocate memory for ZRAM.");
	exit(EXIT_FAILURE);
    }
    cpu->registers.pc = 0x100;
    cpu->registers.sp = 0xFFFE;
    log_info("Loaded %s (%d bytes)", filename, size);
}

void cpu_destroy(struct CPU * cpu) {
    free(cpu->memory.rom);
    free(cpu->memory.gram);
    free(cpu->memory.eram);
    free(cpu->memory.wram);
    free(cpu->memory.zram);
}

void cpu_next_instruction(struct CPU * cpu) {
    char * str;
    uint8_t op = read_byte(cpu, cpu->registers.pc);
    uint16_t operand;
    struct Instruction instruction = instructions[op];

    operand = interpret_opcode(cpu, instruction, &str);
    if (instruction.function == NULL) {
	log_warn("%#04x : Instruction not implemented ! (%#02x, %s)", cpu->registers.pc, op, str);
	print_registers(cpu);
	sleep(10);
    } else {
	log_debug("%#04x : %s", cpu->registers.pc, str);
	switch(instruction.operand) {
	case 0:
	    ((int (*)(struct CPU *))instruction.function)(cpu);
	    break;
	case 1:
	    ((int (*)(struct CPU *, uint8_t))instruction.function)(cpu, (uint8_t)operand);
	    break;
	case 2:
	    ((int (*)(struct CPU *, uint16_t))instruction.function)(cpu, operand);
	    break;
	}
	print_registers(cpu);
    }
    free(str);
    
    cpu->registers.pc++;
}
