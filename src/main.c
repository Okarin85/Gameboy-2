/* main.c --- 
 * 
 * Filename: main.c
 * Author: Jules <archjules>
 * Created: Wed Dec  7 08:48:50 2016 (+0100)
 * Last-Updated: Sun Jan  8 21:40:48 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "platform/screen.h"
#include "platform/input.h"
#include "cpu/cpu.h"
#include "cpu/dma.h"
#include "cpu/instruction.h"
#include "cpu/timer.h"
#include "cpu/interrupt.h"
#include "rom/load.h"
#include "memory/memory.h"
#include "gpu/gpu.h"
#include "logger.h"

/*
 * main:
 * The entry point of the program. Parses CL arguments and loops the CPU.
 * @return: 0 in case of success.
 */
int main(int argc, char ** argv) {
    struct CPU cpu;
    char * rom_filename = NULL, c;

    while((c = getopt(argc, argv, "d")) != -1) {
	switch (c) {
	case 'd':
	    break;
	default:
	    log_warn("The %c option doesn't exist.", c);
	}
    }

    if (optind != argc) {
	rom_filename = argv[optind];
    } else {
	log_fatal("A filename must be specified.");
	return 1;
    }

    cpu_init(&cpu);
    rom_load(&cpu, rom_filename);
    cpu.screen = new_screen();

    while(!cpu.state) {
	cpu_next_instruction(&cpu);
	treat_interruptions(&cpu);
	dma_oam_handle(&cpu);
	gpu_next(&cpu);
    }

    screen_destroy(cpu.screen);
    cpu_destroy(&cpu);
    rom_free(&cpu);
    return 0;
}
