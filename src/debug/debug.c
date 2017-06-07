/* debug.c --- 

 * 
 * Filename: debug.c
 * Author: Jules <archjules>
 * Created: Wed Jun  7 06:03:04 2017 (+0200)
 * Last-Updated: Wed Jun  7 07:01:30 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <stdio.h>
#include <string.h>
#include "debug/debug.h"
#include "logger.h"

void print_registers(struct CPU * cpu) {
    log_debug("AF : 0x%04x (Z : %x, N : %x, H : %x, C : %x)",
	      cpu->registers.af,
	      cpu->registers.f & CPU_FLAG_Z,
	      cpu->registers.f & CPU_FLAG_N,
	      cpu->registers.f & CPU_FLAG_H,
	      cpu->registers.f & CPU_FLAG_C
	);
    log_debug("BC : 0x%04x", cpu->registers.bc);
    log_debug("DE : 0x%04x", cpu->registers.de);
    log_debug("HL : 0x%04x", cpu->registers.hl);
    log_debug("PC : 0x%04x", cpu->registers.pc);
    log_debug("SP : 0x%04x", cpu->registers.sp);
}

void handle_debug_run(struct CPU * cpu) {
    bool is_break;
    
    for (int i = 0; i < cpu->debug.break_n; i++) {
	if (cpu->registers.pc == cpu->debug.breakpoints[i]) is_break = true;
    }
    
    if (cpu->debug.next || is_break) {
	cpu->debug.next = false;
	
    }
}

void handle_debug(struct CPU * cpu) {
    bool is_break;
    char buffer[255];
    char * command;
    char * arg;
    print_registers(cpu);

    while(1) {
	printf("> ");
	fgets(buffer, 255, stdin);
	    
	command = strtok(buffer, "\n ");

	if (strcmp(command, "q") == 0) {
	    // Quit
	    cpu->state = true;
	    return;
	} else if (strcmp(command, "c") == 0) {
	    // Continue
	    return;
	} else if (strcmp(command, "n") == 0) {
	    // Next
	    cpu->debug.next = true;
	    return;
	} else if (strcmp(command, "b") == 0) {
	    // Set breakpoint
	    int addr;
	    arg = strtok(NULL, "\n ");
	    sscanf(arg, "%x", &addr);
	    printf("Setting breakpoint at %#x\n", addr);

	    is_break = false;
	    for (int i = 0; i < cpu->debug.break_n; i++) {
		if (addr == cpu->debug.breakpoints[i]) is_break = true;
	    }

	    if ((cpu->debug.break_n < 0xff) && !is_break) {
		cpu->debug.breakpoints[cpu->debug.break_n] = addr;
		cpu->debug.break_n++;
	    } else if (is_break) {
		log_info("Breakpoint already set");
	    } else {
		log_warn("Too many breakpoints set");
	    }
	} else if (strcmp(command, "r") == 0) {
	    // Remove breakpoint
	    int id = -1, addr;
	    arg = strtok(NULL, "\n ");
	    sscanf(arg, "%x", &addr);
		
	    for (int i = 0; i < cpu->debug.break_n; i++) {
		if (addr == cpu->debug.breakpoints[i]) id = i;
	    }

	    if (id == -1) {
		log_warn("Breakpoint not set");
	    } else {
		printf("Removing breakpoint at %#x\n", addr);
		for (int i = id; i < (cpu->debug.break_n - 1); i++) {
		    cpu->debug.breakpoints[i] = cpu->debug.breakpoints[i + 1];
		}

		cpu->debug.break_n--;
	    }
	} else if (strcmp(command, "i") == 0) {
	    // Print all breakpoints
	    printf("%d : ", cpu->debug.break_n);
	    for (int i = 0; i < cpu->debug.break_n; i++) {
		printf("%#x", cpu->debug.breakpoints[i]);
		    
		if (i != (cpu->debug.break_n - 1)) printf(", ");
	    }

	    printf("\n");
	} 
    }
}
