# MCU library

## Memory-Mapped Devices as objects

- https://www.youtube.com/watch?v=uwzuAGtAEFk&list=PLUn4CkTIEBW3QEFbTi4gWwOCPXgtlb6o4&index=2&t=96s
- https://www.youtube.com/watch?v=EM83l5NZ15c&list=PLUn4CkTIEBW3QEFbTi4gWwOCPXgtlb6o4&index=3

### GPIO

  __HAL_RCC_GPIOD_CLK_ENABLE();
  HAL_GPIO_WritePin(GPIOD, LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN, GPIO_PIN_RESET);

  GPIO_InitTypeDef BoardLEDs;
  BoardLEDs.Mode  = GPIO_MODE_OUTPUT_PP;
  BoardLEDs.Pin   = LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN;
  BoardLEDs.Pull  = GPIO_NOPULL;
  BoardLEDs.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &BoardLEDs);
