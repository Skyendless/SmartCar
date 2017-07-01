/***********************************************************
* Copyright (c) 2015-2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：led.c
* 文件标识：无
* 摘    要：
*
* 当前版本：1.1
* 作    者: Huws
* 完成日期：2016年08月14日
*
* 平    台：STM32_F407    
*************************************************************/

#include "led.h"

unsigned int TIM3_Cnt = 0;
unsigned char LED_State = 0;


void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


void LED_Flash_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
	
	delay_ms(50);
	
	TIM3_Init(10000-1,84-1);			//定时器时钟84M，分频系数84，所以84M/84=1Mhz的计数频率， 1,000,000 / 10,000 = 100  //10ms
	
	LED_State=1;
}

void LED_Flash_0(void)    
{
	
	if(TIM3_Cnt == 6) ////6*10=60ms
	{
		LED_GREEN(1);
		LED_RED(1);
	}
	else if(TIM3_Cnt == 12) 
	{
		LED_GREEN(0);
		LED_RED(0);
	}
	else if(TIM3_Cnt == 18)
	{
		LED_GREEN(1);
		LED_RED(1);
	}
	else if(TIM3_Cnt == 24)
	{
		LED_GREEN(0);
		LED_RED(0);
	}
	else if(TIM3_Cnt == 30)
	{
		LED_GREEN(1);
		LED_RED(1);
	}
	else if(TIM3_Cnt == 36)
	{
		LED_GREEN(0);
		LED_RED(0);
	}
}


/* Green LED Trinkle 4 Times Quickly, it express Control Unlock State */
void LED_Flash_1(void)
{
	
	    if(TIM3_Cnt == 1)
	{
		LED_GREEN(1);
	}
	else if(TIM3_Cnt == 50)
	{
		LED_GREEN(0);
	}
		
	if(TIM3_Cnt == 100)
	{
		LED_GREEN(1);
	}
	else if(TIM3_Cnt == 150)
	{
		LED_GREEN(0);
	}
} 

///* Red LED Trinkle 4 Times quickly, it express Control Lock State */
//void LED_Flash_2(void)
//{
//    B(OFF);
//	G(OFF);
//	if(TIM3_Cnt == 100)
//	{
//		R(ON);
//		LIGHT(ON);
//	}
//	else if(TIM3_Cnt == 105)
//	{
//		R(OFF);
//		LIGHT(OFF);
//	}
//	else if(TIM3_Cnt == 110)
//	{
//		R(ON);
//	}
//	else if(TIM3_Cnt == 115)
//	{
//		R(OFF);
//	}
//	else if(TIM3_Cnt == 120)
//	{
//		R(ON);
//		LIGHT(ON);
//	}
//	else if(TIM3_Cnt == 125)
//	{
//		R(OFF);
//		LIGHT(ON);
//	}
//	else if(TIM3_Cnt == 130)
//	{
//		R(ON);
//	}
//	else if(TIM3_Cnt == 135)
//	{
//		R(OFF);
//	}
//} 



/* Blue Trinkle once slowly and orange LED Trinkle 4 times quickly, it express The state of RC Adjust*/
//void LED_Flash_3(void)
//{
//	if(TIM3_Cnt == 0)
//	{
//		B(ON);
//	}
//	else if(TIM3_Cnt == 20)
//	{
//		B(OFF);
//	}
//	
//	if(TIM3_Cnt == 100)
//	{
//		G(ON);
//		R(ON);
//	}
//	else if(TIM3_Cnt == 105)
//	{
//		G(OFF);
//		R(OFF);
//	}
//	else if(TIM3_Cnt == 110)
//	{
//		G(ON);
//		R(ON);
//	}
//	else if(TIM3_Cnt == 115)
//	{
//		G(OFF);
//		R(OFF);
//	}
//	else if(TIM3_Cnt == 120)
//	{
//		G(ON);
//		R(ON);
//	}
//	else if(TIM3_Cnt == 125)
//	{
//		G(OFF);
//			R(OFF);
//	}
//	else if(TIM3_Cnt == 130)
//	{
//		G(ON);
//		R(ON);
//	}
//	else if(TIM3_Cnt == 135)
//	{
//		G(OFF);
//		R(OFF);
//	}   
//}



void TIM3_IRQ(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
        switch(LED_State)
		{
			case 0: LED_Flash_0(); break;
			case 1: LED_Flash_1(); break;
//			case 2: LED_Flash_2(); break;
//			case 3: LED_Flash_3(); break;
		}
		TIM3_Cnt++;
    TIM3_Cnt = TIM3_Cnt%200;	//10ms * 200 =2000ms			
    }				
}


