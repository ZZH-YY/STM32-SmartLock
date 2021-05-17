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
	*    			 包头  类型位	命令位 包尾
	*						FF		00			00	  FF    已开锁
	*						FF		00			01	  FF    已开门
	*						FF		00			02  	FF    已关门
	*						FF		00			03	  FF    超时，锁门

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
