#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

/****************** LED GPIO�˿ڶ���(PD1) *****************/

#define LED_GPIO_PIN		GPIO_Pin_1            //���ź�
#define LED_GPIO_PORT		GPIOD					   //�˿ں�
#define LED_GPIO_CLK		RCC_APB2Periph_GPIOD   //�˿�ʱ��

/****************** LED ���ض��� *****************/

#define digitalHi(p,i)		{p->BSRR=i;}
#define digitalLo(p,i)		{p->BRR=i;}
#define digitalToggle(p,i)		{p->ODR ^=i;}

#define LED_GPIO_ON			digitalHi(LED_GPIO_PORT,LED_GPIO_PIN) //�ߵ�ƽ
#define LED_GPIO_OFF			digitalLo(LED_GPIO_PORT,LED_GPIO_PIN) //�͵�ƽ
#define LED_GPIO_Toggle  digitalToggle(LED_GPIO_PORT,LED_GPIO_PIN)

void LED_GPIO_Config(void);
#endif /*__LED_H */

