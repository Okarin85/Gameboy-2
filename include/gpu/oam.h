/* oam.h --- 
 * 
 * Filename: oam.h
 * Author: Jules <archjules>
 * Created: Mon Jan  2 08:07:40 2017 (+0100)
 * Last-Updated: Mon Jan  2 10:15:57 2017 (+0100)
 *           By: Jules <archjules>
 */

#ifndef OAM_H
#define OAM_H
#include <stdint.h>
#include "cpu/cpu.h"

// Flags
#define OAM_BG_PRIORITY (1 << 7)
#define OAM_X_FLIP      (1 << 6)
#define OAM_Y_FLIP      (1 << 5)
#define OAM_PALETTE     (1 << 4)

void update_cache(struct CPU *);

void oam_write_byte(struct CPU *, uint16_t, uint8_t);
uint8_t oam_read_byte(struct CPU *, uint16_t);

struct Sprite * oam_get_sprite(struct CPU *, int, int);
int oam_get_color(struct CPU *, struct Sprite *, int, int);

#endif /* OAM_H */