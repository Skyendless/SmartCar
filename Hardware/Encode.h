/***********************************************************
* Copyright (c) 2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：Encode.h
* 文件标识：无
* 摘    要：
*
* 当前版本：1.0
* 作    者: Huws
* 完成日期：2016年08月14日
*
* 平    台：STM32_F407    
*************************************************************/

#include "include.h"

#ifndef _Encde_H_
#define _Encde_H_

#define Encode_Port 	GPIOA

#define Encode1_PinA 		GPIO_Pin_6
#define Encode1_PinB		GPIO_Pin_7

#define Encode2_PinA 		GPIO_Pin_8
#define Encode2_PinB		GPIO_Pin_9

#define Encode1_PinA_Sta 		GPIO_ReadInputDataBit(Encode_Port,Encode1_PinA)
#define Encode1_PinB_Sta 		GPIO_ReadInputDataBit(Encode_Port,Encode1_PinB)	

#define Encode2_PinA_Sta 		GPIO_ReadInputDataBit(Encode_Port,Encode2_PinA)
#define Encode2_PinB_Sta 		GPIO_ReadInputDataBit(Encode_Port,Encode2_PinB)	

extern int En1_Count;
extern int En2_Count;

void Encode_Init(void);
void EXTIX_Init(void);
	

#endif

