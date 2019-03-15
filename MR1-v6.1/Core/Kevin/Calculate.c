/**
  ******************************************************************************
  * 文件名          : Calculate.c
  * 文件描述        : 机器人的各个参数计算
  * 创建时间        : 2019.01.16
  * 作者            : 陆伟建
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2019.02.15
  * 修改人          : 任云帆
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

#include "Calculate.h"
#include "CanReceive.h"
#include "MR1Init.h"
#include <math.h>

/**
* @brief 机器人各种参数计算更新
* @param None
* @retval None
* @TODO None
*/
void Calculate()
{                      
	PID_Calc(&MR1.Chassis_Motor[0].pid);         //进行PID速度环计算
	PID_Calc(&MR1.Chassis_Motor[1].pid);
	PID_Calc(&MR1.Chassis_Motor[2].pid);
	PID_Calc(&MR1.Chassis_Motor[3].pid);
	PID_Calc(&MR1.Chassis_Motor[4].pid);
}

void PID_Calc(PID_s *pid)
{
	pid->cur_error = pid->ref - pid->fdb;
	pid->output += pid->KP * (pid->cur_error - pid->error[1])  + pid->KI * pid->cur_error + pid->KD * (pid->cur_error - 2 * pid->error[1] + pid->error[0]);
	pid->error[0] = pid->error[1]; 
	pid->error[1] = pid->ref - pid->fdb;
	/*设定输出上限*/
	if(pid->output > pid->outputMax) pid->output = pid->outputMax;
	if(pid->output < -pid->outputMax) pid->output = -pid->outputMax;
}

/**
* @brief 四轮运动算法
* @param None
* @retval None
*/
void FourWheelVellControl()
{
	double Vx,Vy,Va,vol[4];
	double len = L;
	Vx = MR1.Target.XSpeed;
	Vy = MR1.Target.YSpeed;
	Va = MR1.Target.ASpeed;
	if(Va > 10 || Va < -10)
	{
		for(int i=0;i<4;i++)
		{
			vol[i] = Va;
		}
	}
  else
	  {
		vol[0]=(double)(sin((AFA) / 180.0f * 3.1415926f) * Vx - cos((AFA) / 180.0f * 3.1415926f)*Vy+len * Va);//计算各轮子的转速
		vol[1]=(double)(-sin((AFA) / 180.0f * 3.1415926f) * Vx - cos((AFA) / 180.0f * 3.1415926f)*Vy+len * Va);
		vol[2]=(double)(-sin((AFA) / 180.0f * 3.1415926f) * Vx + cos((AFA) / 180.0f * 3.1415926f)*Vy+len * Va);
		vol[3]=(double)(sin((AFA) / 180.0f * 3.1415926f) * Vx + cos((AFA) / 180.0f * 3.1415926f)*Vy+len * Va);
	  }
/******************************double转int******************************************/
	MR1.Chassis_Motor[0].pid.ref = (int) vol[0];
	MR1.Chassis_Motor[1].pid.ref = (int) vol[1];
	MR1.Chassis_Motor[2].pid.ref = (int) vol[2];
	MR1.Chassis_Motor[3].pid.ref = (int) vol[3];
}
