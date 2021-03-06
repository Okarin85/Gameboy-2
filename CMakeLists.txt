cmake_minimum_required(VERSION 2.6)

# Configuration
project("Gameboy" C)
include_directories(include)

# Executable
add_executable(gameboy
  src/main.c
  src/cpu/cpu.c
  src/cpu/cb.c
  src/cpu/dma.c
  src/cpu/instruction.c
  src/cpu/interrupt.c
  src/cpu/timer.c
  src/rom/load.c
  src/rom/mbc0.c
  src/rom/mbc1.c
  src/rom/mbc3.c
  src/memory/memory.c
  src/memory/io.c
  src/gpu/gpu.c
  src/gpu/tile.c
  src/gpu/palette.c
  src/gpu/background.c
  src/gpu/oam.c
  src/util/vector.c
  src/debug/debug.c
  src/debug/commands.c
  src/debug/disasm.c
  src/debug/arguments.c
  src/platform/screen.c
  src/platform/input.c
  src/platform/general.c
)

add_definitions(-DLOGLEVEL=0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall -Wextra -Wno-unused-parameter")
target_link_libraries(gameboy SDL2 readline)
