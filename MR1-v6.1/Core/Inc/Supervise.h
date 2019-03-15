/**
  ******************************************************************************
  * 文件名          : supervise.h
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
  * 5.本代码最终解释权归哈尔滨工业大学（深圳）Robocon战队所有
  *
  * Copyright (c) 2019 哈尔滨工业大学（深圳）Robocon战队 版权所有
  ******************************************************************************
  */

#ifndef _SUPERVISE_H_
#define _SUPERVISE_H_

#include "stm32f4xx.h"

#define DETECT_NUM 5u 						/*未完全确定监测外设的数目（目前为5）*/
#define RC_INDEX 0
#define CHASSIS_MOTOR1_INDEX 1
#define CHASSIS_MOTOR2_INDEX 2
#define CHASSIS_MOTOR3_INDEX 3
#define CHASSIS_MOTOR4_INDEX 4
//#define GYRO_INDEX 5

void SuperVise(void);
void LostCounterFeed(int index);
int Is_Error(void);

#endif
