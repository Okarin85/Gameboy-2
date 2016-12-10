/* memory.c --- 
 * 
 * Filename: memory.c
 * Author: Jules <archjules>
 * Created: Thu Dec  8 13:40:29 2016 (+0100)
 * Last-Updated: Sat Dec 10 22:05:39 2016 (+0100)
 *           By: Jules <archjules>
 */
#include "logger.h"
#include "memory.h"
#include "cpu.h"

uint8_t read_byte(struct CPU * cpu, uint16_t address) {
    log_debug("Reading byte 0x%04x", address);
    switch (address & 0xF000) {
    case 0x0000:
    case 0x1000:
    case 0x2000:
    case 0x3000:
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
	return cpu->memory.rom[address];
    case 0x8000:
    case 0x9000:
	return cpu->memory.gram[address & 0x7FFF];
    case 0xA000:
    case 0xB000:
	return cpu->memory.eram[address & 0x1FFF];
    case 0xC000:
    case 0xD000:
	return cpu->memory.wram[address & 0x1FFF];
    case 0xE000:
    case 0xF000:
	if (address < 0xFE00) {
	    return cpu->memory.wram[address & 0x1FFF];
	} else if (address < 0xFEA0) {
	    return cpu->memory.oam [address & 0xFF];
	} else if ((address< 0xFF80) && (address >= 0xFF00)) {
	    return cpu->memory.io  [address & 0xFF];
	} else if ((address >= 0xFF80)) {
	    return cpu->memory.zram[address & 0x7F];
	} else return 0;
    }
}

void write_byte(struct CPU * cpu, uint16_t address, uint8_t value) {
    log_debug("Writing byte 0x%04x (0%x)", address, value);
    switch (address & 0xF000) {
    case 0x0000:
    case 0x1000:
    case 0x2000:
    case 0x3000:
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
	cpu->memory.rom[address] = value;
	return;
    case 0x8000:
    case 0x9000:
	cpu->memory.gram[address & 0x7FFF] = value;
	return;
    case 0xA000:
    case 0xB000:
	cpu->memory.eram[address & 0x1FFF] = value;
	return;
    case 0xC000:
    case 0xD000:
	cpu->memory.wram[address & 0x1FFF] = value;
	return;
    case 0xE000:
    case 0xF000:
	if (address < 0xFE00) {
	    cpu->memory.wram[address & 0x1FFF] = value;
	} else if (address < 0xFEA0) {
	    cpu->memory.oam [address & 0xFF] = value;
	} else if ((address< 0xFF80) && (address >= 0xFF00)) {
	    cpu->memory.io  [address & 0xFF] = value;
	} else if ((address >= 0xFF80)) {
	    cpu->memory.zram[address & 0x7F] = value;
	} else return;
    }
}

uint16_t read_word(struct CPU * cpu, uint16_t address) {
    log_debug("Reading word 0x%04x", address);
    return (read_byte(cpu, address + 1) << 8) | read_byte(cpu, address);
}

void write_word(struct CPU * cpu, uint16_t address, uint16_t value) {
    write_byte(cpu, address + 1, (value & 0xFF00) >> 8);
    write_byte(cpu, address, value & 0x00FF);
}

uint16_t pop_word(struct CPU * cpu) {
    uint16_t value = read_word(cpu, cpu->registers.sp);
    cpu->registers.sp += 2;
}

void push_word(struct CPU * cpu, uint16_t value) {
    cpu->registers.sp -= 2;
    write_word(cpu, cpu->registers.sp, value);
}
