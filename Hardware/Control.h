/***********************************************************
* Copyright (c) 2016,����ũҵ��ѧ������С��
* All rights reserved.
*
* �ļ����ƣ�ccd.h
* �ļ���ʶ����
* ժ    Ҫ��
*
* ��ǰ�汾��1.0
* ��    ��: Huws
* ������ڣ�2016��08��14��
*
* ƽ    ̨��STM32_F407    
*************************************************************/


#ifndef __CONTORL_H
#define __CONTORL_H	


#include "include.h" 

void Control_Task_1(float imiddle);
void Control_Task_2(float imiddle);
void PID_Init (void);

#endif

