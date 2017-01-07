/* mbc.h --- 
 * 
 * Filename: mbc.h
 * Author: Jules <archjules>
 * Created: Tue Jan  3 10:26:12 2017 (+0100)
 * Last-Updated: Thu Jan  5 18:33:42 2017 (+0100)
 *           By: Jules <archjules>
 */

#ifndef MBC_H
#define MBC_H
#include "cpu/cpu.h"

/* MBC0 */
void mbc0_configure(struct CPU * cpu);

/* MBC1 */
struct MBC1 {
    bool mode;
    bool ram_enable;
    
    uint8_t rom_bank;
    uint8_t ram_bank;

    uint8_t * ram;
};

void mbc1_configure(struct CPU * cpu);

#endif /* MBC_H */
