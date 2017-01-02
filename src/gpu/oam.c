/* oam.c --- 
 * 
 * Filename: oam.c
 * Author: Jules <archjules>
 * Created: Fri Dec 30 01:01:21 2016 (+0100)
 * Last-Updated: Mon Jan  2 08:24:15 2017 (+0100)
 *           By: Jules <archjules>
 */
#include "cpu/cpu.h"
#include "gpu/structs.h"
#include "gpu/oam.h"
#include "logger.h"

void oam_write_byte(struct CPU * cpu, uint16_t address, uint8_t value) {
    log_debug("Writing OAM byte %x (%x)", address, value);
    return;
}

uint8_t oam_read_byte(struct CPU * cpu, uint16_t address) {
    log_debug("Reading OAM byte %x", address);
    return 0xFF;
}
