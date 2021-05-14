/**
  ******************************************************************************
  * @file    main.c
  * @author  ZZH/KYF
  * @version V3.0
  * @date    2021-05-14
  * @brief   更新串口2发送数据包
  ******************************************************************************
	*
	*1.基本串口通讯协议：
	*    	命令		 包头  类型位	命令位 数据位	包尾
	*			停止			FF		00			00	  00	   FF
	*			前进			FF		00			01	  00	   FF
	*			后退			FF		00			02  	00     FF
	*			左转			FF		00			03	  00	   FF
	*			右转			FF		00			04	  00	   FF
	* 		左前转		FF		00			05	  00	   FF
	*			左后转		FF		00			06	  00	   FF
	*			右前转		FF		00			07	  00	   FF
	*			右后转		FF		00			08	  00	   FF
	*      开灯	    FF	  05	    00	  00	   FF
	*      关灯	    FF	  05	    01	  00	   FF
	*      动作组n   FF    01      0n    00     FF	(n=0-15)
	******************************************************************************
**/ 

#include "stm32f10x.h"
#include "lock.h"
#include "led.h"
#include "usart.h"
#include "usart2.h"
#include "bsp_adc.h"
#include "Function.h"
#include "SysTick.h"

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

int main(void)
{	
	//ADC反馈检测初始化
	ADCx_Init();
	
	//串口初始化
	USART_Config();
	USART2_Config();
	
	//LOCK GPIO初始化
	LOCK_GPIO_Config();
	
	//LED GOIO初始化
	LED_GPIO_Config();
	
	//初始化Systick
	SysTick_Init();

	while(1)
	{
		//控制函数
		Communication_Decode();
	}
}
