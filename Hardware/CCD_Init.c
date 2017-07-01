/***********************************************************
* Copyright (c) 2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：ccd.c
* 文件标识：无
* 摘    要：
*
* 当前版本：1.0
* 作    者: Huws
* 完成日期：2016年08月14日
*
* 平    台：STM32_F407    
*************************************************************/

#include "ccd_init.h"
#include "sys.h"

#define CCD_CLK PAout(3)// PA3
#define CCD_SI  PAout(4)// PA4

	u8 data[128];
	u8 data_last[128];
	
	float i_middle = 0;
	float	i_middle_last = 0;
	float i_middle_v = 0;  //黑线移动速度
		
 void CCD_init(void)
 {
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 	
	 RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	 //使能PA端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;				 //端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
	 GPIO_SetBits(GPIOA,GPIO_Pin_3 | GPIO_Pin_4);						 //PA.1 PA.3 输出高
	 
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
 
//初始化ADC															   
void  Adc_Init(void)
{    
  GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟

  //先初始化ADC1通道5 IO口
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PA5 通道5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	 
 
	
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
  ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
  ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	
 
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	

}				  
//获得ADC值
//ch: @ref ADC_channels 
//通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
//返回值:转换结果
	u16 Get_Adc(u8 ch)   
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
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
	
	i_middle_last = i_middle;		//上次黑线位置
	
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

	i_middle_v =  i_middle - i_middle_last ; // 黑线的移动速度
		
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



