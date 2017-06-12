/* debug.h --- 
 * 
 * Filename: debug.h
 * Author: Jules <archjules>
 * Created: Wed Jun  7 06:03:48 2017 (+0200)
 * Last-Updated: Sat Jun 10 01:29:10 2017 (+0200)
 *           By: Jules <archjules>
 */
#ifndef DEBUG_H
#define DEBUG_H
#include <stdbool.h>
#include "cpu/cpu.h"
#include "cpu/instruction.h"

struct DCommand {
    char * short_c;
    char * long_c;
    char * description;
    bool (*function)(struct CPU *, char **);
};

void handle_debug(struct CPU *);
void handle_debug_run(struct CPU *);
char * disasm(struct CPU *, uint16_t);

extern struct DCommand commands[];
#endif /* DEBUG_H */
