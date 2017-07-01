/***********************************************************
* Copyright (c) 2016,����ũҵ��ѧ������С��
* All rights reserved.
*
* �ļ����ƣ�Led.h
* �ļ���ʶ����
* ժ    Ҫ��
*
* ��ǰ�汾��1.0
* ��    ��: Huws
* ������ڣ�2016��08��14��
*
* ƽ    ̨��STM32_F407    
*************************************************************/

#ifndef _LED_FLASH_H_
#define _LED_FLASH_H_


#include "include.h"


#define    LED_GREEN(x)  x ? GPIO_SetBits(GPIOC, GPIO_Pin_2): GPIO_ResetBits(GPIOC, GPIO_Pin_2)
#define    LED_RED(x)  x ? GPIO_SetBits(GPIOC, GPIO_Pin_1): GPIO_ResetBits(GPIOC, GPIO_Pin_1)
#define    LED_BLUE(x)  x ? GPIO_SetBits(GPIOC, GPIO_Pin_0): GPIO_ResetBits(GPIOC, GPIO_Pin_0)


void TIM3_Init(u16 arr,u16 psc);
//void TIM6_ON(void);
//void TIM6_OFF(void);
void LED_Flash_Init(void);
void TIM3_IRQ(void);
void LED_Flash_0(void);
void LED_Flash_1(void);
//void LED_Flash_2(void);
//void LED_Flash_3(void);





#endif

