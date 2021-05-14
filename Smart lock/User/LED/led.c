#include "led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//�����˿�����ʱ�� ��ѡ������˿ڣ�ENABLE/DISABLE��
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE); 
	
	//ѡ��Ҫ���Ƶ�����
	GPIO_InitStruct.GPIO_Pin = LED_GPIO_PIN;
	//��������ģʽΪ�������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//������������Ϊ50MHz
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//���ÿ⺯������ʼ��GPIO
	GPIO_Init(LED_GPIO_PORT,&GPIO_InitStruct);
	
	GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);	
}

