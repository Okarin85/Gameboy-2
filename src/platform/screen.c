/* screen.c --- 
 * 
 * Filename: screen.c
 * Author: Jules <archjules>
 * Created: Sat Dec 10 18:19:15 2016 (+0100)
 * Last-Updated: Thu Dec 22 18:46:19 2016 (+0100)
 *           By: Jules <archjules>
 */
#include <SDL/SDL.h>
#include "screen.h"

Screen * new_screen() {
    Screen * window;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_SetVideoMode(SCREEN_WIDTH * PIXEL_SIZE, SCREEN_HEIGHT * PIXEL_SIZE, 24, 0);
    return window;
}

void screen_destroy(SDL_Surface * window) {
    SDL_FreeSurface(window);
    SDL_Quit();
}

void screen_flip(Screen * screen) {
    SDL_Flip(screen);
}

void screen_put_pixel(Screen * screen, int x, int y, uint32_t color) {
    SDL_Rect rect = {.w = PIXEL_SIZE, .h = PIXEL_SIZE, .x = x * PIXEL_SIZE, .y = y * PIXEL_SIZE};
    SDL_FillRect(screen, &rect, color);
}
