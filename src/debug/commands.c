/* commands.c --- 
 * 
 * Filename: commands.c
 * Author: Jules <archjules>
 * Created: Sat Jun 10 00:32:19 2017 (+0200)
 * Last-Updated: Sat Jun 10 23:21:52 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <stdio.h>
#include <string.h>
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

bool command_info(struct CPU * cpu, char ** tokens) {
    bool is_break; char * arg; int addr;
    arg = strtok_r(NULL, "\n ", tokens);
    sscanf(arg, "%x", &addr);

    printf("PC : 0x%04x\n", cpu->history_pc[0xff - addr]);
    printf("SP : 0x%04x\n", cpu->history_sp[0xff - addr]);
    
    return true;
}

bool command_quit(struct CPU * cpu, char ** tokens) {
    cpu->state = true;
    return false;
}

bool command_next(struct CPU * cpu, char ** tokens) {
    char * arg; int addr;
    arg = strtok_r(NULL, "\n ", tokens);
    
    if (arg != NULL) {
	sscanf(arg, "%d", &addr);
	cpu->debug.next = addr;
    } else {
	cpu->debug.next = 1;
    }
    
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
    bool is_break; char * arg; int addr;
    arg = strtok_r(NULL, "\n ", tokens);
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

    return true;
}

bool command_rem_break(struct CPU * cpu, char ** tokens) {
    char * arg; int id = -1, addr;
    arg = strtok_r(NULL, "\n ", tokens);
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

    return true;
}

// Memory-related commands
bool command_read(struct CPU * cpu, char ** tokens) {
    char * arg; int addr;
    arg = strtok_r(NULL, "\n ", tokens);
    sscanf(arg, "%x", &addr);
	    
    for (int i = 0; i < 5; i++) {
	printf("%04x: ", addr + (i << 4));
	for (int j = 0; j < 16; j++) {
	    printf("%02x ", read_byte(cpu, addr + (i << 4) + j));
	}

	printf("\n");
    }

    return true;
}

bool command_dis(struct CPU * cpu, char ** tokens) {
    char * arg; int addr;
    arg = strtok_r(NULL, "\n ", tokens);
    sscanf(arg, "%x", &addr);
    
    char * inst = disasm(cpu, addr);
    printf("0x%04x: %s\n", addr, inst);
    return true;
}

struct DCommand commands[] = {
    {"h", "help", "Print help", command_help},
    {"q", "quit", "Quit the emulator", command_quit},
    {"c",  NULL, "Continue the emulation", command_continue},
    {"n", "next", "Execute one instruction", command_next},
    {"i", "info", "Print history", command_info},
    {"f", "flip", "Flip the screen", command_flip},
    
    {"b",  NULL, "Set a breakpoint", command_set_break},
    {"r", "rem", "Remove a breakpoint", command_rem_break},

    {"x", "read", "Examine bytes at a specified address", command_read},
    {"d", "dis", "Disassemble one instruction", command_dis},
    
    {NULL, NULL, NULL, NULL}
};
