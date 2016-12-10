cmake_minimum_required(VERSION 2.6)

# Configuration
project("Gameboy" C)
include_directories(include)

# Executable
add_executable(gameboy src/main.c src/cpu.c src/memory.c src/instruction.c src/cb.c)
add_definitions(-DLOGLEVEL=0)
target_link_libraries(gameboy SDL)
