# STM32F411E-DISCO board - C++ Blinky with CMake

## Credit

https://github.com/vpetrigo/arm-cmake-toolchains

## Setup

1. Download https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain > AArch32 bare-metal target (arm-none-eabi)
2. Download https://github.com/ninja-build/ninja/releases

## Build

### All in once

    ./gen_build_install.sh

### Step by step

Generate with ARM GNU:

    source env_arm_gnu.sh
    cmake -S . -B build/MinSizeRel -G Ninja --toolchain toolchain/arm_gcc_toolchain.cmake -DCMAKE_BUILD_TYPE=MinSizeRel

Build:

    cmake --build build/MinSizeRel

Install:

    cmake --install build/MinSizeRel --prefix .

## External files

Arm\Packs\Keil\STM32F4xx_DFP\2.17.1\Drivers\CMSIS\Device\ST\STM32F4xx\Source\Templates\gcc\startup_stm32f411xe.s
Arm\Packs\Keil\STM32F4xx_DFP\2.17.1\Drivers\CMSIS\Device\ST\STM32F4xx\Source\Templates\system_stm32f4xx.c
