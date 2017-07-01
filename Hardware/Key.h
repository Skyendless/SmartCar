/***********************************************************
* Copyright (c) 2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：key.h
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

#ifndef _KEY_H_
#define _KEY_H_


#define KEY1 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_13)
#define KEY2 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_14)	
#define KEY3 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_15) 


void KEY_Init(void);
u8 KEY_Scan(void);	
	

#endif

