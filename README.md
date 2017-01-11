<!-- README.md --- 
;; 
;; Filename: README.md
;; Author: Jules <archjules>
;; Created: Thu Dec 29 19:37:03 2016 (+0100)
;; Last-Updated: Thu Jan 12 00:24:42 2017 (+0100)
;;           By: Jules <archjules>
 -->

# Introduction
Gameboy is (surprisingly) a Gameboy Emulator. It can be used to play a few games, including Pokemon Red.

# Usage
## Compilation
To compile the program, go to the directory of the project, and run :

	cmake .
	make

## Using it after compilation
To use the program, run the executable with the ROM file as an argument. The keys to play are (on a BÉPO keyboard) :

 * B for the A button
 * É for the B button
 * Return for the Start button
 * Space for the Select button
 * Directional keys for … the directional keys
 * You can push F1 to toggle Fast mode
 
On a QWERTY keyboard, the keys are the same, but should be Q for the A button, and W for the B button.

# TODO
## Games I test this emulator on
 
 * Tetris (playable)
 * Link's Awakening (seems to be playable until you go left of the first map, then south, and then it's really strange)
 * Pokémon Red (playable)
 
## Things to do, after all of this (probably not)

 * Begin GBC support
 * Sound support
