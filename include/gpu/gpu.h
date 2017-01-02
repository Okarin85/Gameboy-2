/* gpu.h --- 
 * 
 * Filename: gpu.h
 * Author: Jules <archjules>
 * Created: Tue Dec 13 00:46:44 2016 (+0100)
 * Last-Updated: Mon Jan  2 08:13:18 2017 (+0100)
 *           By: Jules <archjules>
 */

#ifndef GPU_H
#define GPU_H
#include <stdint.h>
#include "cpu/cpu.h"

// General GPU
int gpu_next(struct CPU *);

// Background
int background_get_color(struct CPU *, int, int);
#endif /* GPU_H */
