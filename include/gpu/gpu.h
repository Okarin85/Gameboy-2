/* gpu.h --- 
 * 
 * Filename: gpu.h
 * Author: Jules <archjules>
 * Created: Tue Dec 13 00:46:44 2016 (+0100)
 * Last-Updated: Tue Jun 20 22:00:50 2017 (+0200)
 *           By: Jules <archjules>
 */

#ifndef GPU_H
#define GPU_H
#include <stdint.h>
#include "cpu/cpu.h"

#define SCREEN_WHITE 0x00E0F8D0
#define SCREEN_LGRAY 0x0088C070
#define SCREEN_DGRAY 0x00346856
#define SCREEN_BLACK 0x00081820

// General GPU
void gpu_next(struct CPU *);

// Tiles
int tile_get_pixel(struct CPU *, int, int, int, int, int);

// Palettes
uint32_t palette_get_color(char *, int, int);

// Window
int window_get_color(struct CPU *, int, int);

// Background
int background_get_color(struct CPU *, int, int);
#endif /* GPU_H */
