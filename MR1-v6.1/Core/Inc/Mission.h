/**
  ******************************************************************************
  * 文件名          : Mission.h
  * 创建时间        : 2018.2.16
  * 作者            : 任云帆
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2018.03.15
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

#ifndef _MISSION_H_
#define _MISSION_H_

#define AFA 45                              //轮子与车中心夹角
#define L 375                               //机器人轮子到中心的距离

#define AFA 45                              //杞瓙涓庤溅涓績澶硅
#define L 375                               //鏈哄櫒浜鸿疆瀛愬埌涓績鐨勮窛绂?
#define MR1_Ttarget_pos_x1 -(725+500)
#define MR1_Ttarget_pos_y1 (1500+150)
#define MR1_Ttarget_pos_x2 -(725-500)
#define MR1_Ttarget_pos_y2 (3000+250)
#define MR1_Ttarget_pos_x3 -(725+500)
#define MR1_Ttarget_pos_y3 (4500+250)
#define MR1_Ttarget_pos_x4 -725
#define MR1_Ttarget_pos_y4 6000
#define MR1_Ttarget_pos_x5 -725
#define MR1_Ttarget_pos_y5 7500
#define MR1_Ttarget_pos_angle 0
#define MR1_Ttarget_Speed_x_MAX 4000
#define MR1_Ttarget_Speed_y 3500
void MR1_MANUAL(void);
void MR1_STOP(void);
void AUTOGoTrans(void);
void FourWheelVellControl(void);
void MR1_HighSpeed(void);
void MR1_SendSignal(void);
void MR1_SetStage(void);
void MR1_ToToken(void);
void MR1_TransToken(void);
void StopShoot(void);
void MR1_Shoot(void);

#endif
