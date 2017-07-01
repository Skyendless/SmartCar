/***********************************************************
* Copyright (c) 2015-2016,����ũҵ��ѧ������С��
* All rights reserved.
*
* �ļ����ƣ�led.c
* �ļ���ʶ����
* ժ    Ҫ��
*
* ��ǰ�汾��1.1
* ��    ��: Huws
* ������ڣ�2016��08��14��
*
* ƽ    ̨��STM32_F407    
*************************************************************/

#include "led.h"

unsigned int TIM3_Cnt = 0;
unsigned char LED_State = 0;


void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


void LED_Flash_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO
	
	delay_ms(50);
	
	TIM3_Init(10000-1,84-1);			//��ʱ��ʱ��84M����Ƶϵ��84������84M/84=1Mhz�ļ���Ƶ�ʣ� 1,000,000 / 10,000 = 100  //10ms
	
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


