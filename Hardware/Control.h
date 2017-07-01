/***********************************************************
* Copyright (c) 2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：ccd.h
* 文件标识：无
* 摘    要：
*
* 当前版本：1.0
* 作    者: Huws
* 完成日期：2016年08月14日
*
* 平    台：STM32_F407    
*************************************************************/


#ifndef __CONTORL_H
#define __CONTORL_H	


#include "include.h" 

void Control_Task_1(float imiddle);
void Control_Task_2(float imiddle);
void PID_Init (void);

#endif

