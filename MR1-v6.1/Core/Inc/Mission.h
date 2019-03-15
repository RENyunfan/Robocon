/**
  ******************************************************************************
  * 文件名          : user_logic.h
  * 创建时间        : 2018.12.16
  * 作者            : 谢胜
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2018.12.16
  * 修改人          : 谢胜
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

#ifndef _MISSION_H_
#define _MISSION_H_

#define AFA 45                              //轮子与车中心夹角
#define L 375                               //机器人轮子到中心的距离
void MR1_MANUAL(void);
void MR1_STOP(void);
void AUTOGoTrans(void);
void FourWheelVellControl(void);
void MR1_HighSpeed(void);
void MR1_SendSignal(void);
void MR1_SetStage(void);

#endif