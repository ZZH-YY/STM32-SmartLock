/**
  ******************************************************************************
  * @file    main.c
  * @author  ZZH/KYF
  * @version V3.0
  * @date    2021-05-14
  * @brief   ���´���2�������ݰ�
  ******************************************************************************
	*
	*1.��������ͨѶЭ�飺
	*    	����		 ��ͷ  ����λ	����λ ����λ	��β
	*			ֹͣ			FF		00			00	  00	   FF
	*			ǰ��			FF		00			01	  00	   FF
	*			����			FF		00			02  	00     FF
	*			��ת			FF		00			03	  00	   FF
	*			��ת			FF		00			04	  00	   FF
	* 		��ǰת		FF		00			05	  00	   FF
	*			���ת		FF		00			06	  00	   FF
	*			��ǰת		FF		00			07	  00	   FF
	*			�Һ�ת		FF		00			08	  00	   FF
	*      ����	    FF	  05	    00	  00	   FF
	*      �ص�	    FF	  05	    01	  00	   FF
	*      ������n   FF    01      0n    00     FF	(n=0-15)
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

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

int main(void)
{	
	//ADC��������ʼ��
	ADCx_Init();
	
	//���ڳ�ʼ��
	USART_Config();
	USART2_Config();
	
	//LOCK GPIO��ʼ��
	LOCK_GPIO_Config();
	
	//LED GOIO��ʼ��
	LED_GPIO_Config();
	
	//��ʼ��Systick
	SysTick_Init();

	while(1)
	{
		//���ƺ���
		Communication_Decode();
	}
}
