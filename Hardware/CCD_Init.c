/***********************************************************
* Copyright (c) 2016,����ũҵ��ѧ������С��
* All rights reserved.
*
* �ļ����ƣ�ccd.c
* �ļ���ʶ����
* ժ    Ҫ��
*
* ��ǰ�汾��1.0
* ��    ��: Huws
* ������ڣ�2016��08��14��
*
* ƽ    ̨��STM32_F407    
*************************************************************/

#include "ccd_init.h"
#include "sys.h"

#define CCD_CLK PAout(3)// PA3
#define CCD_SI  PAout(4)// PA4

	u8 data[128];
	u8 data_last[128];
	
	float i_middle = 0;
	float	i_middle_last = 0;
	float i_middle_v = 0;  //�����ƶ��ٶ�
		
 void CCD_init(void)
 {
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 	
	 RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;				 //�˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
	 GPIO_SetBits(GPIOA,GPIO_Pin_3 | GPIO_Pin_4);						 //PA.1 PA.3 �����
	 
	 Adc_Init();

 }
 
  void CCD_reader(u8 *data)
 {	
	u8	i; 
	CCD_CLK = 0;
	CCD_SI  = 1;
	delay_us(1);
	CCD_CLK = 1;
	CCD_SI  = 0;
	delay_us(1);
	for(i=0;i<128;i++)
	{
		CCD_CLK = 0;
		*data++ = (u8)(Get_Adc_Average(ADC_Channel_5,2)*255/4096);
		CCD_CLK = 1;
		delay_us(1);
	}
 }
 
 
 void CCD_save(u8 *data)
 {
	int	i;
	for(i=0;i<128;i++)
	{
		data_last[i] = data[i];
	}		
 }
 
  void CCD_display(u8 *data)
 {	
	int	i;
 	for(i=127;i>=0;i--)
	{
		if(data[i]>230)
		{
			POINT_COLOR=WHITE;
			LCD_DrawLine(60+i, 130, 60+i, 150);
		}
		else
		{
			POINT_COLOR=BLACK;
			LCD_DrawLine(60+i, 130, 60+i, 150);
		}
	}
 }
 
//��ʼ��ADC															   
void  Adc_Init(void)
{    
  GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��

  //�ȳ�ʼ��ADC1ͨ��5 IO��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PA5 ͨ��5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 
 
	
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
  ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
  ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��
	
 
	ADC_Cmd(ADC1, ENABLE);//����ADת����	

}				  
//���ADCֵ
//ch: @ref ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
	u16 Get_Adc(u8 ch)   
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_us(5);
	}
	return temp_val/times;
} 
	 
u8 i1=0;
u8 i2=0;
u8 i3=0;

u8 state_ccd = 0;

u8 safe_state = 0;

u8 temp=0;

void ccd_process(u8 *data)
{
	static unsigned char	i;
	
	i_middle_last = i_middle;		//�ϴκ���λ��
	
 	for(i=0;i<=127;i++)
	{
		if(state_ccd==0)
		{
				if(data[i]>190)
			{
					i1=i;
					state_ccd=1;
			}
		}
		
		if (state_ccd==1)
		{
			temp=abs(data[i]-data[(i-1)]);
			if(temp>90)
			{
				i2=i;
				state_ccd=2;
			}
		}
		
			if(state_ccd==2)
		{
				if(data[i]>200)
			{
					i3=i;
					state_ccd=3;
			}
			else
			{
				i_middle = 95 ;
			}
		}
		
	}
		state_ccd=0;

	i_middle=(i2+i3)/2;
	
////
//	if(i_middle < 35)
//	{
//		safe_state = 2 ;  //
//	}
//	else if(i_middle > 90)
//	{
//		safe_state = 3 ;	//
//	}
//	else
//	{
//		safe_ok = 0;
//	}
//	
//	if(i1>60)
//	{
//		safe_state = 3;   //
//	}

	i_middle_v =  i_middle - i_middle_last ; // ���ߵ��ƶ��ٶ�
		
}


//void ccd_safe(u8 *data_last,u8 *data)
//{
//	static unsigned char	i;
//	u8 temp = 0 ;
//	u8 cnt = 0 ;
//	
// 	for(i=0;i<=127;i++)
//	{
//		temp += abs(data[i]-data_last[i]);
//	}
//	
//	if(temp<50)
//	{
//		cnt++;
//	}else
//	{
//		cnt=0;
//	}
//	
//	if(cnt>30)
//  {
//		safe_ok=2;
//		
//	}
//}



