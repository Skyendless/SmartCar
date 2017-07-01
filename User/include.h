/***********************************************************
* Copyright (c) 2016,����ũҵ��ѧ������С��
* All rights reserved.
*
* �ļ����ƣ�includes.h
* �ļ���ʶ����
* ժ    Ҫ��
*
* ��ǰ�汾��1.0
* ��    ��: Huws
* ������ڣ�2016��08��22��
*
* ƽ    ̨��STM32_F407    
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
