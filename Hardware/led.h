/***********************************************************
* Copyright (c) 2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：Led.h
* 文件标识：无
* 摘    要：
*
* 当前版本：1.0
* 作    者: Huws
* 完成日期：2016年08月14日
*
* 平    台：STM32_F407    
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

