cmake_minimum_required(VERSION 2.6)

# Configuration
project("Gameboy" C)
include_directories(include)

# Executable
add_executable(gameboy
  src/main.c
  src/cpu/cpu.c
  src/cpu/cb.c
  src/cpu/instruction.c
  src/cpu/interrupt.c
  src/memory/memory.c
  src/memory/io.c
  src/gpu/gpu.c
  src/platform/screen.c
  src/platform/input.c)

add_definitions(-DLOGLEVEL=0)
target_link_libraries(gameboy SDL)
