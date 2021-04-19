/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "InverseKinematics.h"
#include "Servo.h"
#include "math.h"
#include "matrix_lib.h"
#include "Joystick.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//int a=10;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t Joystick[2];
int a ;
volatile int counter = 0;;
uint8_t Received;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  joystick joy;
  servo obiekt;
  servo_Init(&htim2);

  joystick_Start(&hadc1, &joy);



  //HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_1);
  //HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_2);
  //HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);
  HAL_UART_Receive_IT(&huart2, &Received, 1);
  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 //a = (__HAL_TIM_GET_COUNTER(&htim3))*360/40;

	 //if(counter == 5)
		// HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(matrix_ReadKey()==2)
	  {

		  while(matrix_ReadKey()==0 || matrix_ReadKey() == 2)
		  {
		  	  joystick_Control(&htim2, joy);
		  	  HAL_Delay(100);
		  }

	  }

	  if(matrix_ReadKey()==1)
	  {
		  InverseKinematics(6, 8,&obiekt);
		  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,Theta1((obiekt.servo1/3.14159)*180));
		  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,Theta2((obiekt.servo2/3.14159)*180));
		  InverseKinematics(0, 11,&obiekt);
		  HAL_Delay(3000);
		  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,Theta1((obiekt.servo1/3.14159)*180));
		  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,Theta2((obiekt.servo2/3.14159)*180));
	  }

	  //a= voltageToAngleX(joy);

	  //__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,Theta2(0));
	  //__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,Theta1(180));
//	  HAL_Delay(200);



	  //__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,Theta1(99));
	  	 //__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,Theta2(110));
	  //__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,Theta2(90));
//	 __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,1600);
//	 HAL_Delay(1000);
//	 __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,7600);
//
//	 __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1600);
//	 	 HAL_Delay(1000);
//	 	 __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,7600);
//
//	 	 __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,1600);
//	 		 	 HAL_Delay(1000);
//	 		 	 __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,7600);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
		counter++;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	uint8_t Data[50]; // Tablica przechowujaca wysylana wiadomosc.
	uint16_t size = 0; // Rozmiar wysylanej wiadomosci

	// Odebrany znak zostaje przekonwertowany na liczbe calkowita i sprawdzony
	// instrukcja warunkowa
	switch (atoi(&Received)) {

	case 0: // Jezeli odebrany zostanie znak 0
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);

		break;

	case 1: // Jezeli odebrany zostanie znak 1
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
		break;

	default: // Jezeli odebrano nieobslugiwany znak
		//size = sprintf(Data, "Odebrano nieznany znak: %c\n\r", Received);
		break;
	}

	 // Rozpoczecie nadawania danych z wykorzystaniem przerwan
	HAL_UART_Receive_IT(&huart2, &Received, 1); // Ponowne włączenie nasłuchiwania*/
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
