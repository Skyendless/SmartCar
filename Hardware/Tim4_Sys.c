/***********************************************************
* Copyright (c) 2015-2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：Tim4_Sys.c
* 文件标识：无
* 摘    要：
*
* 当前版本：1.0
* 作    者: Huws
* 完成日期：2016年08月14日
*
* 平    台：STM32_F407    
*************************************************************/

#include "Tim4_Sys.h"

static unsigned int TIM4_Cnt = 0;

void safe_protect(void);

u8 state=0;

void TIM4_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM4时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化TIM4
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器4更新中断
	TIM_Cmd(TIM4,ENABLE); //使能定时器4

}


u8 safe_state1 = 0;
int En1_Count_Speed = 0 ;
int En2_Count_Speed = 0 ;

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);
		TIM4_Cnt++;
			
				if (TIM4_Cnt% 10 == 0 ) //10ms
			{		
				En1_Count_Speed = En1_Count ;
				En2_Count_Speed = En2_Count ;
				En1_Count = 0;
				En2_Count = 0;
			}
			
				if (TIM4_Cnt%20 == 0 ) //ms  //50hz
			{
				
				CCD_reader(data);
				ccd_process(data);

				safe_protect();
			}
			
				if (TIM4_Cnt%1000 == 0 ) //200ms
			{

			}
			
    TIM4_Cnt = TIM4_Cnt%2000;	//1ms * 2000 =2000ms			
    }				
}

void safe_protect(void)
{
	if(task == 1)
	{
		Control_Task_1(i_middle);
	}
	else if (task == 2)
	{
		Control_Task_2(i_middle);
	}
}

void wait_blackline(void)
{
//
}

