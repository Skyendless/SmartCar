/***********************************************************
* Copyright (c) 2015-2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：pwm_out.h
* 文件标识：无
* 摘    要：
*
* 当前版本：1.0
* 作    者: Huws
* 完成日期：2016年08月14日
*
* 平    台：STM32_F407    
*************************************************************/


#ifndef _MOTOR_H
#define _MOTOR_H


#include "include.h"

void TIM2_PWM_Init(u32 arr,u32 psc);

void motor_flash(u16 speed1,u16 speed2);

void tim2_cmd(u8 sta);

#endif


