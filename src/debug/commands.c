/* commands.c --- 
 * 
 * Filename: commands.c
 * Author: Jules <archjules>
 * Created: Sat Jun 10 00:32:19 2017 (+0200)
 * Last-Updated: Thu Jun 15 01:51:13 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <stdio.h>
#include <string.h>
#include "util/vector.h"
#include "memory/memory.h"
#include "rom/mbc.h"
#include "debug/debug.h"
#include "logger.h"

bool command_help(struct CPU * cpu, char ** tokens) {
    int i = 0;
    
    while(commands[i].function != NULL) {
	if (commands[i].short_c && commands[i].long_c) {
	    printf("%s, %s\t%s\n",
		   commands[i].short_c,
		   commands[i].long_c,
		   commands[i].description);
	} else if (commands[i].short_c) {
	    printf("%s\t%s\n",
		   commands[i].short_c,
		   commands[i].description);
	} else {
	    printf("%s\t%s\n",
		   commands[i].long_c,
		   commands[i].description);
	}

	i++;
    }

    return true;
}

bool command_quit(struct CPU * cpu, char ** tokens) {
    cpu->state = true;
    return false;
}

bool command_next(struct CPU * cpu, char ** tokens) {
    cpu->debug.next = read_arg_int_default(tokens, 1);
    
    return false;
}

bool command_continue(struct CPU * cpu, char ** tokens) {
    return false;
}

bool command_flip(struct CPU * cpu, char ** tokens) {
    screen_flip(cpu->screen);
    return true;
}

// Breakpoint-related commands
bool command_set_break(struct CPU * cpu, char ** tokens) {
    int addr = read_arg_int_default(tokens, -1);

    if ((addr != -1) && (!vector_present(cpu->debug.breakpoints, addr))) {
	printf("Setting breakpoint at %#x\n", addr);
	vector_expand(&cpu->debug.breakpoints, addr);
    } else if (addr == -1) {
	log_warn("An argument was expected");
    } else {
	log_warn("Breakpoint already set!");
    }
    
    return true;
}

bool command_rem_break(struct CPU * cpu, char ** tokens) {
    int addr = read_arg_int_default(tokens, -1);

    if (addr != -1) {
	if (vector_remove(&cpu->debug.breakpoints, addr)) {
	    printf("Removing breakpoint at %#x\n", addr);
	} else {
	    log_warn("Breakpoint not set");
	}
    }
    
    return true;
}

// Memory-related commands
bool command_read(struct CPU * cpu, char ** tokens) {
    int addr;
    addr = read_arg_int_default(tokens, -1);

    if (addr != -1) {
	for (int i = 0; i < 5; i++) {
	    printf("%04x: ", addr + (i << 4));
	    for (int j = 0; j < 16; j++) {
		printf("%02x ", read_byte(cpu, addr + (i << 4) + j));
	    }
	    
	    printf("\n");
	}
    }
    
    return true;
}

bool command_dis(struct CPU * cpu, char ** tokens) {
    int addr = read_arg_int_default(tokens, cpu->registers.pc);
    
    char * inst = disasm(cpu, addr);
    printf("0x%04x: %s\n", addr, inst);
    return true;
}

struct DCommand commands[] = {
    {"h", "help", "Print help", command_help},
    {"q", "quit", "Quit the emulator", command_quit},
    {"c",  NULL, "Continue the emulation", command_continue},
    {"n", "next", "Execute one instruction", command_next},
    {"f", "flip", "Flip the screen", command_flip},
    
    {"b",  NULL, "Set a breakpoint", command_set_break},
    {"r", "rem", "Remove a breakpoint", command_rem_break},

    {"x", "read", "Examine bytes at a specified address", command_read},
    {"d", "dis", "Disassemble one instruction", command_dis},
    
    {NULL, NULL, NULL, NULL}
};
