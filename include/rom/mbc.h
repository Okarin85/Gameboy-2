/* mbc.h --- 
 * 
 * Filename: mbc.h
 * Author: Jules <archjules>
 * Created: Tue Jan  3 10:26:12 2017 (+0100)
 * Last-Updated: Sat Jun 17 01:15:48 2017 (+0200)
 *           By: Jules <archjules>
 */

#ifndef MBC_H
#define MBC_H
#include "cpu/cpu.h"

/* MBC0 */
void mbc0_configure(struct CPU * cpu, char * filename);
void mbc0_free(struct CPU * cpu);

/* MBC1 */
struct MBC1 {
    bool mode;
    bool ram_enable;
    
    uint8_t rom_bank;
    uint8_t ram_bank;
    int banks;

    char * save_filename;
    uint8_t * ram;
};

void mbc1_configure(struct CPU * cpu, char * filename);
void mbc1_free(struct CPU * cpu);

/* MBC3 (incomplete) */
struct MBC3 {
    bool mode;
    bool ram_enable;
    
    uint8_t rom_bank;
    uint8_t ram_bank;

    char * save_filename;
    uint8_t * ram;
};

void mbc3_configure(struct CPU * cpu, char * filename);
void mbc3_free(struct CPU * cpu);

#endif /* MBC_H */
