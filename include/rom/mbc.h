/* mbc.h --- 
 * 
 * Filename: mbc.h
 * Author: Jules <archjules>
 * Created: Tue Jan  3 10:26:12 2017 (+0100)
 * Last-Updated: Tue Jan 10 00:54:21 2017 (+0100)
 *           By: Jules <archjules>
 */

#ifndef MBC_H
#define MBC_H
#include "cpu/cpu.h"

/* MBC0 */
void mbc0_configure(struct CPU * cpu);
void mbc0_free(struct CPU * cpu);

/* MBC1 */
struct MBC1 {
    bool mode;
    bool ram_enable;
    
    uint8_t rom_bank;
    uint8_t ram_bank;

    uint8_t * ram;
};

void mbc1_configure(struct CPU * cpu);
void mbc1_free(struct CPU * cpu);

/* MBC3 (incomplete) */
struct MBC3 {
    bool mode;
    bool ram_enable;
    
    uint8_t rom_bank;
    uint8_t ram_bank;

    uint8_t * ram;
};

void mbc3_configure(struct CPU * cpu);
void mbc3_free(struct CPU * cpu);

#endif /* MBC_H */
