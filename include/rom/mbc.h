/* mbc.h --- 
 * 
 * Filename: mbc.h
 * Author: Jules <archjules>
 * Created: Tue Jan  3 10:26:12 2017 (+0100)
 * Last-Updated: Mon Jan  9 09:22:36 2017 (+0100)
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

#endif /* MBC_H */
