/**
  ******************************************************************************
  * @file    usart2.c
  * @author  Hua
  * @version V6.0
  * @date    2021-05-04
  * @brief   usart2初始化
  ******************************************************************************
  * @attention
  *		功能：向舵机控制板发送数据
  ******************************************************************************
**/ 
	
#include "usart2.h"

 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	DEBUG_USART2_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART2_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USART2x, &USART_InitStructure);
	// 使能串口
	USART_Cmd(DEBUG_USART2x, ENABLE);	    
}


///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USART2x, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USART2x, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USART2x, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART2x);
}


///*
//*********************************************************************************************************
//*                                          串口2 数据包发送函数
//*********************************************************************************************************
//*/

//void UART_DM_ReportData(unsigned char data[]) //数据包发送
//{		
//	unsigned char i = 0;
//	for (i=0;i<4;i++) 
//	Usart2_SendByte(*(data + i));	
//}

////发送一个字节
//void Usart2_SendByte(uint8_t ch)
//{
//	/* 发送一个字节数据到USART */
//	USART_SendData(USART2,ch);
//		
//	/* 等待发送数据寄存器为空 */
//	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	
//}