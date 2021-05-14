#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

/****************** LED GPIO端口定义(PD1) *****************/

#define LED_GPIO_PIN		GPIO_Pin_1            //引脚号
#define LED_GPIO_PORT		GPIOD					   //端口号
#define LED_GPIO_CLK		RCC_APB2Periph_GPIOD   //端口时钟

/****************** LED 开关定义 *****************/

#define digitalHi(p,i)		{p->BSRR=i;}
#define digitalLo(p,i)		{p->BRR=i;}
#define digitalToggle(p,i)		{p->ODR ^=i;}

#define LED_GPIO_ON			digitalHi(LED_GPIO_PORT,LED_GPIO_PIN) //高电平
#define LED_GPIO_OFF			digitalLo(LED_GPIO_PORT,LED_GPIO_PIN) //低电平
#define LED_GPIO_Toggle  digitalToggle(LED_GPIO_PORT,LED_GPIO_PIN)

void LED_GPIO_Config(void);
#endif /*__LED_H */

