/* cpu.h --- 
 * 
 * Filename: cpu.h
 * Author: Jules <archjules>
 * Created: Wed Dec  7 09:03:16 2016 (+0100)
 * Last-Updated: Mon Jan  2 07:45:24 2017 (+0100)
 *           By: Jules <archjules>
 */

#ifndef CPU_H
#define CPU_H
#include "platform/screen.h"
#include <stdint.h>
#include <stdbool.h>

#define CPU_FLAG_Z (1 << 7)
#define CPU_FLAG_N (1 << 6)
#define CPU_FLAG_H (1 << 5)
#define CPU_FLAG_C (1 << 4)

#define FLAG_SET(f, a) (f |= (a))
#define FLAG_UNSET(f, a) (f &= ~(a))
#define FLAG_SETIF(c, f, a) if (c) { FLAG_SET((f), (a)); } else { FLAG_UNSET((f), (a)); }
#define FLAG_CLEARIF(c, f, a) FLAG_SETIF(!(c), (f), (a))

struct GPU {
    bool state;
    bool bg;
    bool bg_map;
    bool bg_tile;
    uint_fast8_t mode;
    uint_fast8_t current_line;
    uint_fast8_t scroll_x, scroll_y;
    uint_fast16_t clock;
    uint32_t bg_palette[4];
};

struct CPU {
    bool state;
    bool halted;
    bool interrupts;
    struct {
	union {
	    struct {
		uint8_t f;
		uint8_t a;
	    } __attribute__((packed));
	    uint16_t af;
	};
	union {
	    struct {
		uint8_t c;
		uint8_t b;
	    } __attribute__((packed));
	    uint16_t bc;
	};
	union {
	    struct {
		uint8_t e;
		uint8_t d;
	    } __attribute__((packed));
	    uint16_t de;
	};
	union {
	    struct {
		uint8_t l;
		uint8_t h;
	    } __attribute__((packed));
	    uint16_t hl;
	};
	uint16_t pc;
	uint16_t sp;
    } registers;

    struct {
	bool bios_inplace;
	
	uint8_t * rom;
	uint8_t * gram;
	uint8_t * eram;
	uint8_t * wram;
	uint8_t * zram;
	uint8_t oam[0x100];
	uint8_t io[0x100];
    } memory;

    struct {
	uint8_t direction;
	uint8_t buttons;
    } keys;
    
    struct GPU gpu;
    Screen * screen;

    uint_fast16_t clock;
    uint_fast8_t  time_last;
};

void cpu_next_instruction(struct CPU * cpu);
void cpu_load_rom(struct CPU * cpu, char * filename);
void cpu_destroy(struct CPU * cpu);
#endif /* CPU_H */
