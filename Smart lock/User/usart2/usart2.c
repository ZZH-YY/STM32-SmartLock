/**
  ******************************************************************************
  * @file    usart2.c
  * @author  Hua
  * @version V6.0
  * @date    2021-05-04
  * @brief   usart2��ʼ��
  ******************************************************************************
  * @attention
  *		���ܣ��������ư巢������
  ******************************************************************************
**/ 
	
#include "usart2.h"

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART2_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART2_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USART2x, &USART_InitStructure);
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USART2x, ENABLE);	    
}


///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USART2x, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USART2x, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USART2x, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART2x);
}


///*
//*********************************************************************************************************
//*                                          ����2 ���ݰ����ͺ���
//*********************************************************************************************************
//*/

//void UART_DM_ReportData(unsigned char data[]) //���ݰ�����
//{		
//	unsigned char i = 0;
//	for (i=0;i<4;i++) 
//	Usart2_SendByte(*(data + i));	
//}

////����һ���ֽ�
//void Usart2_SendByte(uint8_t ch)
//{
//	/* ����һ���ֽ����ݵ�USART */
//	USART_SendData(USART2,ch);
//		
//	/* �ȴ��������ݼĴ���Ϊ�� */
//	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	
//}