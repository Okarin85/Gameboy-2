/* mbc1.c --- 
 * 
 * Filename: mbc1.c
 * Author: Jules <archjules>
 * Created: Tue Jan  3 10:52:18 2017 (+0100)
 * Last-Updated: Wed Jan 11 23:16:04 2017 (+0100)
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

    return 0xFF;
}

uint8_t mbc1_read_ram(struct CPU * cpu, uint16_t address) {
    return ((struct MBC1 *)cpu->rom.mbc_info)->ram[address & 0x1FFF];
}

/* Write functions */

void mbc1_write_rom(struct CPU * cpu, uint16_t address, uint8_t value) {
    struct MBC1 * mbc_info = cpu->rom.mbc_info;
    int tmp;
    
    switch(address & 0xF000) {
    case 0x0000:
    case 0x1000:
	tmp = ((value & 0xF) == 0xA);
	((struct MBC1 *)cpu->rom.mbc_info)->ram_enable = tmp;
	if (!tmp) {
	    FILE * fp = fopen(((struct MBC1 *)cpu->rom.mbc_info)->save_filename, "w");
	    fwrite(((struct MBC1 *)cpu->rom.mbc_info)->ram, 0x2000, 1, fp);
	    fclose(fp);
	}
	break;
    case 0x2000:
    case 0x3000:
	if ((value == 0x00) || (value == 0x20) || (value == 0x40) || (value == 0x60))
	   value++;
	mbc_info->rom_bank &= ~(0x1F);
	mbc_info->rom_bank |= (value & 0x1f);
	break;
    case 0x4000:
    case 0x5000:
	printf("%x\n", value);
	sleep(2);
	break;
    case 0x6000:
    case 0x7000:
	printf("Mode select : %x\n", value);
	((struct MBC1 *)cpu->rom.mbc_info)->mode = value;
	break;
    }
}

void mbc1_write_ram(struct CPU * cpu, uint16_t address, uint8_t value) {
    ((struct MBC1 *)cpu->rom.mbc_info)->ram[address & 0x1FFF] = value;
    return;
}

/* Configure function */

void mbc1_configure(struct CPU * cpu, char * filename) {
    struct MBC1 * mbc = malloc(sizeof(struct MBC1));
    FILE * fp;
    int size;
    
    if (mbc == NULL) {
	log_fatal("Couldn't allocate memory for the MBC");
	exit(EXIT_FAILURE);
    }

    mbc->ram = malloc(0x2000);
    
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
	fread(mbc->ram, 0x2000, 1, fp);
	fclose(fp);
	log_info("Savefile loaded");
    }
    
    mbc->mode = false;
    mbc->ram_enable = false;
    
    mbc->rom_bank = 1;
    mbc->ram_bank = 0;
    
    cpu->rom.read_rom = mbc1_read_rom;
    cpu->rom.read_ram = mbc1_read_ram;
    cpu->rom.write_rom= mbc1_write_rom;
    cpu->rom.write_ram= mbc1_write_ram;
    
    cpu->rom.mbc_info = mbc;
}
