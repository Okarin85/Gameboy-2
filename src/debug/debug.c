/* debug.c --- 

 * 
 * Filename: debug.c
 * Author: Jules <archjules>
 * Created: Wed Jun  7 06:03:04 2017 (+0200)
 * Last-Updated: Sun Jun 18 00:30:39 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "memory/memory.h"
#include "debug/debug.h"
#include "logger.h"

void print_registers(struct CPU * cpu) {
    char * dis = disasm(cpu, cpu->registers.pc);
    
    log_debug("AF : 0x%04x [%c%c%c%c]",
	      cpu->registers.af,
	      (cpu->registers.f & CPU_FLAG_Z) ? 'Z' : '-',
	      (cpu->registers.f & CPU_FLAG_N) ? 'N' : '-',
	      (cpu->registers.f & CPU_FLAG_H) ? 'H' : '-',
	      (cpu->registers.f & CPU_FLAG_C) ? 'C' : '-'
	);
    log_debug("BC : 0x%04x", cpu->registers.bc);
    log_debug("DE : 0x%04x", cpu->registers.de);
    log_debug("HL : 0x%04x", cpu->registers.hl);
    log_debug("PC : 0x%04x", cpu->registers.pc);
    log_debug("SP : 0x%04x", cpu->registers.sp);
    log_debug("Timer track : %d", cpu->timer_track);
    log_debug("");
    log_debug("0x%04x: %s", cpu->registers.pc, dis);

    free(dis);
}

void handle_debug_run(struct CPU * cpu) {
    if (cpu->debug.next >= 0) cpu->debug.next--;
    
    if (cpu->debug.next == 0) {
	handle_debug(cpu);
    }

    if (vector_present(cpu->debug.breakpoints, cpu->registers.pc)) {
	log_debug("Breakpoint triggered at 0x%x", cpu->registers.pc);
	handle_debug(cpu);
    }
}

void handle_debug(struct CPU * cpu) {
    char * re;
    char * buffer;
    char * command;
    bool c = true, f;
    
    cpu->debug.next = -1;
    print_registers(cpu);

    while(c) {
        buffer = readline("> ");

	if ((buffer == NULL) || (*buffer == 0)) continue;
	add_history(buffer);
	
	command = strtok_r(buffer, "\n ", &re);
	f = false;
	
	for(int i = 0; commands[i].function != NULL; i++) {
	    if ((commands[i].short_c &&
		 (strcmp(command, commands[i].short_c) == 0)) ||
		(commands[i].long_c &&
		 (strcmp(command, commands[i].long_c) == 0))) {
		c = commands[i].function(cpu, &re);
		f = true;
	    }
	}

	if (!f) {
	    printf("Command not found\n");
	}
	
	free(buffer);
    }
}
