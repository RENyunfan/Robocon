/**
  ******************************************************************************
  * 文件名          : can_motor.h
  * 创建时间        : 2019.01.16
  * 作者            : 陆伟建
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2019.01.16
  * 修改人          : 陆伟建
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

#ifndef _CANRECEIVE_H_
#define _CANRECEIVE_H_

#include "can.h"
#include "MR1Init.h"

/* 定义各个电机的CAN ID号 */
#define CAN_CHASSIS_MOTOR1_ID 0x201
#define CAN_CHASSIS_MOTOR2_ID 0x202
#define CAN_CHASSIS_MOTOR3_ID 0x203
#define CAN_CHASSIS_MOTOR4_ID 0x204
#define CAN_CHASSIS_MOTOR5_ID 0x205


#define CAN_BUF_SIZE 4

struct CAN_Motor
{
	int fdbSpeed;           //电机反馈的转速/rpm
	PID_s speed_pid;    	 //电机速度环PID
};

#define DEFAULT_CAN_MOTOR \
{0,\
	 DEFAULT_PID \
}




void CanDataReceive(int motor_index);
void CanDataEncoderProcess(PID_s *motor);
HAL_StatusTypeDef CanFilterInit(CAN_HandleTypeDef* hcan);
void CanDataEncoderProcess5(void);
void MotorParamInit(struct CAN_Motor *motor, int speedP, int speedI, int speedD,int speedOutmax);

#endif
