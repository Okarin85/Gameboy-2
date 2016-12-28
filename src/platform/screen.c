/* screen.c --- 
 * 
 * Filename: screen.c
 * Author: Jules <archjules>
 * Created: Sat Dec 10 18:19:15 2016 (+0100)
 * Last-Updated: Wed Dec 28 12:24:19 2016 (+0100)
 *           By: Jules <archjules>
 */
#include <SDL/SDL.h>
#include "screen.h"

/*
 * new_screen:
 * Initialises the screen
 */
Screen * new_screen() {
    Screen * window;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_SetVideoMode(SCREEN_WIDTH * PIXEL_SIZE, SCREEN_HEIGHT * PIXEL_SIZE, 24, 0);
    return window;
}

/*
 * screen_destroy:
 * Frees the allocated ressources
 */
void screen_destroy(SDL_Surface * window) {
    SDL_FreeSurface(window);
    SDL_Quit();
}

/*
 * screen_flip:
 * Flip the screen
 */
void screen_flip(Screen * screen) {
    SDL_Flip(screen);
}

/*
 * screen_put_pixel
 * Put a pixel on the framebuffer
 *
 * @x: The x coordinate
 * @y: The y coordinate
 * @color: The color of the pixel
 */
void screen_put_pixel(Screen * screen, int x, int y, uint32_t color) {
    SDL_Rect rect = {.w = PIXEL_SIZE, .h = PIXEL_SIZE, .x = x * PIXEL_SIZE, .y = y * PIXEL_SIZE};
    SDL_FillRect(screen, &rect, color);
}
