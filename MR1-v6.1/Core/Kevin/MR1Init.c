/**
  ******************************************************************************
  * 文件名          : MR1Init.c
  * 创建时间        : 2019.02.12
  * 作者            : 任云帆
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2019.02.15
  * 修改人          : 任云帆
  ******************************************************************************
  *								文件描述     								   *
  ******************************************************************************
  *	本文件定义了MR1所有的全局变量和MR1初始化函数。
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

#include "MR1Init.h"
#include "string.h"
#include "CanReceive.h"
#include "UsartReceive.h"

MR1_s MR1;
int count = 0;
uint8_t UsartReceiveGyro;
uint8_t UsartReceiveRemote[18];               //遥控器接收的原始数据
uint8_t CanReceiveData[8];                      //CAN接收的电机反馈信息



/**
* @brief 机器人各种参数初始化
* @param None
* @retval None
* @TODO None
*/
void RobotParamInit()
{                                 //配置底盘4个3508电机的参数
	memset(&MR1,0,sizeof(MR1));      //把底盘电机的数据结构体清零
	for(int i=0;i<5;i++)
	{
		MR1.Chassis_Motor[i].pid.KP = 15;
		MR1.Chassis_Motor[i].pid.KI = 1;
		MR1.Chassis_Motor[i].pid.KD = 1;
		MR1.Chassis_Motor[i].pid.outputMax = 3500;
	}
//	MR1.GyroData.zangle=0;
//	MR1.GyroData.xangle=0;
//	MR1.GyroData.yangle=0;
//	MR1.GyroData.pos_x =0;
//	MR1.GyroData.pos_y =0;
//	MR1.GyroData.w_z   =0;
	MR1.WorkState = L2_Rx_STOP;          //初始化机器人状态为停止状态
}


