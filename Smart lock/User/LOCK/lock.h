#ifndef __LOCK_H
#define __LOCK_H

#include "stm32f10x.h"


/****************** LOCK GPIO�˿ڶ���   *****************/

#define LOCK_GPIO_PIN		GPIO_Pin_5             
#define LOCK_GPIO_PORT	GPIOC					   
#define LOCK_GPIO_CLK		RCC_APB2Periph_GPIOC   //�˿�ʱ��

/****************** LOCK ���ض��� *****************/

#define digitalHi(p,i)		{p->BSRR=i;}
#define digitalLo(p,i)		{p->BRR=i;}
#define digitalToggle(p,i)		{p->ODR ^=i;}

#define LOCK_Close			digitalHi(LOCK_GPIO_PORT,LOCK_GPIO_PIN) //�ߵ�ƽ
#define LOCK_Open			digitalLo(LOCK_GPIO_PORT,LOCK_GPIO_PIN) //�͵�ƽ

void LOCK_GPIO_Config(void);
#endif /* __LOCK_H */

