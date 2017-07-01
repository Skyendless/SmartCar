/***********************************************************
* Copyright (c) 2015-2016,����ũҵ��ѧ������С��
* All rights reserved.
*
* �ļ����ƣ�main.c
* �ļ���ʶ����
* ժ    Ҫ��
*
* ��ǰ�汾��1.1
* ��    ��: Huws
* ������ڣ�2016��08��22��
*
* ƽ    ̨��STM32_F407    
*************************************************************/

#include "include.h"

	u8 key;
	u8 task = 0;
	
int main(void)
{   	
	KEY_Init();
	LED_Flash_Init();
	
	TIM2_PWM_Init(2500-1,84-1);   //84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ2500������PWMƵ��Ϊ 1M/2500=400hz  
	
	PID_Init();
	
	TIM4_Init(1000-1,84-1);  //1ms �ж�һ��
	
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



	

