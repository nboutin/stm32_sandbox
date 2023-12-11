
#pragma once

#include "mmo_gpio.h"
#include "stm32f411xe.h"

#undef GPIOD

namespace stm32f4xx {

struct gpiod_traits {
  static constexpr std::uintptr_t base_address{GPIOD_BASE};
  // __HAL_RCC_GPIOD_CLK_ENABLE(); // Todo: add gpio clock enable
};

using GPIOD = mcu::GPIO_t<gpiod_traits>;

/* Ensure that its respect memory-mapped device addresses offset */
static_assert(std::is_standard_layout<GPIOD>::value, "GPIO is not a standard-layout class");
static_assert(sizeof(GPIOD) == 10 * sizeof(mcu::device_register), "GPIO contains unexpected padding");

} // namespace stm32f4xx
