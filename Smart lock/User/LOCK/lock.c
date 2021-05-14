#include "lock.h"


void LOCK_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//�����˿�����ʱ�� ��ѡ������˿ڣ�ENABLE/DISABLE��
	RCC_APB2PeriphClockCmd(LOCK_GPIO_CLK, ENABLE); 
	
	//ѡ��Ҫ���Ƶ�����
	GPIO_InitStruct.GPIO_Pin = LOCK_GPIO_PIN;// �̵�
	//��������ģʽΪ�������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//������������Ϊ50MHz
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//���ÿ⺯������ʼ��GPIO
	GPIO_Init(LOCK_GPIO_PORT,&GPIO_InitStruct);
	
	GPIO_SetBits(LOCK_GPIO_PORT, LOCK_GPIO_PIN);	
}
