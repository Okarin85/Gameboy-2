/* input.c --- 
 * 
 * Filename: input.c
 * Author: Jules <archjules>
 * Created: Thu Dec 15 14:44:01 2016 (+0100)
 * Last-Updated: Sun Jun 18 03:13:03 2017 (+0200)
 *           By: Jules <archjules>
 */
#include "debug/debug.h"
#include "platform/input.h"
#include "logger.h"
#define KEY_A 20
#define KEY_B 26
#define KEY_START 40
#define KEY_SELECT 44
#define KEY_UP 82
#define KEY_DOWN 81
#define KEY_RIGHT 79
#define KEY_LEFT 80
#define KEY_F1 58
#define KEY_F11 68

extern uint8_t oam[0xA0];

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
		// Debug keys
	    case KEY_F1: // Fast mode
		cpu->fast_mode = true;
		break;
	    case KEY_F11: // Debugger
	        cpu->debug.next = 1;
		break;
	    default:
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
	    case KEY_F1:
		cpu->fast_mode = false;
		break;
	    default:
		break;
	    }
	    break;
	}
    }
}
