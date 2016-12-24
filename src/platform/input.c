/* input.c --- 
 * 
 * Filename: input.c
 * Author: Jules <archjules>
 * Created: Thu Dec 15 14:44:01 2016 (+0100)
 * Last-Updated: Thu Dec 15 14:52:47 2016 (+0100)
 *           By: Jules <archjules>
 */
#include "input.h"

void treat_events(struct CPU * cpu) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
	switch(event.type) {
	case SDL_QUIT:
	    cpu->state = 1;
	    break;
	}
    }
}
