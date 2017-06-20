/* cpu.h --- 
 * 
 * Filename: cpu.h
 * Author: Jules <archjules>
 * Created: Wed Dec  7 09:03:16 2016 (+0100)
 * Last-Updated: Mon Jun 19 17:04:22 2017 (+0200)
 *           By: Jules <archjules>
 */

#ifndef CPU_H
#define CPU_H
#include <stdint.h>
#include <stdbool.h>
#include "util/vector.h"
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
    bool cgb_mode;
    bool cgb;
    bool halt_bug;
    bool fast_mode;
    bool joypad_mode;

    uint8_t interrupt_flags;
    uint8_t interrupt_enable;

    int bgp_index;
    int obp_index;
    bool bgp_increment;
    bool obp_increment;
    
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
	int  wram_bank;
	int  gram_bank;

	uint8_t * bios;
	uint8_t * gram;
	uint8_t * wram;
	uint8_t * zram;
	uint8_t bgp[0x40];
	uint8_t obp[0x40];
    } memory;

    struct {
	uint8_t direction;
	uint8_t buttons;
    } keys;

    // Graphical stuff
    struct GPU gpu;
    Screen screen;

    // DMA
    bool dma_ongoing;
    uint16_t dma_source;
    uint16_t dma_dest;

    // HDMA
    bool hdma_ongoing;
    uint8_t  hdma_length;
    uint16_t hdma_source;
    uint16_t hdma_dest;

    // Debug
    struct {
	int next;
	struct Vector breakpoints;
    } debug;
    
    // Timer stuff
    uint16_t timer_track;
    
    uint8_t timer_tma;
    uint8_t timer_tima;
    uint8_t timer_tima_enabled;
    int     timer_tima_speed;
    
    uint_fast16_t clock;
    uint_fast8_t  time_last;
};

void cpu_next_instruction(struct CPU *);
void cpu_init(struct CPU *);
void cpu_load_bios(struct CPU *, char *);
void cpu_delay(struct CPU *, int);
void cpu_destroy(struct CPU *);
#endif /* CPU_H */
