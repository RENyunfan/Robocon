/**
  ******************************************************************************
  * 文件名          : SendSignal.c
  * 创建时间        : 2018.12.16
  * 作者            : 谢胜
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2019.02.15
  * 修改人          : 任云帆
  ******************************************************************************
  *									文件描述							       *
  ******************************************************************************
  *	定义了电机速度发送函数
  ******************************************************************************
  * 1.本代码基于STMF405RGT6开发，编译环境为Keil 5，基于FreeRTOS进行开发。
  * 2.本代码只适用于RoboMaster 2019步兵机器人，不建议用于其他用途
  * 3.本代码以UTF-8格式编码，请勿以ANSI编码形式打开
  * 4.本代码包含大量中文注释，请仔细通读代码后使用
  * 5.本代码最终解释权归哈尔滨工业大学（深圳）南工骁鹰战队所有
  *
  * Copyright (c) 2019 哈尔滨工业大学（深圳）南工骁鹰战队 版权所有
  ******************************************************************************
  */

#include "SendSignal.h"
#include "MR1Init.h"
#include "CanReceive.h"
#include "usart.h"
#include "string.h"
/**
* @brief 将陀螺仪修正命令发送至陀螺仪
* @param None
* @retval None
* @TODO None
*/
void SendGyro(int commond)
{
		uint8_t GyroCorrect[]="ATCR";
		uint8_t GyroReset[]="ATC0";

	switch(commond)
	{
		case 99:
				HAL_UART_Transmit_DMA(&huart6,GyroCorrect,4u);break;
		case 0:
				HAL_UART_Transmit_DMA(&huart6,GyroReset,4u);break;
	}

}


/**
* @brief 将计算得到的电机新参数发送给电机
* @param None
* @retval None
* @TODO None
*/
void SendSignal()
{
	if(MR1.WorkState == L2_Rx_STOP)        //如果机器人为停止状态，则电机初始化为0
	{
		CanTransmit_1234(&hcan1,0,0,0,0);
	}
	else                                  //当机器人不是停止状态时
	{
		CanTransmit_1234(&hcan1, MR1.Chassis_Motor[0].pid.output,
								 MR1.Chassis_Motor[1].pid.output,
								 MR1.Chassis_Motor[2].pid.output,
								 MR1.Chassis_Motor[3].pid.output);
		CanTransmit_5(&hcan1,MR1.Chassis_Motor[4].pid.output);
	}
}
/**
* @brief ID为1~4的电机信号发送函数
* @param ID为1~4的各个电机的电流数值
* @retval None
*/
void CanTransmit_1234(CAN_HandleTypeDef *hcanx, int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq)
{
	CAN_TxHeaderTypeDef TxMessage;
		
	TxMessage.DLC=0x08;
	TxMessage.StdId=0x200;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.RTR=CAN_RTR_DATA;

	uint8_t TxData[8];
	TxData[0] = (uint8_t)(cm1_iq >> 8);
	TxData[1] = (uint8_t)cm1_iq;
	TxData[2] = (uint8_t)(cm2_iq >> 8);
	TxData[3] = (uint8_t)cm2_iq;
	TxData[4] = (uint8_t)(cm3_iq >> 8);
	TxData[5] = (uint8_t)cm3_iq;
	TxData[6] = (uint8_t)(cm4_iq >> 8);
	TxData[7] = (uint8_t)cm4_iq; 

	if(HAL_CAN_AddTxMessage(hcanx,&TxMessage,TxData,(uint32_t*)CAN_TX_MAILBOX0)!=HAL_OK)
	{
		 Error_Handler();       //如果CAN信息发送失败则进入死循环
	}
}

/**
* @brief ID为5的电机信号发送函数
* @param ID为5的各个电机的电流数值
* @retval None
*/
void CanTransmit_5(CAN_HandleTypeDef *hcanx, int16_t cm5_iq)
{
	CAN_TxHeaderTypeDef TxMessage;
		
	TxMessage.DLC=0x08;
	TxMessage.StdId=0x1FF;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.RTR=CAN_RTR_DATA;

	uint8_t TxData[8];
	TxData[0] = (uint8_t)(cm5_iq >> 8);
	TxData[1] = (uint8_t)cm5_iq;


	if(HAL_CAN_AddTxMessage(hcanx,&TxMessage,TxData,(uint32_t*)CAN_TX_MAILBOX0)!=HAL_OK)
	{
		 Error_Handler();       //如果CAN信息发送失败则进入死循环
	}
}
