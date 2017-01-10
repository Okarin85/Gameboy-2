/* general.c --- 
 * 
 * Filename: general.c
 * Author: Jules <archjules>
 * Created: Mon Jan  2 16:37:27 2017 (+0100)
 * Last-Updated: Mon Jan  9 20:36:23 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <SDL/SDL.h>
#include "cpu/cpu.h"
#include "platform/input.h"
#include "platform/screen.h"
#include "logger.h"

uint8_t io_handle_read(struct CPU *, uint8_t);

void handle_new_frame(struct CPU * cpu) {
    static int last = 0;
    int now = SDL_GetTicks();
    
    treat_events(cpu);
    if (!cpu->gpu.lcd_off)
	screen_flip(cpu->screen);
    
    if ((now - last) < 17) {
	SDL_Delay(17 - (now - last));
    }

    last = now;
}
