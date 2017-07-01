/***********************************************************
* Copyright (c) 2016,湖南农业大学机器人小组
* All rights reserved.
*
* 文件名称：control.h
* 文件标识：无
* 摘    要：
*
* 当前版本：1.0
* 作    者: Huws
* 完成日期：2016年08月14日
*
* 平    台：STM32_F407    
*************************************************************/

#include "Control.h"

PID PID_CCD;
PID PID_ENCODE;

u16 Motor1;
u16 Motor2;


void PID_Init (void)
{
	PID_CCD.P = 25 ;
	PID_CCD.I = 0;
	PID_CCD.D = 50;
	
	PID_ENCODE.P = 30;
	PID_ENCODE.I = 0.2;
	PID_ENCODE.D = 50;
}
	
 float i_tar = 64;

 int En_Count_Speed = 0;

void Control_Task_1(float imiddle)  //快跑
{ 
		float temp1;
		float temp2;
		float Speed_Tar = 40; 
	
		static float CCD_Error = 0;
		static float CCD_Error_old = 0; 
		
		static float Speed_Error = 0 ;
		static float Speed_Error_old = 0 ;
		
		CCD_Error_old = CCD_Error;
		CCD_Error = imiddle - i_tar ;
//		Speed_Tar = Speed_Tar - 0.3(CCD_Error)
		temp1 = (CCD_Error - CCD_Error_old)/0.02f;
		
		Speed_Error_old = Speed_Error ;
		En_Count_Speed = En1_Count_Speed + En2_Count_Speed;
		Speed_Error = Speed_Tar - En_Count_Speed ;
		temp2 = Speed_Error - Speed_Error_old;
		
	
	//////CCD
			PID_CCD.P_Out = PID_CCD.P * CCD_Error;
			PID_CCD.I_Out += PID_CCD.I * CCD_Error;  
			if(PID_CCD.I_Out>300)
			{
				PID_CCD.I_Out=300;
			}
			PID_CCD.D_Out = PID_CCD.D * temp1;  //
			
			PID_CCD.Out = PID_CCD.P_Out + PID_CCD.I_Out + PID_CCD.D_Out;	
		
			Motor1 =  PID_ENCODE.P_Out + PID_CCD.Out ;
			Motor2 =  PID_ENCODE.P_Out - PID_CCD.Out ;
		
		
		/////ENCODE
		PID_ENCODE.P_Out = PID_ENCODE.P * Speed_Error;
		PID_ENCODE.I_Out += PID_ENCODE.I * Speed_Error;  
		if(PID_ENCODE.I_Out>1000)
		{
			PID_ENCODE.I_Out=1000;
		}
		PID_ENCODE.D_Out = PID_ENCODE.D * temp2;  //
		
		
		/////
		
		PID_CCD.Out = PID_CCD.P_Out + PID_CCD.I_Out + PID_CCD.D_Out;	
		
		PID_ENCODE.Out = PID_ENCODE.P_Out + PID_ENCODE.I_Out + PID_ENCODE.D_Out;
		
		Motor1 =   PID_ENCODE.Out + PID_CCD.Out ;
		Motor2 =   PID_ENCODE.Out - PID_CCD.Out ;
		

		motor_flash(Motor1,Motor2);
}

void Control_Task_2(float imiddle)  //慢跑
{ 
		float temp1;
		float temp2;
		float Speed_Tar = 10;
	
		static float CCD_Error = 0;
		static float CCD_Error_old = 0; 
		
		static float Speed_Error = 0 ;
		static float Speed_Error_old = 0 ;
		
		CCD_Error_old = CCD_Error;
		CCD_Error = imiddle - i_tar ;
//		Speed_Tar = Speed_Tar - 0.3(CCD_Error)
		temp1 = (CCD_Error - CCD_Error_old);
		
		Speed_Error_old = Speed_Error ;
		En_Count_Speed = (En1_Count_Speed + En2_Count_Speed)/2;
		Speed_Error = Speed_Tar - En_Count_Speed ;
		temp2 =  (Speed_Error - Speed_Error_old);
		
	
	//////CCD
			PID_CCD.P_Out = PID_CCD.P * CCD_Error;
			PID_CCD.I_Out += PID_CCD.I * CCD_Error;  
			if(PID_CCD.I_Out>300)
			{
				PID_CCD.I_Out=300;
			}
			PID_CCD.D_Out = PID_CCD.D * temp1;  //
			
			PID_CCD.Out = PID_CCD.P_Out + PID_CCD.I_Out + PID_CCD.D_Out;	
		
			Motor1 =  PID_ENCODE.P_Out + PID_CCD.Out ;
			Motor2 =  PID_ENCODE.P_Out - PID_CCD.Out ;
		
		
		/////ENCODE
		PID_ENCODE.P_Out = PID_ENCODE.P * Speed_Error;
		PID_ENCODE.I_Out += PID_ENCODE.I * Speed_Error;  
		if(PID_ENCODE.I_Out>1000)
		{
			PID_ENCODE.I_Out=1000;
		}
		PID_ENCODE.D_Out = PID_ENCODE.D * temp2;  //
		
		
		/////
		
		PID_CCD.Out = PID_CCD.P_Out + PID_CCD.I_Out + PID_CCD.D_Out;	
		
		PID_ENCODE.Out = PID_ENCODE.P_Out + PID_ENCODE.I_Out + PID_ENCODE.D_Out;
		
		Motor1 =   PID_ENCODE.Out + PID_CCD.Out ;
		Motor2 =   PID_ENCODE.Out - PID_CCD.Out ;
		

		motor_flash(Motor1,Motor2);
}

