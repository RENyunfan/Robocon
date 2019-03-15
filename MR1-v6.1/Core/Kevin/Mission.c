/**
  ******************************************************************************
  * 文件名          : Mission.c
  * 创建时间        : 2019.02.12
  * 作者            : 任云帆
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2019.02.15
  * 修改人          : 任云帆
  ******************************************************************************
	*																文件描述																		 *
	******************************************************************************
	*	本文件定义了MR1所有工作函数。
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

#include "Mission.h"
#include "Calculate.h"				//使用FourWheelVellControl();函数
#include "SendSignal.h"				//使用SendSignal();函数
#include "MR1Init.h"
#include <math.h>

/**
* @brief MR1手动模式
* @param None
* @retval None
*/
void MR1_SendSignal()
{
		FourWheelVellControl();
		Calculate();
		SendSignal();
}
/**
* @brief MR1放置平台
* @param None
* @retval None
*/
void MR1_SetStage()
{
	if(MR1.Target.BSpeed>1000)
	MR1.Chassis_Motor[4].pid.ref=500;
	else if(MR1.Target.BSpeed<-1000)
	MR1.Chassis_Motor[4].pid.ref=-500;
	else MR1.Chassis_Motor[4].pid.ref=0;
	Calculate();
	SendSignal();
}




/**
* @brief MR1手动模式
* @param None
* @retval None
*/
void MR1_MANUAL()
{
		MR1.SpeedLevel = 10;

}


/**
* @brief MR1停止
* @param None
* @retval None
*/
void MR1_STOP()
{
	MR1.Target.ASpeed = 0;
	MR1.Target.XSpeed = 0;
	MR1.Target.YSpeed = 0;
}



