/**
  ******************************************************************************
  * 文件名          : CanReceive.c
  * 创建时间        : 2018.02.02
  * 作者            : 任云帆
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2019.02.15
  * 修改人          : 任云帆
  ******************************************************************************
  *									文件描述							       *
  ******************************************************************************
  *	对电机信息进行解码
  ******************************************************************************
  * 1.本代码基于STMF405RGT6开发，编译环境为Keil 5，基于FreeRTOS进行开发。
  * 2.本代码只适用于RoboMaster 2019步兵机器人，不建议用于其他用途
  * 3.本代码以UTF-8格式编码，请勿以ANSI编码形式打开
  * 4.本代码包含大量中文注释，请仔细通读代码后使用
  * 5.本代码最终解释权归哈尔滨工业大学（深圳）Robocon战队所有
  *
  * Copyright (c) 2019 哈尔滨工业大学（深圳）Robocon战队 版权所有
  ******************************************************************************
  */
#include "CanReceive.h"
#include "Supervise.h"
#include "MR1Init.h"
                                               //定义底盘电机的参数结构体


/**
* @brief 根据电机信息的ID号进行对应的数据解析
* @param 电机ID号
* @retval None
*/
void CanDataReceive(int motor_index)
{

	switch(motor_index)
	{
		case CAN_CHASSIS_MOTOR1_ID:
			LostCounterFeed(CHASSIS_MOTOR1_INDEX);    //每一次接收到电机反馈数据就清空计数器
			CanDataEncoderProcess(&MR1.Chassis_Motor[0].pid);break;    //电机数据具体解析函数
		case CAN_CHASSIS_MOTOR2_ID:
			LostCounterFeed(CHASSIS_MOTOR2_INDEX);
			CanDataEncoderProcess(&MR1.Chassis_Motor[1].pid);break;
		case CAN_CHASSIS_MOTOR3_ID:
			LostCounterFeed(CHASSIS_MOTOR3_INDEX);
			CanDataEncoderProcess(&MR1.Chassis_Motor[2].pid);break;
		case CAN_CHASSIS_MOTOR4_ID:
			LostCounterFeed(CHASSIS_MOTOR4_INDEX);
			CanDataEncoderProcess(&MR1.Chassis_Motor[3].pid);break;
		case CAN_CHASSIS_MOTOR5_ID:
			LostCounterFeed(CHASSIS_MOTOR4_INDEX);
			CanDataEncoderProcess(&MR1.Chassis_Motor[4].pid);break;
		default:;
	}
}

/**
* @brief CAN通信电机的反馈数据具体解析函数
* @param 电机数据结构体
* @retval None
*/
void CanDataEncoderProcess(PID_s *motor)
{
	
	motor->fdb = CanReceiveData[2]<<8|CanReceiveData[3];
	motor->fdbPos = CanReceiveData[0]<<8|CanReceiveData[1];

  /* 将电机速度反馈值由无符号整型转变为有符号整型 */
	if(motor->fdb > 32768)
	{
		motor->fdb -= 65536;
	}
}


/**
* @brief CAN外设过滤器初始化
* @param can结构体
* @retval None
*/
HAL_StatusTypeDef CanFilterInit(CAN_HandleTypeDef* hcan)
{
  CAN_FilterTypeDef  sFilterConfig;

  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;
  
	if(hcan == &hcan1)
	{
		sFilterConfig.FilterBank = 0;
	}
	if(hcan == &hcan2)
	{
		sFilterConfig.FilterBank = 14;
	}
	
  if(HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_CAN_Start(hcan) != HAL_OK)
  {
    Error_Handler();
  }
	
  if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    Error_Handler();
  }

	return HAL_OK;
}
