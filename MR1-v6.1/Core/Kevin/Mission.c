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
#include "tim.h"

/**
* @brief MR1手动模式
* @param None
* @retval None
*/
void MR1_SendSignal()
{
		//FourWheelVellControl();
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
	if(MR1.Target.YSpeed>1000)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_SET);
	}
	else if(MR1.Target.YSpeed<-1000)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_RESET);
	}
	if(MR1.Target.BSpeed>2000)
	MR1.Chassis_Motor[4].pid.ref=-4500;
	else if(MR1.Target.BSpeed<-2000)
	MR1.Chassis_Motor[4].pid.ref=4500;
	else MR1.Chassis_Motor[4].pid.ref=0;
	Calculate();
	SendSignal();
		//HAL_Delay(2000);
}

/**
* @brief MR1发射兽骨
* @param None
* @retval None
*/
void MR1_Shoot()
{
	//if(MR1.Target.YSpeed>3000)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2,GPIO_PIN_RESET);
	}
//	else
//	{
//	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2,GPIO_PIN_RESET);
//	}

		//HAL_Delay(2000);
}


/**
* @brief 电磁阀电压置零
* @param None
* @retval None
*/
void StopShoot()
{
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2,GPIO_PIN_RESET);

}




/**
* @brief MR1自动穿越丛林
* @param None
* @retval None
*/
void MR1_ToToken()
{
	if ( MR1.GyroData.pos_y<=MR1_Ttarget_pos_y1)
	{
//	MR1.ToToken_Speed_x.ref=MR1_Ttarget_pos_x1-MR1.GyroData.pos_x;//自动模式x方向参考速度
//	MR1.ToToken_Speed_y.ref=MR1_Ttarget_pos_y1-MR1.GyroData.pos_y;//自动模式y方向参考速度
//	PID_Calc(&MR1.ToToken_Speed_x);
	MR1.Target.XSpeed=MR1.ToToken_Speed_x.KP*(MR1_Ttarget_pos_x1-(int)MR1.GyroData.pos_x);//X方向速度
		if(MR1.Target.XSpeed<-MR1_Ttarget_Speed_x_MAX)
		{
			MR1.Target.XSpeed=-MR1_Ttarget_Speed_x_MAX;
		}
		if(MR1.Target.XSpeed>MR1_Ttarget_Speed_x_MAX)
		{
			MR1.Target.XSpeed=MR1_Ttarget_Speed_x_MAX;
		}
	MR1.Target.YSpeed=MR1_Ttarget_Speed_y;//Y方向匀速
		
	}
	else if (MR1.GyroData.pos_y<=MR1_Ttarget_pos_y2&&MR1.GyroData.pos_y>MR1_Ttarget_pos_y1)
	{
//	MR1.ToToken_Speed_x.ref=MR1_Ttarget_pos_x2-MR1.GyroData.pos_x;//自动模式x方向参考速度
//	MR1.ToToken_Speed_y.ref=MR1_Ttarget_pos_y2-MR1.GyroData.pos_y;//自动模式y方向参考速度
//	PID_Calc(&MR1.ToToken_Speed_x);
	MR1.Target.XSpeed=MR1.ToToken_Speed_x.KP*(MR1_Ttarget_pos_x2-(int)MR1.GyroData.pos_x);//X方向速度
		if(MR1.Target.XSpeed<-MR1_Ttarget_Speed_x_MAX)
		{
			MR1.Target.XSpeed=-MR1_Ttarget_Speed_x_MAX;
		}
		if(MR1.Target.XSpeed>MR1_Ttarget_Speed_x_MAX)
		{
			MR1.Target.XSpeed=MR1_Ttarget_Speed_x_MAX;
		}
	MR1.Target.YSpeed=MR1_Ttarget_Speed_y-500;//Y方向匀速
		
	}
	else if (MR1.GyroData.pos_y<=MR1_Ttarget_pos_y3&&MR1.GyroData.pos_y>MR1_Ttarget_pos_y2)
	{
//	MR1.ToToken_Speed_x.ref=MR1_Ttarget_pos_x3-MR1.GyroData.pos_x;//自动模式x方向参考速度
//	MR1.ToToken_Speed_y.ref=MR1_Ttarget_pos_y3-MR1.GyroData.pos_y;//自动模式y方向参考速度
//	PID_Calc(&MR1.ToToken_Speed_x);
	MR1.Target.XSpeed=MR1.ToToken_Speed_x.KP*(MR1_Ttarget_pos_x3-(int)MR1.GyroData.pos_x);//X方向速度
		if(MR1.Target.XSpeed<-MR1_Ttarget_Speed_x_MAX)
		{
			MR1.Target.XSpeed=-MR1_Ttarget_Speed_x_MAX;
		}
		if(MR1.Target.XSpeed>MR1_Ttarget_Speed_x_MAX)
		{
			MR1.Target.XSpeed=MR1_Ttarget_Speed_x_MAX;
		}
	MR1.Target.YSpeed=MR1_Ttarget_Speed_y;//Y方向匀速
	}
	else if (MR1.GyroData.pos_y<=MR1_Ttarget_pos_y4&&MR1.GyroData.pos_y>MR1_Ttarget_pos_y3)
	{
//	MR1.ToToken_Speed_x.ref=MR1_Ttarget_pos_x3-MR1.GyroData.pos_x;//自动模式x方向参考速度
//	MR1.ToToken_Speed_y.ref=MR1_Ttarget_pos_y3-MR1.GyroData.pos_y;//自动模式y方向参考速度
//	PID_Calc(&MR1.ToToken_Speed_x);
	MR1.Target.XSpeed=MR1.ToToken_Speed_x.KP*(MR1_Ttarget_pos_x4-(int)MR1.GyroData.pos_x);//X方向速度
		if(MR1.Target.XSpeed<-MR1_Ttarget_Speed_x_MAX)
		{
			MR1.Target.XSpeed=-MR1_Ttarget_Speed_x_MAX;
		}
		if(MR1.Target.XSpeed>MR1_Ttarget_Speed_x_MAX)
		{
			MR1.Target.XSpeed=MR1_Ttarget_Speed_x_MAX;
		}
	MR1.Target.YSpeed=MR1_Ttarget_Speed_y;//Y方向匀速
	}
	else if (MR1.GyroData.pos_y<=MR1_Ttarget_pos_y5&&MR1.GyroData.pos_y>MR1_Ttarget_pos_y4)
	{
//	MR1.ToToken_Speed_x.ref=MR1_Ttarget_pos_x3-MR1.GyroData.pos_x;//自动模式x方向参考速度
//	MR1.ToToken_Speed_y.ref=MR1_Ttarget_pos_y3-MR1.GyroData.pos_y;//自动模式y方向参考速度
//	PID_Calc(&MR1.ToToken_Speed_x);

	MR1.Target.YSpeed=MR1_Ttarget_Speed_y;//Y方向匀速
	}
	else
	{
	 MR1.WorkState=L2_Rx_STOP;
	}
//	MR1.ToToken_Theta.fdb=MR1_Ttarget_pos_angle-MR1.GyroData.zangle;
//	PID_Calc(&MR1.ToToken_Theta);
	MR1.Target.ASpeed=MR1.ToToken_Theta.KP*((int)MR1.GyroData.zangle-MR1_Ttarget_pos_angle);//转动速度
	FourWheelVellControl();
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
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,1650);
	if(MR1.Target.BSpeed>2000)
	MR1.Chassis_Motor[4].pid.ref=-4500;
	else if(MR1.Target.BSpeed<-2000)
	MR1.Chassis_Motor[4].pid.ref=4500;
	else MR1.Chassis_Motor[4].pid.ref=0;
	FourWheelVellControl();	
	MR1_SendSignal();
}

/**
* @brief MR1松开兽骨
* @param None
* @retval None
*/
void MR1_TransToken()
{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,2000);
}


/**
* @brief MR1停止
* @param None
* @retval None
*/
void MR1_STOP()
{
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET);//使能电机脚部
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);//使能电机脚部
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);//使能电机脚部
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);//使能电机脚部
	MR1.Target.ASpeed = 0;
	MR1.Target.XSpeed = 0;
	MR1.Target.YSpeed = 0;
	MR1.Chassis_Motor[4].pid.ref=0;
	MR1.Chassis_Motor[3].pid.ref=0;
	MR1.Chassis_Motor[2].pid.ref=0;
	MR1.Chassis_Motor[1].pid.ref=0;
	MR1.Chassis_Motor[0].pid.ref=0;
	MR1_SendSignal();
}


