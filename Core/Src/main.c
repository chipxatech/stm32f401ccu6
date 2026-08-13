/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body - LED Blink Test
  * @description    : Blinks onboard LED on PC13 (WeAct Black Pill STM32F401CCU6)
  *                   LED is ACTIVE LOW: GPIO_PIN_RESET = ON, GPIO_PIN_SET = OFF
  *                   Blink period: 1 second (500ms ON, 500ms OFF)
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* Private user code ---------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock to 84 MHz using HSE 25MHz + PLL */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  /* Infinite loop */
  while (1)
  {
    /*
     * LED is Active LOW on WeAct Black Pill:
     * GPIO_PIN_RESET (0) = LED ON  (cathode pulled low, current flows)
     * GPIO_PIN_SET   (1) = LED OFF (cathode high, no current)
     */

    /* LED ON */
    HAL_GPIO_WritePin(LED_ONBOARD_GPIO_Port, LED_ONBOARD_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);

    /* LED OFF */
    HAL_GPIO_WritePin(LED_ONBOARD_GPIO_Port, LED_ONBOARD_Pin, GPIO_PIN_SET);
    HAL_Delay(500);
  }
}

/**
  * @brief System Clock Configuration
  * @detail Configures the system clock as follows:
  *         - HSE = 25 MHz (external crystal on WeAct Black Pill)
  *         - PLL Source = HSE
  *         - PLLM = 25 (VCO input = 1 MHz)
  *         - PLLN = 336 (VCO output = 336 MHz)
  *         - PLLP = 4 (SYSCLK = 84 MHz)
  *         - PLLQ = 7 (USB = 48 MHz)
  *         - AHB Prescaler = 1 (HCLK = 84 MHz)
  *         - APB1 Prescaler = 2 (PCLK1 = 42 MHz)
  *         - APB2 Prescaler = 1 (PCLK2 = 84 MHz)
  *         - Flash Latency = 2 WS (for 84 MHz @ 3.3V)
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  * HSE = 25MHz external crystal on WeAct Black Pill board
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  /* Flash latency = 2 wait states for 84 MHz at 2.7V-3.6V */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @detail Configures PC13 as output push-pull for onboard LED
  *         - Mode: Output Push-Pull
  *         - Pull: No pull-up, no pull-down
  *         - Speed: Low (sufficient for LED toggling)
  *         - Initial state: GPIO_PIN_SET (LED OFF, since active LOW)
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();  /* For HSE pins PH0/PH1 */
  __HAL_RCC_GPIOA_CLK_ENABLE();  /* For SWD pins PA13/PA14 */

  /* Configure GPIO pin Output Level - Start with LED OFF (active LOW, so SET = OFF) */
  HAL_GPIO_WritePin(LED_ONBOARD_GPIO_Port, LED_ONBOARD_Pin, GPIO_PIN_SET);

  /* Configure GPIO pin : LED_ONBOARD_Pin (PC13)
   * Output Push-Pull, No pull, Low speed
   */
  GPIO_InitStruct.Pin = LED_ONBOARD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_ONBOARD_GPIO_Port, &GPIO_InitStruct);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
    /* Stay here on error */
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
