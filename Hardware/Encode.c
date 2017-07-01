/***********************************************************
* Copyright (c) 2016,����ũҵ��ѧ������С��
* All rights reserved.
*
* �ļ����ƣ�encode.c
* �ļ���ʶ����
* ժ    Ҫ��
*
* ��ǰ�汾��1.0
* ��    ��: Huws
* ������ڣ�2016��08��20��
*
* ƽ    ̨��STM32_F407    
*************************************************************/


#include "Encode.h"

void Encode_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
 
  GPIO_InitStructure.GPIO_Pin = Encode1_PinA | Encode1_PinB | Encode2_PinA | Encode2_PinB ; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(Encode_Port, &GPIO_InitStructure);
	
	EXTIX_Init();
 
} 

 int En1_Count=0;
 int En2_Count=0;

 void EXTI9_5_IRQHandler(void)
{			
	/////������1
		if(EXTI_GetITStatus(EXTI_Line6)!=RESET) //A��
		{
			 if( Encode1_PinB_Sta )
			 {
						 En1_Count++;
			 }
			
			 EXTI_ClearITPendingBit(EXTI_Line6); 
		}
		
		if(EXTI_GetITStatus(EXTI_Line7)!=RESET)  //B��
		{
			if( Encode1_PinA_Sta )
			 {
					En1_Count--;
			 }

			EXTI_ClearITPendingBit(EXTI_Line7); 
			
		}
	/////������2
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
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6);	//PA6 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource7);	//PA7 ���ӵ��ж���3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource9);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
}


