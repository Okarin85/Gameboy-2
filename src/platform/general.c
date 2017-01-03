/* general.c --- 
 * 
 * Filename: general.c
 * Author: Jules <archjules>
 * Created: Mon Jan  2 16:37:27 2017 (+0100)
 * Last-Updated: Tue Jan  3 00:59:19 2017 (+0100)
 *           By: Jules <archjules>
 */
#include <SDL/SDL.h>
#include "cpu/cpu.h"
#include "platform/input.h"
#include "platform/screen.h"
#include "logger.h"

void handle_new_frame(struct CPU * cpu) {
    static int last = 0;
    int now = SDL_GetTicks();
    
    treat_events(cpu);
    screen_flip(cpu->screen);

    if ((now - last) < 17) {
	SDL_Delay(17 - (now - last));
    }

    last = now;
}
