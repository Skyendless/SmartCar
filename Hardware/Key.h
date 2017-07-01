/***********************************************************
* Copyright (c) 2016,����ũҵ��ѧ������С��
* All rights reserved.
*
* �ļ����ƣ�key.h
* �ļ���ʶ����
* ժ    Ҫ��
*
* ��ǰ�汾��1.0
* ��    ��: Huws
* ������ڣ�2016��08��14��
*
* ƽ    ̨��STM32_F407    
*************************************************************/

#include "include.h"

#ifndef _KEY_H_
#define _KEY_H_


#define KEY1 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_13)
#define KEY2 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_14)	
#define KEY3 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_15) 


void KEY_Init(void);
u8 KEY_Scan(void);	
	

#endif

