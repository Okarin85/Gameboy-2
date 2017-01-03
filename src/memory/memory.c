/* memory.c --- 
 * 
 * Filename: memory.c
 * Author: Jules <archjules>
 * Created: Thu Dec  8 13:40:29 2016 (+0100)
 * Last-Updated: Tue Jan  3 10:42:53 2017 (+0100)
 *           By: Jules <archjules>
 */
#include "cpu/cpu.h"
#include "gpu/oam.h"
#include "memory/memory.h"
#include "memory/io.h"
#include "logger.h"

static uint8_t gb_bios[] = {
    0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
    0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
    0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
    0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
    0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
    0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
    0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
    0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
    0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xF2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
    0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
    0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
    0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
    0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
    0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
    0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
    0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
};

uint8_t read_byte(struct CPU * cpu, uint16_t address) {
    //  log_debug("Reading byte 0x%04x", address);
    switch (address & 0xF000) {
    case 0x0000:
	if (cpu->memory.bios_inplace && (address < 0x100)) return gb_bios[address];
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
	return cpu->memory.gram[address & 0x1FFF];
    case 0xA000:
    case 0xB000:
	return cpu->rom.read_ram(cpu, address);
    case 0xC000:
    case 0xD000:
	return cpu->memory.wram[address & 0x1FFF];
    case 0xE000:
    case 0xF000:
	if (address < 0xFE00) {
	    return cpu->memory.wram[address & 0x1FFF];
	} else if (address < 0xFEA0) {
	    return oam_read_byte(cpu, address & 0xFF);
	} else if (((address< 0xFF80) && (address >= 0xFF00)) || (address == 0xFFFF)) {
	    return io_handle_read(cpu, address & 0xFF);
	} else if ((address >= 0xFF80)) {
	    return cpu->memory.zram[address & 0xFF];
	} else return 0;
    }
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
	cpu->memory.gram[address & 0x1FFF] = value;
	return;
    case 0xA000:
    case 0xB000:
	cpu->rom.write_ram(cpu, address, value);
    case 0xC000:
    case 0xD000:
	cpu->memory.wram[address & 0x1FFF] = value;
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
	    cpu->memory.zram[address & 0xFF] = value;
	} else return;
    }
}

uint16_t read_word(struct CPU * cpu, uint16_t address) {
    // log_debug("Reading word 0x%04x", address);
    return (read_byte(cpu, address + 1) << 8) | read_byte(cpu, address);
}

void write_word(struct CPU * cpu, uint16_t address, uint16_t value) {
    write_byte(cpu, address + 1, (value & 0xFF00) >> 8);
    write_byte(cpu, address, value & 0x00FF);
}

uint16_t pop_word(struct CPU * cpu) {
    uint16_t value = read_word(cpu, cpu->registers.sp);
    cpu->registers.sp += 2;
    return value;
}

void push_word(struct CPU * cpu, uint16_t value) {
    cpu->registers.sp -= 2;
    write_word(cpu, cpu->registers.sp, value);
}
