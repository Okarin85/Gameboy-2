/* debug.h --- 
 * 
 * Filename: debug.h
 * Author: Jules <archjules>
 * Created: Wed Jun  7 06:03:48 2017 (+0200)
 * Last-Updated: Fri Jun  9 02:00:14 2017 (+0200)
 *           By: Jules <archjules>
 */
#ifndef DEBUG_H
#define DEBUG_H
#include <stdbool.h>
#include "cpu/cpu.h"
#include "cpu/instruction.h"

void handle_debug(struct CPU *);
void handle_debug_run(struct CPU *);
#endif /* DEBUG_H */
