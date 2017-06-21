/* memory.c --- 
 * 
 * Filename: memory.c
 * Author: Jules <archjules>
 * Created: Thu Dec  8 13:40:29 2016 (+0100)
 * Last-Updated: Tue Jun 20 17:45:47 2017 (+0200)
 *           By: Jules <archjules>
 */
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#include "cpu/cpu.h"
#include "gpu/oam.h"
#include "memory/memory.h"
#include "memory/io.h"
#include "logger.h"

uint8_t read_byte(struct CPU * cpu, uint16_t address) {
    switch (address & 0xF000) {
    case 0x0000: 
	if (cpu->memory.bios_inplace && (address < 0x100))
	    return cpu->memory.bios[address];

	if (cpu->memory.bios_inplace && cpu->cgb && (address >= 0x200)) {
	    return cpu->memory.bios[address];
	}
    case 0x1000:
    case 0x2000:
    case 0x3000:
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
	return cpu->rom.read_rom(cpu, address);
    case 0x8000:
    case 0x9000:
	return cpu->memory.gram
	    [(cpu->memory.gram_bank << 13) + (address & 0x1FFF)];
    case 0xA000:
    case 0xB000:
	return cpu->rom.read_ram(cpu, address);
    case 0xC000:
	return cpu->memory.wram
	    [address & 0xFFF];
    case 0xD000:
	return cpu->memory.wram
	    [(cpu->memory.wram_bank << 12) + (address & 0xFFF)];
    case 0xE000:
    case 0xF000:
	if (address < 0xFE00) {
	    return cpu->memory.wram[address & 0x1FFF];
	} else if (address < 0xFEA0) {
	    return oam_read_byte(cpu, address & 0xFF);
	} else if (((address < 0xFF80) && (address >= 0xFF00)) || (address == 0xFFFF)) {
	    return io_handle_read(cpu, address & 0xFF);
	} else if ((address >= 0xFF80)) {
	    return cpu->memory.zram[address & 0x7F];
	}
    default:
	return 0xFF;
    }
}

uint8_t fetch_byte(struct CPU * cpu, uint16_t address) {
    uint8_t value = read_byte(cpu, address);
    cpu_delay(cpu, 1);
    return value;
}

void write_byte(struct CPU * cpu, uint16_t address, uint8_t value) {
    switch (address & 0xF000) {
    case 0x0000:
    case 0x1000:
    case 0x2000:
    case 0x3000:
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
        cpu->rom.write_rom(cpu, address, value);
	return;
    case 0x8000:
    case 0x9000:
	cpu->memory.gram
	    [(cpu->memory.gram_bank << 13) + (address & 0x1FFF)] = value;
	return;
    case 0xA000:
    case 0xB000:
	cpu->rom.write_ram(cpu, address, value);
	return;
    case 0xC000:
	cpu->memory.wram
	    [address & 0xFFF] = value;
	break;
    case 0xD000:
	cpu->memory.wram
	    [(cpu->memory.wram_bank << 12) + (address & 0xFFF)] = value;
	return;
    case 0xE000:
    case 0xF000:
	if (address < 0xFE00) {
	    cpu->memory.wram[address & 0x1FFF] = value;
	} else if (address < 0xFEA0) {
	    oam_write_byte(cpu, address & 0xFF, value);
	} else if (((address< 0xFF80) && (address >= 0xFF00)) || (address == 0xFFFF)) {
	    io_handle_write(cpu, address & 0xFF, value);
	} else if ((address >= 0xFF80)) {
	    cpu->memory.zram[address & 0x7F] = value;
	} else return;
    }
}

void store_byte(struct CPU * cpu, uint16_t address, uint8_t value) {
    write_byte(cpu, address, value);
    cpu_delay(cpu, 1);
}

uint16_t read_word(struct CPU * cpu, uint16_t address) {
    // log_debug("Reading word 0x%04x", address);
    return (read_byte(cpu, address + 1) << 8) | read_byte(cpu, address);
}

uint16_t fetch_word(struct CPU * cpu, uint16_t address) {
    return (fetch_byte(cpu, address + 1) << 8) | fetch_byte(cpu, address);
}

void write_word(struct CPU * cpu, uint16_t address, uint16_t value) {
    write_byte(cpu, address + 1, (value & 0xFF00) >> 8);
    write_byte(cpu, address, value & 0x00FF);
}

void store_word(struct CPU * cpu, uint16_t address, uint16_t value) {
    store_byte(cpu, address + 1, (value & 0xFF00) >> 8);
    store_byte(cpu, address, value & 0x00FF);    
}

uint16_t pop_word(struct CPU * cpu) {
    uint16_t value = fetch_byte(cpu, cpu->registers.sp);
    cpu->registers.sp++;
    value |= (fetch_byte(cpu, cpu->registers.sp) << 8);
    cpu->registers.sp++;
    return value;
}

void push_word(struct CPU * cpu, uint16_t value) {
    cpu->registers.sp--;
    store_byte(cpu, cpu->registers.sp, (value & 0xFF00) >> 8);
    cpu->registers.sp--;
    store_byte(cpu, cpu->registers.sp, (value & 0xFF));
}
