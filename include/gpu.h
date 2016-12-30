/* gpu.h --- 
 * 
 * Filename: gpu.h
 * Author: Jules <archjules>
 * Created: Tue Dec 13 00:46:44 2016 (+0100)
 * Last-Updated: Fri Dec 30 01:09:56 2016 (+0100)
 *           By: Jules <archjules>
 */

#ifndef GPU_H
#define GPU_H
#include <stdint.h>
#include "cpu.h"

// General GPU
int gpu_next(struct CPU *);

// Background
uint32_t background_get_color(struct CPU *, int, int);
#endif /* GPU_H */
