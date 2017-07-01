# SmartCar
2016电子设计竞赛-风动巡线小车
主控芯片：STM32F407    摄像头：线性CCD TSL1401    编码器：欧姆龙 光电式 200线

注意：几乎所有程序都放在 Hardware 文件夹里面了。 

PID控制算法 部分 在/Hardware/control.c 里面
黑线提取的程序 在/Hardware/ccd.c
时间控制和多任务控制 在/Hardware/Tim4_Sys.c

