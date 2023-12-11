
#pragma once

#include "stm32f4xx_hal_cpp.h"

namespace peripherals {
// HAL_GPIO_WritePin(GPIOD, LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN, GPIO_PIN_RESET);

// GPIO_InitTypeDef BoardLEDs;
// BoardLEDs.Mode  = GPIO_MODE_OUTPUT_PP;
// BoardLEDs.Pin   = LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN;
// BoardLEDs.Pull  = GPIO_NOPULL;
// BoardLEDs.Speed = GPIO_SPEED_FREQ_LOW;
// HAL_GPIO_Init(GPIOD, &BoardLEDs);

stm32f4xx::GPIOD& gpiod{*new stm32f4xx::GPIOD()};
} // namespace peripherals
