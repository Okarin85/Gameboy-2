/* main.c --- 
 * 
 * Filename: main.c
 * Author: Jules <archjules>
 * Created: Wed Dec  7 08:48:50 2016 (+0100)
 * Last-Updated: Mon Jun 19 13:12:19 2017 (+0200)
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
    char * bios_filename = NULL, c;

    cpu_init(&cpu);
    
    while((c = getopt(argc, argv, "b:df")) != -1) {
	switch (c) {
	case 'b':
	    bios_filename = optarg;
	    break;
	case 'd':
	    cpu.debug.next = 1;
	    break;
	case 'f':
	    cpu.fast_mode = true;
	    break;
	default:
	    log_warn("The %c option doesn't exist.", c);
	}
    }

    if (bios_filename == NULL) {
	log_fatal("A bootrom must be specified.");
	return 1;
    } else {
	cpu_load_bios(&cpu, bios_filename);
    }
    
    if (optind != argc) {
	rom_load(&cpu, argv[optind]);
    } else {
	log_fatal("A filename must be specified.");
	return 1;
    }

    cpu.screen = new_screen();

    while(!cpu.state) {
	cpu_next_instruction(&cpu);
    }

    screen_destroy(cpu.screen);
    cpu_destroy(&cpu);
    rom_free(&cpu);
    return 0;
}
