/***********************************************************
* Copyright (c) 2015-2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：无
* 摘    要：
*
* 当前版本：1.1
* 作    者: Huws
* 完成日期：2016年08月22日
*
* 平    台：STM32_F407    
*************************************************************/

#include "include.h"

	u8 key;
	u8 task = 0;
	
int main(void)
{   	
	KEY_Init();
	LED_Flash_Init();
	
	TIM2_PWM_Init(2500-1,84-1);   //84M/84=1Mhz的计数频率,重装载值2500，所以PWM频率为 1M/2500=400hz  
	
	PID_Init();
	
	TIM4_Init(1000-1,84-1);  //1ms 中断一次
	
	CCD_init(); 
	
	Encode_Init();
	
		while(1)
	{
		key=KEY_Scan();
		if(key==1)
		{
			task = 1;
			LED_State=0;
		}else if(key==2)
		{
			task = 2;
			LED_State=1;
		}else if(key==3)
		{
			task = 0;
			motor_flash(0,0);
		}
	}
}



	

