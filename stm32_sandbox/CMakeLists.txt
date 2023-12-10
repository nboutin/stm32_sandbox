cmake_minimum_required(VERSION 3.23)

project(stm32_sandbox
  LANGUAGES CXX C ASM)

include(toolchain/stm32f4_disco.cmake)
include(cmake/compilation_flags.cmake)

# ---

add_subdirectory(stm32_sandbox)
