/* cpu.h --- 
 * 
 * Filename: cpu.h
 * Author: Jules <archjules>
 * Created: Wed Dec  7 09:03:16 2016 (+0100)
 * Last-Updated: Fri Jun  9 11:13:42 2017 (+0200)
 *           By: Jules <archjules>
 */

#ifndef CPU_H
#define CPU_H
#include <stdint.h>
#include <stdbool.h>
#include "platform/screen.h"
#include "rom/types.h"
#include "gpu/structs.h"

#define CPU_FLAG_Z (1 << 7)
#define CPU_FLAG_N (1 << 6)
#define CPU_FLAG_H (1 << 5)
#define CPU_FLAG_C (1 << 4)

#define FLAG_SET(f, a) (f |= (a))
#define FLAG_UNSET(f, a) (f &= ~(a))
#define FLAG_SETIF(c, f, a) if (c) { FLAG_SET((f), (a)); } else { FLAG_UNSET((f), (a)); }
#define FLAG_CLEARIF(c, f, a) FLAG_SETIF(!(c), (f), (a))

struct CPU {
    bool state;
    bool halted;
    bool interrupts;
    bool halt_bug;
    bool fast_mode;
    int old_pc;
    
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
	uint8_t * rom_data;
	uint8_t * ram_data;
	
	uint8_t (*read_rom)(struct CPU *, uint16_t address);
	uint8_t (*read_ram)(struct CPU *, uint16_t address);
	void (*write_rom)(struct CPU *, uint16_t address, uint8_t value);
	void (*write_ram)(struct CPU *, uint16_t address, uint8_t value);
	void (*free)(struct CPU *);
	
	void * mbc_info;
    } rom;
    
    struct {
	bool bios_inplace;
	
	uint8_t * gram;
	uint8_t * wram;
	uint8_t * zram;
	uint8_t io[0x100];
    } memory;

    struct {
	uint8_t direction;
	uint8_t buttons;
    } keys;

    // Graphical stuff
    struct GPU gpu;
    Screen * screen;

    // DMA
    bool dma_ongoing;
    uint16_t dma_source;
    uint16_t dma_dest;

    // Debug
    struct {
	bool next;
	int breakpoints[0xff];
	int break_n;
    } debug;
    
    // Timer stuff
    int timer_track;
    
    uint8_t timer_tma;
    uint8_t timer_tima;
    uint8_t timer_tima_enabled;
    int     timer_tima_speed;
    
    uint_fast16_t clock;
    uint_fast8_t  time_last;
};

void cpu_next_instruction(struct CPU *);
void cpu_init(struct CPU *);
void cpu_delay(struct CPU *, int);
void cpu_destroy(struct CPU *);
#endif /* CPU_H */
