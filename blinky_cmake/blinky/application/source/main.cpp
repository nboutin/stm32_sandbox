
#include "stm32f411e_discovery.h"
#include "stm32f4xx_hal.h"

static void PeriphCommonClock_Config(void);
static void SystemClock_Config(void);

static void Init_OnBoard_LEDs(void);
static void Delay_ms(volatile int time_ms);
static void Error_Handler(void);

int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  Init_OnBoard_LEDs();

  while (1)
  {
    while (1)
    {
      HAL_GPIO_WritePin(GPIOD, LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN, GPIO_PIN_SET);
      Delay_ms(2000);
      HAL_GPIO_WritePin(GPIOD, LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN, GPIO_PIN_RESET);
      Delay_ms(2000);
    }
  }
}

void Init_OnBoard_LEDs(void)
{
  __HAL_RCC_GPIOD_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOD, LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN, GPIO_PIN_RESET);

  GPIO_InitTypeDef BoardLEDs;
  BoardLEDs.Mode  = GPIO_MODE_OUTPUT_PP;
  BoardLEDs.Pin   = LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN;
  BoardLEDs.Pull  = GPIO_NOPULL;
  BoardLEDs.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &BoardLEDs);
}

void Delay_ms(volatile int time_ms)
{
  int j;
  for (j = 0; j < time_ms * 4000; j++)
  {
  } /* exceute NOP for 1ms */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
static void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM       = 8;
  RCC_OscInitStruct.PLL.PLLN       = 336;
  RCC_OscInitStruct.PLL.PLLP       = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ       = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief Peripherals Common Clock Configuration
 * @retval None
 */
static void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
   */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN       = 192;
  PeriphClkInitStruct.PLLI2S.PLLI2SR       = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

static void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
