/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
int led_buffer[4] = {1, 2, 3, 4};
const int MAX_LED = 4;
int index_led = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {0x00, 0xFC, 0xFE, 0x33, 0x33, 0xFE, 0xFC, 0x00};

void controlLEDs(uint8_t num) {
    // Analyze each bit of the 8 LSBs and control the LEDs accordingly

    // Bit 0 (rightmost bit)
    if (num & 0x01) {   // Check if bit 0 is 1
        HAL_GPIO_WritePin(GPIOB, ROW0_Pin, GPIO_PIN_RESET); //ledROW0_on
    } else {
        HAL_GPIO_WritePin(GPIOB, ROW0_Pin, GPIO_PIN_SET); //ledROW0_off
    }
    // Bit 1
    if (num & 0x02) {   // Check if bit 1 is 1
        HAL_GPIO_WritePin(GPIOB, ROW1_Pin, GPIO_PIN_RESET); //ledROW1_on
    } else {
        HAL_GPIO_WritePin(GPIOB, ROW1_Pin, GPIO_PIN_SET); //ledROW1_off
    }

    // Bit 2
    if (num & 0x04) {   // Check if bit 2 is 1
        HAL_GPIO_WritePin(GPIOB, ROW2_Pin, GPIO_PIN_RESET); //ledROW2_on
    } else {
        HAL_GPIO_WritePin(GPIOB, ROW2_Pin, GPIO_PIN_SET); //ledROW2_off
    }

    // Bit 3
    if (num & 0x08) {   // Check if bit 3 is 1
        HAL_GPIO_WritePin(GPIOB, ROW3_Pin, GPIO_PIN_RESET); //ledROW3_on
    } else {
        HAL_GPIO_WritePin(GPIOB, ROW3_Pin, GPIO_PIN_SET); //ledROW3_off
    }
        // Bit 4
    if (num & 0x10) {
        HAL_GPIO_WritePin(GPIOB, ROW4_Pin, GPIO_PIN_RESET); //ledROW4_on
    } else {
        HAL_GPIO_WritePin(GPIOB, ROW4_Pin, GPIO_PIN_SET); //ledROW4_off
    }

    // Bit 5
    if (num & 0x20) {
        HAL_GPIO_WritePin(GPIOB, ROW5_Pin, GPIO_PIN_RESET); //ledROW5_on
    } else {
        HAL_GPIO_WritePin(GPIOB, ROW5_Pin, GPIO_PIN_SET); //ledROW5_off
    }

    // Bit 6
    if (num & 0x40) {
        HAL_GPIO_WritePin(GPIOB, ROW6_Pin, GPIO_PIN_RESET); //ledROW6_on
    } else {
        HAL_GPIO_WritePin(GPIOB, ROW6_Pin, GPIO_PIN_SET); //ledROW6_off
    }

    // Bit 7
    if (num & 0x80) {
        HAL_GPIO_WritePin(GPIOB, ROW7_Pin, GPIO_PIN_RESET); //ledROW7_on
    } else {
        HAL_GPIO_WritePin(GPIOB, ROW7_Pin, GPIO_PIN_SET); //ledROW7_off
    }
}

void offAllMatrixLED() {
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin|ENM6_Pin|ENM7_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, ROW0_Pin|ROW1_Pin|ROW2_Pin|ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin|ROW7_Pin, GPIO_PIN_SET);
}

void updateLEDMatrix(int index) {
  // Turn off all LEDs first
  offAllMatrixLED();

  // Set the appropriate row and column LEDs based on the index
  switch (index) {
    case 0:
      HAL_GPIO_WritePin(GPIOA, ENM0_Pin, GPIO_PIN_RESET);
      controlLEDs(matrix_buffer[0]);
      break;
    case 1:
      HAL_GPIO_WritePin(GPIOA, ENM1_Pin, GPIO_PIN_RESET);
      controlLEDs(matrix_buffer[1]);
      break;
    case 2:
      HAL_GPIO_WritePin(GPIOA, ENM2_Pin, GPIO_PIN_RESET);
      controlLEDs(matrix_buffer[2]);
      break;
    case 3:
      HAL_GPIO_WritePin(GPIOA, ENM3_Pin, GPIO_PIN_RESET);
      controlLEDs(matrix_buffer[3]);
      break;
    case 4:
      HAL_GPIO_WritePin(GPIOA, ENM4_Pin, GPIO_PIN_RESET);
      controlLEDs(matrix_buffer[4]);
      break;
    case 5:
      HAL_GPIO_WritePin(GPIOA, ENM5_Pin, GPIO_PIN_RESET);
      controlLEDs(matrix_buffer[5]);
      break;
    case 6:
      HAL_GPIO_WritePin(GPIOA, ENM6_Pin, GPIO_PIN_RESET);
      controlLEDs(matrix_buffer[6]);
      break;
    case 7:
      HAL_GPIO_WritePin(GPIOA, ENM7_Pin, GPIO_PIN_RESET);
      controlLEDs(matrix_buffer[7]);
      break;
    default:
      break;
  }
}





setTimer0(10);
while (1)
  {


    if(timer0_flag == 1){
    setTimer0(10); //set counter() and reset timer0_flag
      // second++;
      // if (second >= 60)
      // {
      //   second = 0;
      //   minute++;
      // }
      // if (minute >= 60)
      // {
      //   minute = 0;
      //   hour++;
      // }
      // if (hour >= 24)
      // {
      //   hour = 0;
      // }
      // updateClockBuffer();

      updateLEDMatrix(index_led_matrix);
      index_led_matrix = (index_led_matrix + 1) % MAX_LED_MATRIX;

      // // Blink two LEDs every second
      // HAL_GPIO_TogglePin(GPIOA, DOT_Pin);



    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin
                          |DOT_Pin|EN0_Pin|EN1_Pin|EN2_Pin
                          |EN3_Pin|ENM4_Pin|ENM5_Pin|ENM6_Pin
                          |ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_0_Pin|SEG_1_Pin|ROW2_Pin|ROW3_Pin
                          |ROW4_Pin|ROW5_Pin|ROW6_Pin|ROW7_Pin
                          |SEG_2_Pin|SEG_3_Pin|SEG_4_Pin|SEG_5_Pin
                          |SEG_6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin ENM2_Pin ENM3_Pin
                           DOT_Pin EN0_Pin EN1_Pin EN2_Pin
                           EN3_Pin ENM4_Pin ENM5_Pin ENM6_Pin
                           ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin
                          |DOT_Pin|EN0_Pin|EN1_Pin|EN2_Pin
                          |EN3_Pin|ENM4_Pin|ENM5_Pin|ENM6_Pin
                          |ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG_0_Pin SEG_1_Pin ROW2_Pin ROW3_Pin
                           ROW4_Pin ROW5_Pin ROW6_Pin ROW7_Pin
                           SEG_2_Pin SEG_3_Pin SEG_4_Pin SEG_5_Pin
                           SEG_6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG_0_Pin|SEG_1_Pin|ROW2_Pin|ROW3_Pin
                          |ROW4_Pin|ROW5_Pin|ROW6_Pin|ROW7_Pin
                          |SEG_2_Pin|SEG_3_Pin|SEG_4_Pin|SEG_5_Pin
                          |SEG_6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */





  // Timer callback function
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

      timer_run();
}


// if(counter <= 0){
// 			counter = 100;
// 			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
// }


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
