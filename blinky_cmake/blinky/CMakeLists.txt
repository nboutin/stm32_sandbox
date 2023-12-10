
set(target_name blinky_cmake)

add_executable(${target_name}
  application/source/main.cpp
  system/source/stm32f4xx_it.c
  system/source/stm32f4xx_hal_msp.c
  system/source/syscalls.c
  system/source/sysmem.c
  system/source/startup_stm32f411xe.s
  system/Source/system_stm32f4xx.c
  # ---
  lib/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
  lib/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
  lib/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
  lib/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
  lib/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
)

target_include_directories(${target_name} PRIVATE
  system/include
  lib/Drivers/BSP/STM32F411E-Discovery
  lib/Drivers/CMSIS/Core/Include
  lib/Drivers/CMSIS/Device/ST/STM32F4xx/Include
  lib/Drivers/STM32F4xx_HAL_Driver/Inc
  lib/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
)

target_compile_definitions(${target_name} PRIVATE USE_HAL_DRIVER STM32F411xE)

target_compile_features(${target_name} PRIVATE c_std_11 cxx_std_14)

# Optimization flags: place function and data in their own sections
string(APPEND CMAKE_C_FLAGS " -ffunction-sections -fdata-sections -flto")
string(APPEND CMAKE_CXX_FLAGS " -ffunction-sections -fdata-sections -flto")

string(APPEND CMAKE_CXX_FLAGS " -fno-exceptions -fno-rtti")

# Set linker script
string(APPEND CMAKE_EXE_LINKER_FLAGS " -T ${CMAKE_CURRENT_SOURCE_DIR}/linker/STM32F411VEHX_FLASH.ld -static -flto")

# Discard unused sections
string(APPEND CMAKE_EXE_LINKER_FLAGS " -Wl,--gc-sections")

# Use C math library
string(APPEND CMAKE_EXE_LINKER_FLAGS " -Wl,--start-group -lc -lm -Wl,--end-group")

include(../cmake/binary_size.cmake)
include(../cmake/map_file.cmake)

# --- install

include(GNUInstallDirs)
install(TARGETS ${target_name} EXPORT ${target_name})
