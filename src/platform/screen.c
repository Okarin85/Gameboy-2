/* screen.c --- 
 * 
 * Filename: screen.c
 * Author: Jules <archjules>
 * Created: Sat Dec 10 18:19:15 2016 (+0100)
 * Last-Updated: Sat Jun 17 23:16:24 2017 (+0200)
 *           By: Jules <archjules>
 */
#include <SDL2/SDL.h>
#include "gpu/gpu.h"
#include "platform/screen.h"

/*
 * new_screen:
 * Initialises the screen
 */
Screen new_screen() {
    Screen screen;
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_CreateWindowAndRenderer(
	SCREEN_WIDTH * PIXEL_SIZE,
	SCREEN_HEIGHT * PIXEL_SIZE,
	0,
	&screen.window,
	&screen.renderer);
    
    return screen;
}

/*
 * screen_destroy:
 * Frees the allocated ressources
 */
void screen_destroy(Screen screen) {
    SDL_DestroyRenderer(screen.renderer);
    SDL_DestroyWindow(screen.window);
    SDL_Quit();
}
	
/*
 * screen_flip:
 * Flip the screen
 */
void screen_flip(Screen screen) {
    SDL_RenderPresent(screen.renderer);
    SDL_UpdateWindowSurface(screen.window);
}

/*
 * screen_put_pixel
 * Put a pixel on the framebuffer
 *
 * @x: The x coordinate
 * @y: The y coordinate
 * @color: The color of the pixel
 */
void screen_put_pixel(Screen screen, int x, int y, uint32_t color) {
    SDL_Rect rect = {.w = PIXEL_SIZE,
		     .h = PIXEL_SIZE,
		     .x = x * PIXEL_SIZE,
		     .y = y * PIXEL_SIZE};

    SDL_SetRenderDrawColor(screen.renderer,
			   (color & 0x00FF0000) >> 16,
			   (color & 0x0000FF00) >> 8,
			   (color & 0x000000FF),
			   255);
    SDL_RenderFillRect(screen.renderer, &rect);
}
