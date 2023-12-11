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

#include <bitset>
#include <cstdint>
#include <type_traits>

namespace mcu {
using device_register = std::uint32_t volatile;

/**
 * \details To maintain a standard-layout class, it is forbidden to add:
 * - virtual functions
 * - All non-static data members are of the same access control
 */
template <typename gpio_traits> class GPIO_t {
public:
  // clang-format off
  enum pin{pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7, pin8, pin9, pin10, pin11, pin12, pin13, pin14, pin15,
    pin16, pin17, pin18, pin19, pin20, pin21, pin22, pin23, pin24, pin25, pin26, pin27, pin28, pin29, pin30, pin31, pin32, pin33, pin34, pin35};
  // clang-format on

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

  GPIO_t(){};

  static void* operator new(std::size_t);
  static void operator delete(void*) {}

  void set();
  void reset();

private:
  void set_io_direction_mode(gpio_mode gpio_mode_, pin pin_);

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

template <typename gpio_traits> static void* GPIO_t<gpio_traits>::operator new(std::size_t)
{
  return reinterpret_cast<void*>(gpio_traits::base_address);
}

template <typename gpio_traits> void GPIO_t<gpio_traits>::set() {}

template <typename gpio_traits> void GPIO_t<gpio_traits>::reset() {}

/**
 * Configure IO Direction mode (Input, Output, Alternate or Analog)
 */
template <typename gpio_traits> void GPIO_t<gpio_traits>::set_io_direction_mode(gpio_mode gpio_mode_, pin pin_)
{
  auto position = (1U << pin_) * 2;
  std::bitset<32> temp{MODER};
  temp &= ~(0x3 << position);     // Clear the bits
  temp.set(position, gpio_mode_); // Set the bits
  MODER = temp.to_ulong();        // Write the new mode back to the GPIO pins
  // temp &= ~(GPIO_MODER_MODER0 << (position * 2U));
  // temp |= ((GPIO_Init->Mode & GPIO_MODE) << (position * 2U));
}

} // namespace mcu