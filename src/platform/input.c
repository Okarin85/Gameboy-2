/* input.c --- 
 * 
 * Filename: input.c
 * Author: Jules <archjules>
 * Created: Thu Dec 15 14:44:01 2016 (+0100)
 * Last-Updated: Thu Dec 29 19:22:36 2016 (+0100)
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
	case SDL_KEYDOWN:
	    switch(event.key.keysym.scancode) {
	    case 24: // A
		cpu->keys.buttons &= ~(0x01);
		break;
	    case 25: // B
		cpu->keys.buttons &= ~(0x02);
		break;
	    case 65: // Select
		cpu->keys.buttons &= ~(0x04);
		break;
	    case 36: // Start
		cpu->keys.buttons &= ~(0x08);
		break;
	    case 114: // Right
		cpu->keys.direction &= ~(0x01);
		break;
	    case 113: // Left
		cpu->keys.direction &= ~(0x02);
		break;
	    case 111: // Up
		cpu->keys.direction &= ~(0x04);
		break;
	    case 116: // Down
		cpu->keys.direction &= ~(0x08);
		break;
	    }
	    break;
	case SDL_KEYUP:
	    switch(event.key.keysym.scancode) {
	    case 24: // A
		cpu->keys.buttons |= 0x01;
		break;
	    case 25: // B
		cpu->keys.buttons |= 0x02;
		break;
	    case 65: // Select
		cpu->keys.buttons |= 0x04;
		break;
	    case 36: // Start
		cpu->keys.buttons |= 0x08;
		break;
	    case 114: // Right
		cpu->keys.direction |= 0x01;
		break;
	    case 113: // Left
		cpu->keys.direction |= 0x02;
		break;
	    case 111: // Up
		cpu->keys.direction |= 0x04;
		break;
	    case 116: // Down
		cpu->keys.direction |= 0x08;
		break;
	    }
	    break;
	}
    }
}
