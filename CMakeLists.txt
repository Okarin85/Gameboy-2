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
  src/memory/memory.c
  src/memory/io.c
  src/gpu/gpu.c
  src/gpu/background.c
  src/gpu/oam.c
  src/platform/screen.c
  src/platform/input.c
  src/platform/general.c
)

add_definitions(-DLOGLEVEL=0)
target_link_libraries(gameboy SDL)
