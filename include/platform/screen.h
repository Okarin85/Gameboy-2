/* screen.h --- 
 * 
 * Filename: screen.h
 * Author: Jules <archjules>
 * Created: Sat Dec 10 18:20:43 2016 (+0100)
 * Last-Updated: Sat Jun 17 21:48:56 2017 (+0200)
 *           By: Jules <archjules>
 */

#ifndef SCREEN_H
#define SCREEN_H
#include <stdint.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define PIXEL_SIZE 2

typedef struct {
    SDL_Window * window;
    SDL_Renderer * renderer;
} Screen;

void screen_destroy(Screen);
void screen_turnoff(Screen);
void screen_flip(Screen);
void screen_put_pixel(Screen, int, int, uint32_t);
Screen new_screen();
#endif /* SCREEN_H */
