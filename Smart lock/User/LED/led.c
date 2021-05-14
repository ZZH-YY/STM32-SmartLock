#include "led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//开启端口外设时钟 （选择外设端口，ENABLE/DISABLE）
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE); 
	
	//选择要控制的引脚
	GPIO_InitStruct.GPIO_Pin = LED_GPIO_PIN;
	//设置引脚模式为推挽输出
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//设置引脚速率为50MHz
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//调用库函数，初始化GPIO
	GPIO_Init(LED_GPIO_PORT,&GPIO_InitStruct);
	
	GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);	
}

