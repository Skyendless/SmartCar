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


#ifndef __CCD_H
#define __CCD_H	


#include "include.h" 


extern u8 data[128];

extern float i_middle;
extern float i_middle_v;
extern u8 safe_state;
//extern u8 i2;
//extern u8 i3;

void CCD_init(void);
void CCD_reader(u8 *data);
void CCD_display(u8 *data);
void ccd_process(u8 *data);
void CCD_save(u8 *data);

void Adc_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  


#endif 
