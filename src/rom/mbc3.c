/* mbc3.c --- 
 * 
 * Filename: mbc3.c
 * Author: Jules <archjules>
 * Created: Tue Jan  3 10:52:18 2017 (+0100)
 * Last-Updated: Tue Jan 10 13:47:01 2017 (+0100)
 *           By: Jules <archjules>
 */
#include "cpu/cpu.h"
#include "rom/mbc.h"
#include "logger.h"

/* Read functions */

uint8_t mbc3_read_rom(struct CPU * cpu, uint16_t address) {
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
	bank_base = (((struct MBC3 *)cpu->rom.mbc_info)->rom_bank) * 0x4000;
	return cpu->rom.rom_data[bank_base + (address & 0x3FFF)];
    }

    return 0xFF;
}

uint8_t mbc3_read_ram(struct CPU * cpu, uint16_t address) {
    uint16_t ram_base = 0x2000 * ((struct MBC3 *)cpu->rom.mbc_info)->ram_bank;
    return ((struct MBC3 *)cpu->rom.mbc_info)->ram[ram_base + (address & 0x1FFF)];
}

/* Write functions */

void mbc3_write_rom(struct CPU * cpu, uint16_t address, uint8_t value) {
    struct MBC3 * mbc_info = cpu->rom.mbc_info;
    
    switch(address & 0xF000) {
    case 0x0000:
    case 0x1000:
	mbc_info->ram_enable = ((value & 0xF) == 0xA);
	break;
    case 0x2000:
    case 0x3000:
	if (value == 0) value = 1;
	mbc_info->rom_bank = (value & 0x7f);
	break;
    case 0x4000:
    case 0x5000:
	if (value >= 0x3)
	    mbc_info->ram_bank = value;
	break;
    case 0x6000:
    case 0x7000:
	printf("Mode select : %x\n", value);
	((struct MBC3 *)cpu->rom.mbc_info)->mode = value;
	break;
    }
}

void mbc3_write_ram(struct CPU * cpu, uint16_t address, uint8_t value) {
    uint16_t ram_base = 0x2000 * ((struct MBC3 *)cpu->rom.mbc_info)->ram_bank;
    ((struct MBC3 *)cpu->rom.mbc_info)->ram[ram_base + (address & 0x1FFF)] = value;
    return;
}

/* Configure function */

void mbc3_configure(struct CPU * cpu) {
    struct MBC3 * mbc = malloc(sizeof(struct MBC3));
    if (mbc == NULL) {
	log_fatal("Couldn't allocate memory for the MBC");
	exit(EXIT_FAILURE);
    }
    
    cpu->rom.read_rom = mbc3_read_rom;
    cpu->rom.read_ram = mbc3_read_ram;
    cpu->rom.write_rom= mbc3_write_rom;
    cpu->rom.write_ram= mbc3_write_ram;

    mbc->mode = false;
    mbc->ram_enable = false;

    mbc->ram = malloc(0x8000);
    
    mbc->rom_bank = 1;
    mbc->ram_bank = 0;

    cpu->rom.mbc_info = mbc;
}

void mbc3_free(struct CPU * cpu) {
    free(((struct MBC3 *)cpu->rom.mbc_info)->ram);
}
