/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * æ–‡ä»¶å          : main.c
  * æ–‡ä»¶æè¿°        : æ–‡ä»¶ä¸»å‡½æ•°
  * åˆ›å»ºæ—¶é—´        : 2019.02.16
  * ä½œè€…            : ä»»äº‘å¸†
  *-----------------------------------------------------------------------------
  * æœ€è¿‘ä¿®æ”¹æ—¶é—´    : 2019.02.16
  * ä¿®æ”¹äºº          : ä»»äº‘å¸†
  ******************************************************************************
  * 1.æœ¬ä»£ç åŸºäºŽSTM32F427IIH6å¼€å‘ï¼Œç¼–è¯‘çŽ¯å¢ƒä¸ºKeil 5ï¼ŒåŸºäºŽFreeRTOSè¿›è¡Œå¼€å‘ã€‚
  * 2.æœ¬ä»£ç åªé€‚ç”¨äºŽRobocon 2019MR1æœºå™¨äººï¼Œä¸å»ºè®®ç”¨äºŽå…¶ä»–ç”¨é€”
  * 3.æœ¬ä»£ç ä»¥UTF-8æ ¼å¼ç¼–ç ï¼Œè¯·å‹¿ä»¥ANSIç¼–ç å½¢å¼æ‰“å¼€
  * 4.æœ¬ä»£ç åŒ…å«å¤§é‡ä¸­æ–‡æ³¨é‡Šï¼Œè¯·ä»”ç»†é€šè¯»ä»£ç åŽä½¿ç”¨
  * 5.æœ¬ä»£ç æœ€ç»ˆè§£é‡Šæƒå½’å“ˆå°”æ»¨å·¥ä¸šå¤§å­¦ï¼ˆæ·±åœ³ï¼‰å—å·¥é—®å¤©æˆ˜é˜Ÿæ‰€æœ‰
  *
  * Copyright (c) 2019 å“ˆå°”æ»¨å·¥ä¸šå¤§å­¦ï¼ˆæ·±åœ³ï¼‰å—å·¥é—®å¤©æˆ˜é˜Ÿ ç‰ˆæƒæ‰€æœ‰
  ******************************************************************************
  */

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CanReceive.h"
#include "UsartReceive.h"
#include "MR1Init.h"
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
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
//extern uint8_t GyroReceiveData; /*ÍÓÂÝÒÇ½ÓÊÕÊý¾Ý*/
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
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);       //PWM1,ÓÃÓÚ¿ØÖÆ»úÐµ×éµÄµç»ú£¨Ã»Ð´£©
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);       //PWM2,ÓÃÓÚ¿ØÖÆ»úÐµ×éµÄµç»ú£¨Ã»Ð´£©
	HAL_UART_Receive_DMA(&huart6, &UsartReceiveGyro, 1u);      //¿ªÆôÍÓÂÝÒÇÊý¾Ý½ÓÊÕ´®¿Ú6
  HAL_UART_Receive_DMA(&huart1, UsartReceiveRemote, 18u);              //¿ªÆôÒ£¿ØÆ÷Êý¾Ý½ÓÊÕ´®¿Ú1
	CanFilterInit(&hcan1);          //³õÊ¼»¯CAN1¹ýÂËÆ÷
	CanFilterInit(&hcan2);          //³õÊ¼»¯CAN2¹ýÂËÆ÷
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

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

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
