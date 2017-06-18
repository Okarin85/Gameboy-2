/* load.c --- 
 * 
 * Filename: load.c
 * Author: Jules <archjules>
 * Created: Mon Jan  2 18:21:01 2017 (+0100)
 * Last-Updated: Sun Jun 18 20:25:38 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <stdio.h>
#include "cpu/cpu.h"
#include "rom/mbc.h"
#include "logger.h"

void rom_configure(struct CPU * cpu, char * filename) {
    char title[17] = {0};
    int rom_size, ram_size, mbc_type;

    memcpy(title, cpu->rom.rom_data + 0x134, 15);
    mbc_type = cpu->rom.rom_data[0x147];
    rom_size = 32768 << cpu->rom.rom_data[0x148];
    switch(cpu->rom.rom_data[0x149] & 0x3) {
    case 0:
	ram_size = 0;
	break;
    case 1:
	ram_size = 2048;
	break;
    case 2:
	ram_size = 8096;
	break;
    case 3:
	ram_size = 32768;
	break;
    }

    /* Set CPU mode */
    cpu->cgb_mode = (cpu->rom.rom_data[0x143] & 0x80) != 0;
    
    /* Allocate RAM */
    cpu->rom.ram_data = malloc(ram_size);
    if ((cpu->rom.ram_data == NULL) && (ram_size != 0)) {
	log_fatal("Couldn't allocate memory for the RAM");
	exit(EXIT_FAILURE);
    }

    log_info("ROM title : %s", title);
    log_info("ROM mode  : %s",
	     (cpu->cgb_mode) ? "CGB mode" : "Non-CGB mode");
    log_info("ROM size  : %do", rom_size);
    log_info("RAM size  : %do", ram_size);
    log_info("MBC type  : %x", mbc_type);
    
    /* Configure MBC */
    switch(mbc_type) {
    case 0x00: // MBC0
	mbc0_configure(cpu, filename);
	break;
    case 0x01: // MBC1
    case 0x02:
    case 0x03:
	mbc1_configure(cpu, filename);
	break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
	mbc3_configure(cpu, filename);
	break;
    default:
	log_fatal("MBC chip not supported !");
	exit(EXIT_FAILURE);
	break;
    }
}

void rom_load(struct CPU * cpu, char * filename) {
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
    
    cpu->rom.rom_data = malloc(size);
    if (cpu->rom.rom_data == NULL) {
	log_fatal("Couldn't allocate memory for the ROM.");
	exit(EXIT_FAILURE);
    }

    fread(cpu->rom.rom_data, 1, size, fp);
    fclose(fp);
    
    log_debug("Loaded %s", filename);
    rom_configure(cpu, filename);
}

void rom_free(struct CPU * cpu) {
    free(cpu->rom.rom_data);
}
