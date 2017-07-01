/***********************************************************
* Copyright (c) 2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：encode.c
* 文件标识：无
* 摘    要：
*
* 当前版本：1.0
* 作    者: Huws
* 完成日期：2016年08月20日
*
* 平    台：STM32_F407    
*************************************************************/


#include "Encode.h"

void Encode_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
 
  GPIO_InitStructure.GPIO_Pin = Encode1_PinA | Encode1_PinB | Encode2_PinA | Encode2_PinB ; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(Encode_Port, &GPIO_InitStructure);
	
	EXTIX_Init();
 
} 

 int En1_Count=0;
 int En2_Count=0;

 void EXTI9_5_IRQHandler(void)
{			
	/////编码器1
		if(EXTI_GetITStatus(EXTI_Line6)!=RESET) //A相
		{
			 if( Encode1_PinB_Sta )
			 {
						 En1_Count++;
			 }
			
			 EXTI_ClearITPendingBit(EXTI_Line6); 
		}
		
		if(EXTI_GetITStatus(EXTI_Line7)!=RESET)  //B相
		{
			if( Encode1_PinA_Sta )
			 {
					En1_Count--;
			 }

			EXTI_ClearITPendingBit(EXTI_Line7); 
			
		}
	/////编码器2
				if(EXTI_GetITStatus(EXTI_Line8)!=RESET)
		{
			 if( Encode2_PinB_Sta )
			 {
						 En2_Count++;
			 }
			
			 EXTI_ClearITPendingBit(EXTI_Line8); 
		}
		
		if(EXTI_GetITStatus(EXTI_Line9)!=RESET)
		{
			if( Encode2_PinA_Sta )
			 {
					En2_Count--;
			 }

			EXTI_ClearITPendingBit(EXTI_Line9); 
			
		}
}



void EXTIX_Init(void)
{

	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6);	//PA6 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource7);	//PA7 连接到中断线3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource9);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
}


