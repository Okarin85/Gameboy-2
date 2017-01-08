<!-- README.md --- 
;; 
;; Filename: README.md
;; Author: Jules <archjules>
;; Created: Thu Dec 29 19:37:03 2016 (+0100)
;; Last-Updated: Sun Jan  8 12:04:42 2017 (+0100)
;;           By: Jules <archjules>
 -->

# Introduction
Gameboy is (surprisingly) a Gameboy Emulator. It's currently a Work In Progress.

# Usage
## Compilation
To compile the program, go to the directory of the project, and run :

	cmake .
	make

## Using it after compilation
To use the program, run the executable with the ROM file as an argument

# TODO
## Things to do before Tetris is playable

 * Sprite implementation (kinda done)
 * DMA (done)
 * Timer implementation (done, but apparently not perfect)
 
## Things to do before Pokemon Red is playable

 * MBC implementation (begun, but only MBC0 and MBC1 are implemented, so no Pokemon Red)
 
## Things to do before the emulator is actually pleasant to play with

 * Savegame implementation (after the MBC implementation)
 * Config file (libherring is done, so I just have to add it to this project)
 
## Things to do after all of this

 * Sound support
 * Begin GBC support
 * Maybe do an actual UI?
