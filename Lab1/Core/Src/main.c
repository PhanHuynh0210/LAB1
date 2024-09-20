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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG1(int num);
void display7SEG2(int num);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int counter = 0;
int state = 0;
int RED = 5;
int GREEN = 3;
int YELLOW = 2;
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

      /* USER CODE END WHILE */
  	  while (1)
  	   {
  	       switch (state)
  	       {
  	           case 0:
  	        	   display7SEG2(RED--);
  	               // Set 1: Red on, Yellow and Green off
  	               HAL_GPIO_WritePin(GPIOA, RED_1_Pin, GPIO_PIN_RESET);
  	               HAL_GPIO_WritePin(GPIOA, YELLOW_1_Pin, GPIO_PIN_SET);
  	               HAL_GPIO_WritePin(GPIOA, GREEN_1_Pin, GPIO_PIN_SET);

  	               // Set 2: Green on, Red and Yellow off
  	               HAL_GPIO_WritePin(GPIOA, RED_2_Pin, GPIO_PIN_SET);
  	               HAL_GPIO_WritePin(GPIOA, YELLOW_2_Pin, GPIO_PIN_SET);
  	               HAL_GPIO_WritePin(GPIOA, GREEN_2_Pin, GPIO_PIN_RESET);
  	               display7SEG1(GREEN--);

  	               if (counter >= 3)
  	               {
  	                   state = 1;
  	                   counter = 0;
  	                   GREEN = 3;
  	               }


  	               break;

  	           case 1:
  	               // Set 2: Yellow on, Red and Green off
  	        	   display7SEG2(RED--);
  	               HAL_GPIO_WritePin(GPIOA, YELLOW_2_Pin, GPIO_PIN_RESET);
  	               HAL_GPIO_WritePin(GPIOA, GREEN_2_Pin, GPIO_PIN_SET);
  	               display7SEG1(YELLOW--);
  	               if (counter >= 2)
  	               {
  	                   state = 2;
  	                   counter = 0;
  	                   YELLOW = 2;
  	                   RED = 5;
  	               }
  	               break;

  	           case 2:
  	               // Set 1: Green on, Red and Yellow off
  	        	   display7SEG1(RED--);
  	               HAL_GPIO_WritePin(GPIOA, RED_1_Pin, GPIO_PIN_SET);
  	               HAL_GPIO_WritePin(GPIOA, GREEN_1_Pin, GPIO_PIN_RESET);

  	               // Set 2: Red on, Yellow and Green off
  	               HAL_GPIO_WritePin(GPIOA, RED_2_Pin, GPIO_PIN_RESET);
  	               HAL_GPIO_WritePin(GPIOA, YELLOW_2_Pin, GPIO_PIN_SET);
  	               display7SEG2(GREEN--);
  	               if (counter >= 3)
  	               {
  	                   state = 3;
  	                   counter = 0;
  	                   GREEN = 3;

  	               }
  	               break;

  	           case 3:
  	               // Set 1: Yellow on, Red and Green off
  	        	   display7SEG1(RED--);
  	               HAL_GPIO_WritePin(GPIOA, YELLOW_1_Pin, GPIO_PIN_RESET);
  	               HAL_GPIO_WritePin(GPIOA, GREEN_1_Pin, GPIO_PIN_SET);
  	               display7SEG2(YELLOW--);
  	               // Set 2: Yellow on, Red and Green off


  	               if (counter >= 2)
  	               {
  	                   state = 0;
  	                   counter = 0;
  	                   RED = 5;
  	                   YELLOW = 2;
  	               }
  	               break;
  	       }

  	       HAL_Delay(1000);
  	       counter++;
  	   }
      /* USER CODE BEGIN 3 */
    }
  /* USER CODE END 3 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, A_Pin|B_Pin|C_Pin|S3_Pin
                          |S4_Pin|S5_Pin|S6_Pin|D_Pin
                          |E_Pin|F_Pin|G_Pin|S0_Pin
                          |S1_Pin|S2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED_1_Pin|GREEN_1_Pin|YELLOW_1_Pin|RED_2_Pin
                          |GREEN_2_Pin|YELLOW_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : A_Pin B_Pin C_Pin S3_Pin
                           S4_Pin S5_Pin S6_Pin D_Pin
                           E_Pin F_Pin G_Pin S0_Pin
                           S1_Pin S2_Pin */
  GPIO_InitStruct.Pin = A_Pin|B_Pin|C_Pin|S3_Pin
                          |S4_Pin|S5_Pin|S6_Pin|D_Pin
                          |E_Pin|F_Pin|G_Pin|S0_Pin
                          |S1_Pin|S2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : RED_1_Pin GREEN_1_Pin YELLOW_1_Pin RED_2_Pin
                           GREEN_2_Pin YELLOW_2_Pin */
  GPIO_InitStruct.Pin = RED_1_Pin|GREEN_1_Pin|YELLOW_1_Pin|RED_2_Pin
                          |GREEN_2_Pin|YELLOW_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
const long long digitToSegment[] = {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111  // 9
    };

  void display7SEG1(int num) {
      if (num < 0 || num > 9) {
          return;
      }
      long long segments = digitToSegment[num];
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (segments & (1 << 0)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment a
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, (segments & (1 << 1)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment b
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, (segments & (1 << 2)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment c
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (segments & (1 << 3)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment d
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (segments & (1 << 4)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment e
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (segments & (1 << 5)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment f
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (segments & (1 << 6)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment g
  }

  void display7SEG2(int num) {
      if (num < 0 || num > 9) {
          return;
      }
      long long segments = digitToSegment[num];
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (segments & (1 << 0)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment a
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (segments & (1 << 1)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment b
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (segments & (1 << 2)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment c
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (segments & (1 << 3)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment d
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (segments & (1 << 4)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment e
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (segments & (1 << 5)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment f
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (segments & (1 << 6)) ? GPIO_PIN_RESET : GPIO_PIN_SET); // Segment g
  }

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
