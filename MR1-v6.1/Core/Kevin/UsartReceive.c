/**
  ******************************************************************************
  * 文件名          : UsartReceive.c
  * 文件描述        : 遥控器数据解析
  * 创建时间        : 2019.01.16
  * 作者            : 任云帆
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2019.02.15
  * 修改人          : 任云帆
  ******************************************************************************
  *									文件描述							       *
  ******************************************************************************
  *	对遥控器接收数据进行解码，并实时更新机器人状态
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

#include "UsartReceive.h"
#include "stm32f4xx_hal_uart.h"
#include "Supervise.h"
#include "usart.h"
#include "main.h"
#include "MR1Init.h"
extern int count;
Remote_s Raw_Data;
int countt;
/**
* @brief 遥控器数据具体解析函数
* @param None
* @retval None
*/
void RemoteReceiveHandle()
{
	Raw_Data.ch0 = ((int16_t)UsartReceiveRemote[0] | ((int16_t)UsartReceiveRemote[1] << 8)) & 0x07FF; 
	Raw_Data.ch1 = (((int16_t)UsartReceiveRemote[1] >> 3) | ((int16_t)UsartReceiveRemote[2] << 5)) & 0x07FF;
	Raw_Data.ch2 = (((int16_t)UsartReceiveRemote[2] >> 6) | ((int16_t)UsartReceiveRemote[3] << 2) |
											 ((int16_t)UsartReceiveRemote[4] << 10)) & 0x07FF;
	Raw_Data.ch3 = (((int16_t)UsartReceiveRemote[4] >> 1) | ((int16_t)UsartReceiveRemote[5]<<7)) & 0x07FF;
	Raw_Data.left = ((UsartReceiveRemote[5] >> 4) & 0x000C) >> 2;
	Raw_Data.right = ((UsartReceiveRemote[5] >> 4) & 0x0003);
	//LostCounterFeed(RC_INDEX);  //每次接收到数据就重置遥控器计数器
  MR1StateChange();
}

void MR1StateChange()
{
      if(Raw_Data.left == 3) //停止模式
      {
          MR1.WorkState = L2_Rx_STOP;
      }
      
      else if(Raw_Data.left == 1) 
      {
          switch (Raw_Data.right)
              {
                  case 1:           
                      MR1.WorkState = L1_R1_ToToken;
                      break;
                  case 3:
                      MR1.WorkState = L1_R2_MANUAL;
                      break;
                  case 2:
                      MR1.WorkState = L1_R3_TransToken;
                      break;           
              }
      }
      
      else if(Raw_Data.left == 2) 
      {
          switch (Raw_Data.right)
              {
                  case 1:           
                      MR1.WorkState = L3_R1_Pick;
                      break;
                  case 3:
                      MR1.WorkState = L3_R2_Move;
                      break;
                  case 2:           
                      MR1.WorkState = L3_R3_Shoot;
                      break;          
              }
      }

      
      if(MR1.WorkState == L1_R2_MANUAL || MR1.WorkState == L3_R2_Move || MR1.WorkState == L3_R1_Pick)           //遥控器控制模式
      {
          MR1.Target.YSpeed = (Raw_Data.ch1 - CH0_BIAS) * MR1.SpeedLevel;
          MR1.Target.XSpeed = (Raw_Data.ch0 - CH1_BIAS) * MR1.SpeedLevel;
          MR1.Target.ASpeed = (Raw_Data.ch2 - CH3_BIAS) * MR1.SpeedLevel;
					MR1.Target.BSpeed = (Raw_Data.ch3 - CH3_BIAS) * MR1.SpeedLevel;
      }

}


void GyroReceiveHandle()
{
	static uint8_t count=0;
	static uint8_t i=0;
  uint8_t ch = UsartReceiveGyro;
	static union
  {
	 uint8_t data[24];
	 float ActVal[6];
  }posture;
	switch(count)
		 {
			 case 0:
				 if(ch==0x0d)
					 count++;
				 else
					 count=0;
				 break;
				 
			 case 1:
				 if(ch==0x0a)
				 {
					 i=0;
					 count++;
				 }
				 else if(ch==0x0d);
				 else
					 count=0;
				 break;
				 
			 case 2:
				 posture.data[i]=ch;
			   i++;
			   if(i>=24)
				 {
					 i=0;
					 count++;
				 }
				 break;
				 
			 case 3:
				 if(ch==0x0a)
					 count++;
				 else
					 count=0;
				 break;
				 
			 case 4:
				 if(ch==0x0d)
				 {
  				 MR1.GyroData.zangle=posture.ActVal[0];
	  		   MR1.GyroData.xangle=posture.ActVal[1];
		  	   MR1.GyroData.yangle=posture.ActVal[2];
			     MR1.GyroData.pos_x =posture.ActVal[3];
			     MR1.GyroData.pos_y =posture.ActVal[4];
			     MR1.GyroData.w_z   =posture.ActVal[5];
				 }
			   count=0;
				 break;
			 default:
				 count=0;
			   break;		 
		 
	 }
}



