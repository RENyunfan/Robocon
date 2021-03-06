/**
  ******************************************************************************
  * 文件名          : freertos.c
  * 创建时间        : 2019.02.12
  * 作者            : 任云帆
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2019.02.15
  * 修改人          : 任云帆
  ******************************************************************************
	*																文件描述																		 *
	******************************************************************************
	*	操作系统启动，多任务线程管理
	******************************************************************************
  * 1.本代码基于STM32F427IIH6开发，编译环境为Keil 5，基于FreeRTOS进行开发。
  * 2.本代码只适用于Robocon 2019MR1机器人，不建议用于其他用途
  * 3.本代码以UTF-8格式编码，请勿以ANSI编码形式打开
  * 4.本代码包含大量中文注释，请仔细通读代码后使用
  * 5.本代码最终解释权归哈尔滨工业大学（深圳）南工问天战队所有
  *
  * Copyright (c) 2019 哈尔滨工业大学（深圳）南工问天战队 版权所有
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#include "Supervise.h"
#include "UsartReceive.h"
#include "CanReceive.h"
#include "MR1Init.h"
#include "Mission.h"
#include "Calculate.h"
#include "SendSignal.h"
#include "LED.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int flag ;
int aaa;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CHASSIS
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId MR1OtherHandle;
osThreadId LEDShowTaskHandle;
osThreadId RobotTaskHandle;
osTimerId SuperviseTimerHandle;
osSemaphoreId JudgeSignalHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void MR1OtherTask(void const * argument);
void LEDShow(void const * argument);
void MR1MainTask(void const * argument);
void SuperviseTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of JudgeSignal */
  osSemaphoreDef(JudgeSignal);
  JudgeSignalHandle = osSemaphoreCreate(osSemaphore(JudgeSignal), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of SuperviseTimer */
  osTimerDef(SuperviseTimer, SuperviseTask);
  SuperviseTimerHandle = osTimerCreate(osTimer(SuperviseTimer), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
		osTimerStart(SuperviseTimerHandle, 2);                   
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of MR1Other */
  osThreadDef(MR1Other, MR1OtherTask, osPriorityNormal, 0, 128);
  MR1OtherHandle = osThreadCreate(osThread(MR1Other), NULL);

  /* definition and creation of LEDShowTask */
  osThreadDef(LEDShowTask, LEDShow, osPriorityNormal, 0, 128);
  LEDShowTaskHandle = osThreadCreate(osThread(LEDShowTask), NULL);

  /* definition and creation of RobotTask */
  osThreadDef(RobotTask, MR1MainTask, osPriorityNormal, 0, 4096);
  RobotTaskHandle = osThreadCreate(osThread(RobotTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header_MR1OtherTask */
/**
  * @brief  未定义留作备用线程
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_MR1OtherTask */
void MR1OtherTask(void const * argument)
{

  /* USER CODE BEGIN MR1OtherTask */
  /* Infinite loop */
  for(;;)
  {
		if(MR1.Chassis_Motor[0].fdbSpeed>5000)
		{
			MR1.WorkState=L2_Rx_STOP;
			SendSignal();
		}
    osDelay(1);
  }
  /* USER CODE END MR1OtherTask */
}

/* USER CODE BEGIN Header_LEDShow */
/**
* @brief LED闪烁线程
* @param None
* @retval None
*/
/* USER CODE END Header_LEDShow */
void LEDShow(void const * argument)
{
  /* USER CODE BEGIN LEDShow */
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);//初始化为熄灭
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_14,GPIO_PIN_SET);//停止状态红灯亮
  /* Infinite loop */
  for(;;)
  {
//		switch(MR1.WorkState)
//		{
//			case L1_R2_MANUAL:
//				LED_MANUAL();break;
//			case L2_Rx_STOP:
//				LED_STOP();break;
//			case L3_R2_Move:
//				LED_HIGH();break;
//			default:;
//		}
		LED_Water();
		osDelay(1);
		
  }
  /* USER CODE END LEDShow */
}

/* USER CODE BEGIN Header_MR1MainTask */
/**
* @brief MR1工作主线程
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MR1MainTask */
void MR1MainTask(void const * argument)
{
  /* USER CODE BEGIN MR1MainTask */
	RobotParamInit();

	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET);//使能电机脚部
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_SET);//使能电机脚部
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET);//使能电机脚部
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,1750);
  /* Infinite loop */
  for(;;)
  {
		switch(MR1.WorkState)
		{
			case L1_R2_MANUAL:
				MR1_MANUAL();StopShoot();break;
			case L2_Rx_STOP:
				MR1_STOP();StopShoot();break;
			case L3_R2_Move:
				MR1_SetStage();StopShoot();break;
			case L3_R1_Pick:
				StopShoot(); break;
			case L1_R1_ToToken:
				MR1_ToToken();StopShoot();break;
			case 	L1_R3_TransToken:
				MR1_TransToken();StopShoot();break;
			case L3_R3_Shoot:
				MR1_Shoot();break;
			default:MR1_STOP();
		}

		osDelay(1);
       

  /* USER CODE END MR1MainTask */
		}
	}

/* SuperviseTask function */
void SuperviseTask(void const * argument)
{
  /* USER CODE BEGIN SuperviseTask */
  //  SuperVise(); 
  /* USER CODE END SuperviseTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/**
* @brief USART串口接收回调函数
* @param 串口实例句柄
* @retval None
*/
void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
	if(huart == &huart1)          //串口1作为遥控器接收句�?
	{
		HAL_UART_Receive_DMA(&huart1, UsartReceiveRemote, 18u);
		RemoteReceiveHandle();      //进入串口接收解码函数
  }
  else if(huart == &huart6)     //串口6作为�?螺仪接收句柄
	{
		HAL_UART_Receive_DMA(&huart6, &UsartReceiveGyro, 1u);
		GyroReceiveHandle();        //进入串口接收解码函数
	}
}

/**
* @brief CAN通信接收回调函数
* @param CAN接口实例句柄
* @retval None
*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef   RxHeader;
	if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, CanReceiveData) != HAL_OK)
  {
    Error_Handler();            //错误状�?�回调函�?
  }
  CanDataReceive(RxHeader.StdId);   //根据电机号对CAN接收进行解码
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
