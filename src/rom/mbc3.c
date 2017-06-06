/* mbc3.c --- 
 * 
 * Filename: mbc3.c
 * Author: Jules <archjules>
 * Created: Tue Jan  3 10:52:18 2017 (+0100)
 * Last-Updated: Tue Jun  6 20:48:48 2017 (+0200)
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
	bank_base = (((struct MBC3 *)cpu->rom.mbc_info)->rom_bank) << 14;
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
    int tmp;
    
    switch(address & 0xF000) {
    case 0x0000:
    case 0x1000:
	tmp = ((value & 0xF) == 0xA);
	((struct MBC1 *)cpu->rom.mbc_info)->ram_enable = tmp;
	if (!tmp) {
	    FILE * fp = fopen(((struct MBC1 *)cpu->rom.mbc_info)->save_filename, "w");
	    fwrite(((struct MBC1 *)cpu->rom.mbc_info)->ram, 0x8000, 1, fp);
	    fclose(fp);
	}
	break;
    case 0x2000:
    case 0x3000:
	if (value == 0) value = 1;
	mbc_info->rom_bank = (value & 0x7f);
	break;
    case 0x4000:
    case 0x5000:
	if (value <= 0x3)
	    mbc_info->ram_bank = value;
	break;
    case 0x6000:
    case 0x7000:
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

void mbc3_configure(struct CPU * cpu, char * filename) {
    struct MBC3 * mbc = malloc(sizeof(struct MBC3));
    int size;
    FILE * fp;
    
    if (mbc == NULL) {
	log_fatal("Couldn't allocate memory for the MBC");
	exit(EXIT_FAILURE);
    }

    mbc->ram = malloc(0x8000);
    if (mbc->ram == NULL) {
	log_fatal("Couldn't allocate memory for the cartridge RAM");
	exit(EXIT_FAILURE);
    }
    
    size = snprintf(NULL, 0, "%s.sav", filename);
    mbc->save_filename = malloc(size);
    if (mbc->save_filename == NULL) {
	log_fatal("Couldn't allocate memory.");
	exit(EXIT_FAILURE);
    }

    snprintf(mbc->save_filename, size + 1, "%s.sav", filename);

    /* Tries to load the save */
    fp = fopen(mbc->save_filename, "r");
    if (fp != NULL) {
	fread(mbc->ram, 0x8000, 1, fp);
	fclose(fp);
	log_info("Savefile loaded");
    }
    
    mbc->mode = false;
    mbc->ram_enable = false;
    
    mbc->rom_bank = 1;
    mbc->ram_bank = 0;

    cpu->rom.read_rom = mbc3_read_rom;
    cpu->rom.read_ram = mbc3_read_ram;
    cpu->rom.write_rom= mbc3_write_rom;
    cpu->rom.write_ram= mbc3_write_ram;
    cpu->rom.free     = mbc3_free;
    
    cpu->rom.mbc_info = mbc;
}

void mbc3_free(struct CPU * cpu) {
    free(((struct MBC3 *)cpu->rom.mbc_info)->ram);
}
