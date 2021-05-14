#ifndef __LOCK_H
#define __LOCK_H

#include "stm32f10x.h"


/****************** LOCK GPIO端口定义   *****************/

#define LOCK_GPIO_PIN		GPIO_Pin_5             
#define LOCK_GPIO_PORT	GPIOC					   
#define LOCK_GPIO_CLK		RCC_APB2Periph_GPIOC   //端口时钟

/****************** LOCK 开关定义 *****************/

#define digitalHi(p,i)		{p->BSRR=i;}
#define digitalLo(p,i)		{p->BRR=i;}
#define digitalToggle(p,i)		{p->ODR ^=i;}

#define LOCK_Close			digitalHi(LOCK_GPIO_PORT,LOCK_GPIO_PIN) //高电平
#define LOCK_Open			digitalLo(LOCK_GPIO_PORT,LOCK_GPIO_PIN) //低电平

void LOCK_GPIO_Config(void);
#endif /* __LOCK_H */

