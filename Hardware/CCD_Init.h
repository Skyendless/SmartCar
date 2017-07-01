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


#ifndef __CCD_H
#define __CCD_H	


#include "include.h" 


extern u8 data[128];

extern float i_middle;
extern float i_middle_v;
extern u8 safe_state;
//extern u8 i2;
//extern u8 i3;

void CCD_init(void);
void CCD_reader(u8 *data);
void CCD_display(u8 *data);
void ccd_process(u8 *data);
void CCD_save(u8 *data);

void Adc_Init(void); 				//ADC通道初始化
u16  Get_Adc(u8 ch); 				//获得某个通道值 
u16 Get_Adc_Average(u8 ch,u8 times);//得到某个通道给定次数采样的平均值  


#endif 
