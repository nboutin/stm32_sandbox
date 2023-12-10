/**
 * \file gpio.h
 * \brief GPIO Memory-Mapped Devices as objects
 * \author Nicolas Boutin
 * \date 2023-12
 */

// __HAL_RCC_GPIOD_CLK_ENABLE();
// HAL_GPIO_WritePin(GPIOD, LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN, GPIO_PIN_RESET);

// GPIO_InitTypeDef BoardLEDs;
// BoardLEDs.Mode  = GPIO_MODE_OUTPUT_PP;
// BoardLEDs.Pin   = LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN;
// BoardLEDs.Pull  = GPIO_NOPULL;
// BoardLEDs.Speed = GPIO_SPEED_FREQ_LOW;
// HAL_GPIO_Init(GPIOD, &BoardLEDs);

#pragma once

#include <cstdint>
#include <type_traits>

#include "stm32f411xe.h"

namespace mcu {
using device_register = std::uint32_t volatile;

/**
 * \details To maintain a standard-layout class, it is forbidden to add:
 * - virtual functions
 * - All non-static data members are of the same access control
 */
class GPIO {
public:
  enum gpio_mode : std::uint32_t {
    gpio_input  = 0UL << 0U,
    gpio_output = 1UL << 0U,
  }; // , alternate, analog

  enum output_mode : std::uint32_t {
    push_pull  = 0UL << 4U,
    open_drain = 1UL << 4U,
  };

  enum mode : std::uint32_t {
    input,
    output_pp = gpio_output | push_pull,
    output_od = gpio_output | open_drain,
  };

  GPIO()
  {
    // (void) m;
    // set_mode(m);
  }
  enum gpio_id { A, B, C, D, E, Not_F, Not_G, H };
  void* operator new(std::size_t sz, gpio_id id)
  {
    (void) sz;
    return reinterpret_cast<void*>(AHB1PERIPH_BASE + id * +0x0400UL);
  }

private:
  // Configuration
  device_register MODER;   /*!< GPIO port mode register,               Address offset: 0x00      */
  device_register OTYPER;  /*!< GPIO port output type register,        Address offset: 0x04      */
  device_register OSPEEDR; /*!< GPIO port output speed register,       Address offset: 0x08      */
  device_register PUPDR;   /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  // Data
  device_register IDR; /*!< GPIO port input data register,         Address offset: 0x10      */
  device_register ODR; /*!< GPIO port output data register,        Address offset: 0x14      */
  // Set/reset
  device_register BSRR; /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
  // Locking
  device_register LCKR; /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  // Alternate function
  device_register AFR[2]; /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
};

/* Ensure that with respect memory-mapped device addresses offset */
static_assert(std::is_standard_layout<GPIO>::value, "GPIO is not a standard-layout class");

static_assert(sizeof(GPIO) == 10 * sizeof(device_register), "GPIO contains unexpected padding");

// error: 'mcu::device_register mcu::GPIO::MODER' is private within this context
// static_assert(offsetof(GPIO, MODER) == 0x00, "GPIO MODER register is not at offset 0x00");
}; // namespace mcu
