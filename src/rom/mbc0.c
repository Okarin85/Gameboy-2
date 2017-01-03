/* mbc0.c --- 
 * 
 * Filename: mbc0.c
 * Author: Jules <archjules>
 * Created: Tue Jan  3 10:15:59 2017 (+0100)
 * Last-Updated: Tue Jan  3 10:29:27 2017 (+0100)
 *           By: Jules <archjules>
 */
#include "cpu/cpu.h"

/* Read functions */

uint8_t mbc0_read_rom(struct CPU * cpu, uint16_t address) {
    return cpu->rom.rom_data[address];
}

uint8_t mbc0_read_ram(struct CPU * cpu, uint16_t address) {
    return 0xFF;
}

/* Write functions */

void mbc0_write_rom(struct CPU * cpu, uint16_t address, uint8_t value) {
    return;
}

void mbc0_write_ram(struct CPU * cpu, uint16_t address, uint8_t value) {
    return;
}

/* Configure function */

void mbc0_configure(struct CPU * cpu) {
    cpu->rom.read_rom = mbc0_read_rom;
    cpu->rom.read_ram = mbc0_read_ram;
    cpu->rom.write_rom= mbc0_write_rom;
    cpu->rom.write_ram= mbc0_write_ram;
}
