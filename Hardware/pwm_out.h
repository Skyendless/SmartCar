/***********************************************************
* Copyright (c) 2015-2016,����ũҵ��ѧ������С��
* All rights reserved.
*
* �ļ����ƣ�pwm_out.h
* �ļ���ʶ����
* ժ    Ҫ��
*
* ��ǰ�汾��1.0
* ��    ��: Huws
* ������ڣ�2016��08��14��
*
* ƽ    ̨��STM32_F407    
*************************************************************/


#ifndef _MOTOR_H
#define _MOTOR_H


#include "include.h"

void TIM2_PWM_Init(u32 arr,u32 psc);

void motor_flash(u16 speed1,u16 speed2);

void tim2_cmd(u8 sta);

#endif


