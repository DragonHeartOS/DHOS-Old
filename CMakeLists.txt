cmake_minimum_required (VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(CMAKE_C_COMPILER "Toolchain/build/bin/x86_64-elf-gcc")
set(CMAKE_CXX_COMPILER "Toolchain/build/bin/x86_64-elf-g++")
set(CMAKE_LINKER "Toolchain/build/bin/x86_64-elf-ld")

project (dhos VERSION 0.1 LANGUAGES C CXX ASM_NASM)

set (WARNING_FLAGS -Wall -Wextra -Wconversion -Wsign-conversion)
set (COMMON_COMPILER_FLAGS ${WARNING_FLAGS})
set (C_COMPILER_FLAGS ${COMMON_COMPILER_FLAGS})
set (CXX_COMPILER_FLAGS ${COMMON_COMPILER_FLAGS} -fno-exceptions -fno-rtti)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_C_STANDARD 11)

set(KERNEL_TARGET katline)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory (Katline)

add_custom_target(image)
add_custom_command(
  TARGET   image
  COMMAND  "../Util/BuildDiskImage.sh"
  USES_TERMINAL
)

add_custom_target(cdrom)
add_custom_command(
  TARGET   cdrom
  COMMAND  "../Util/BuildCDROMImage.sh"
)

add_custom_target(run)
add_custom_command(
  TARGET   run
  COMMAND  "../Util/Run.sh"
  USES_TERMINAL
)
