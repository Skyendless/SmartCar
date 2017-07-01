/***********************************************************
* Copyright (c) 2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：includes.h
* 文件标识：无
* 摘    要：
*
* 当前版本：1.0
* 作    者: Huws
* 完成日期：2016年08月22日
*
* 平    台：STM32_F407    
*************************************************************/

#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include "stm32f4xx.h"
#include "stdio.h"
#include "delay.h"
#include "Key.h"
#include "led.h"
#include "lcd.h"
#include "Tim4_Sys.h"
#include "usart.h"
#include "ccd_init.h"
#include "pwm_out.h"
#include "touch.h" 
#include "Control.h"
#include "encode.h"


typedef struct
{
  float P;
	float I;
	float D;
	float P_Out;
	float I_Out;
	float D_Out;
	float IMAX;
	float Out;
}PID;


extern u8 task;
extern unsigned char LED_State;



#endif 
