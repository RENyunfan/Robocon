/**
  ******************************************************************************
  * 文件名          : MR1Init.h
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


#ifndef _MR1INIT_H_
#define _MR1INIT_H_

typedef unsigned char uint8_t;
typedef   signed          char int8_t;
typedef   signed short     int int16_t;


/**
* @brief MR1工作状态枚举类型
* @param None
* @retval None
*/
typedef enum 
{
	L1_R1_ToToken,					    //自动穿越丛林到达令牌交接处
	L1_R2_MANUAL,
	L1_R3_TransToken,			        //手动微调交接令牌
	L2_Rx_STOP,
	L3_R1_Pick,						//半自动拾起兽骨
	L3_R2_Move,						//半自动转移兽骨
	L3_R3_Shoot                     //半自动发射兽骨

}WorkState_e;

typedef struct 
{
	int16_t fdbPos;
	float KP;
	float KI;
	float KD;
	int error[2];
	int fdb;
	int ref;
	int cur_error;
	int output;
	int outputMax;
}PID_s;

/**
* @brief 遥控器接收数据解析结构体
* @param None
* @retval None
*/
typedef struct 
{
    int YSpeed;
    int XSpeed;
    int ASpeed;
		int BSpeed;
}Target_s;

/**
* @brief MR1移动电机结构体
* @param None
* @retval None
*/

typedef struct 
{
	uint8_t temper;			//电机温度
	int16_t fdbSpeed;


	PID_s pid;				//电机PID
}Motor_Move_s;

/**
* @brief 陀螺仪返回参数
* @param None
* @retval None
*/
typedef struct
{
	float pos_x;
	float pos_y;
	float zangle;
	float xangle;
	float yangle;
	float w_z;
}Gyro_s;



/**
* @brief MR1全部参数结构体
* @param None
* @retval None
*/
typedef struct
{
	Target_s Target;
	WorkState_e WorkState;
	Motor_Move_s Chassis_Motor[5];
	Gyro_s GyroData;

	int motor5;
	int SpeedLevel;
}MR1_s;


extern MR1_s MR1;
extern uint8_t UsartReceiveRemote[18];   
extern uint8_t UsartReceiveGyro;
extern uint8_t CanReceiveData[8]; 

void RobotParamInit(void);


#endif
