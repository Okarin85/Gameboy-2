/* main.c --- 
 * 
 * Filename: main.c
 * Author: Jules <archjules>
 * Created: Wed Dec  7 08:48:50 2016 (+0100)
 * Last-Updated: Fri Dec 23 01:26:06 2016 (+0100)
 *           By: Jules <archjules>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "memory.h"
#include "screen.h"
#include "input.h"
#include "cpu.h"
#include "gpu.h"
#include "instruction.h"
#include "interrupt.h"
#include "logger.h"

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

    bzero(&cpu, sizeof(struct CPU));
    cpu_load_rom(&cpu, rom_filename);
    cpu.screen = new_screen();
    
    while(!cpu.state) {
	cpu_next_instruction(&cpu);
	treat_interruptions(&cpu);
	gpu_next(&cpu);
	treat_events(&cpu);
    }

    screen_destroy(cpu.screen);
    cpu_destroy(&cpu);
    return 0;
}
