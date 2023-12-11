
#pragma once

#include "stm32f411e_disco.h"
#include "stm32f4xx_hal_cpp.h"

// HAL_GPIO_WritePin(GPIOD, LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN, GPIO_PIN_RESET);

// GPIO_InitTypeDef BoardLEDs;
// BoardLEDs.Mode  = GPIO_MODE_OUTPUT_PP;
// BoardLEDs.Pin   = LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN;
// BoardLEDs.Pull  = GPIO_NOPULL;
// BoardLEDs.Speed = GPIO_SPEED_FREQ_LOW;
// HAL_GPIO_Init(GPIOD, &BoardLEDs);

stm32f4xx::GPIOD& gpiod{
    *new stm32f4xx::GPIOD{stm32f411e_disco::LED4, stm32f4xx::GPIOD::gpio_output}
};
// stm32f4xx::GPIOD& gpiod{*new stm32f4xx::GPIOD{stm32f4xx::GPIOD::pin12}};
