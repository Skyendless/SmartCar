/***********************************************************
* Copyright (c) 2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：Tim4_Sys.h
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

#ifndef _TIM4_H_
#define _TIM4_H_


void TIM4_Init(u16 arr,u16 psc);
	
extern int En1_Count_Speed;
extern int En2_Count_Speed;

#endif

