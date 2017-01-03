/* mbc1.c --- 
 * 
 * Filename: mbc1.c
 * Author: Jules <archjules>
 * Created: Tue Jan  3 10:52:18 2017 (+0100)
 * Last-Updated: Tue Jan  3 12:01:59 2017 (+0100)
 *           By: Jules <archjules>
 */
#include "cpu/cpu.h"
#include "rom/mbc.h"
#include "logger.h"

/* Read functions */

uint8_t mbc1_read_rom(struct CPU * cpu, uint16_t address) {
    int bank_base;
    
    switch(address & 0xF000) {
    case 0x0000:
    case 0x1000:
    case 0x2000:
    case 0x3000:
	return cpu->rom.rom_data[address];
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
	bank_base = (((struct MBC1 *)cpu->rom.mbc_info)->rom_bank) * 0x4000;
	return cpu->rom.rom_data[bank_base + (address & 0x3FFF)];
    }
}

uint8_t mbc1_read_ram(struct CPU * cpu, uint16_t address) {
    return 0xFF;
}

/* Write functions */

void mbc1_write_rom(struct CPU * cpu, uint16_t address, uint8_t value) {
    int bank;
    
    switch(address) {
    case 0x0000:
    case 0x0001:
	((struct MBC1 *)cpu->rom.mbc_info)->ram_enable = ((value & 0xF) == 0xA);
	break;
    case 0x0002:
    case 0x0003:
	if ((value == 0x00) || (value == 0x20) || (value == 0x40) || (value == 0x60))
	    value++;
	((struct MBC1 *)cpu->rom.mbc_info)->rom_bank = value;
	break;
    }
}

void mbc1_write_ram(struct CPU * cpu, uint16_t address, uint8_t value) {
    return;
}

/* Configure function */

void mbc1_configure(struct CPU * cpu) {
    struct MBC1 * mbc = malloc(sizeof(struct MBC1));
    if (mbc == NULL) {
	log_fatal("Couldn't allocate memory for the MBC");
	exit(EXIT_FAILURE);
    }
    
    cpu->rom.read_rom = mbc1_read_rom;
    cpu->rom.read_ram = mbc1_read_ram;
    cpu->rom.write_rom= mbc1_write_rom;
    cpu->rom.write_ram= mbc1_write_ram;

    mbc->mode = false;
    mbc->ram_enable = false;

    mbc->rom_bank = 1;
    mbc->ram_bank = 0;

    cpu->rom.mbc_info = mbc;
}
