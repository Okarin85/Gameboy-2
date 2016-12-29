/* input.c --- 
 * 
 * Filename: input.c
 * Author: Jules <archjules>
 * Created: Thu Dec 15 14:44:01 2016 (+0100)
 * Last-Updated: Thu Dec 29 19:35:58 2016 (+0100)
 *           By: Jules <archjules>
 */
#include "input.h"
#define KEY_A 24
#define KEY_B 25
#define KEY_START 36
#define KEY_SELECT 65
#define KEY_UP 111
#define KEY_DOWN 116
#define KEY_RIGHT 114
#define KEY_LEFT 113

void treat_events(struct CPU * cpu) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
	switch(event.type) {
	case SDL_QUIT:
	    cpu->state = 1;
	    break;
	case SDL_KEYDOWN:
	    switch(event.key.keysym.scancode) {
	    case KEY_A: // A
		cpu->keys.buttons &= ~(0x01);
		break;
	    case KEY_B: // B
		cpu->keys.buttons &= ~(0x02);
		break;
	    case KEY_SELECT: // Select
		cpu->keys.buttons &= ~(0x04);
		break;
	    case KEY_START: // Start
		cpu->keys.buttons &= ~(0x08);
		break;
	    case KEY_RIGHT: // Right
		cpu->keys.direction &= ~(0x01);
		break;
	    case KEY_LEFT: // Left
		cpu->keys.direction &= ~(0x02);
		break;
	    case KEY_UP: // Up
		cpu->keys.direction &= ~(0x04);
		break;
	    case KEY_DOWN: // Down
		cpu->keys.direction &= ~(0x08);
		break;
	    }
	    break;
	case SDL_KEYUP:
	    switch(event.key.keysym.scancode) {
	    case KEY_A: // A
		cpu->keys.buttons |= 0x01;
		break;
	    case KEY_B: // B
		cpu->keys.buttons |= 0x02;
		break;
	    case KEY_SELECT: // Select
		cpu->keys.buttons |= 0x04;
		break;
	    case KEY_START: // Start
		cpu->keys.buttons |= 0x08;
		break;
	    case KEY_RIGHT: // Right
		cpu->keys.direction |= 0x01;
		break;
	    case KEY_LEFT: // Left
		cpu->keys.direction |= 0x02;
		break;
	    case KEY_UP: // Up
		cpu->keys.direction |= 0x04;
		break;
	    case KEY_DOWN: // Down
		cpu->keys.direction |= 0x08;
		break;
	    }
	    break;
	}
    }
}
