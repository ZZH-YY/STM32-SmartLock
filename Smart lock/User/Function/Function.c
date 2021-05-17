#include "lock.h"
#include "led.h"
#include "usart.h"
#include "usart2.h"
#include "bsp_adc.h"
#include "Function.h"
#include "SysTick.h"
extern uint8_t buffer[3];  //定义串口缓冲接收数组
extern uint8_t rec_flag;   //定义串口接收标志 1-正在接收 
extern int Communication_Decode_flag; //接收完成标志位置 1-接受结束
extern __IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal; 

int ADC_flag; //开门状态标志位（0-未开门 1-已开门）


/*
*********************************************************************************************************
*                                               状态反馈数据包
*********************************************************************************************************
*/
unsigned char Status_0[4]   = { 0xff, 0x00, 0x00, 0xff };               //已开锁
unsigned char Status_1[4]   = { 0xff, 0x00, 0x01, 0xff };               //已开门
unsigned char Status_2[4]   = { 0xff, 0x00, 0x02, 0xff };               //已关门
unsigned char Status_3[4]   = { 0xff, 0x00, 0x03, 0xff };               //超时未开门，门关闭


void Communication_Decode(void)
{
	if(Communication_Decode_flag)
	 {
			Communication_Decode_flag=0;
				switch(buffer[0])
        {
					case 0x01:
						LOCK_Open;      //开门
						UART_DM_ReportData(Status_0);//向串口2发送“已开锁”数据
					  LED_GPIO_ON;    //开灯
						ADC_flag=0;     //标志：未开门
						Door_ADC_Control(); //门控函数
						return;
				}
		}
}




/*
*********************************************************************************************************
*                                          ADC转换函数
*********************************************************************************************************
*/
void ADC_Local(void)
{
	ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值
}
/*
*********************************************************************************************************
*                                          ADC检测 门控函数
*********************************************************************************************************
*/
uint8_t i;
uint8_t num;
void Door_ADC_Control(void)
{	
	ADC_Local();//获取电压
	if(ADC_ConvertedValueLocal > 3 )
	{
		printf("正在等待开门(%.2f V)\r\n",ADC_ConvertedValueLocal);
		for(i=1;i<=100;i++)
		{ 
			num = i;
			ADC_Local();//获取电压 
			if(ADC_ConvertedValueLocal <= 3)
			{
				ADC_flag = 1; //已开门，标志位置1
				UART_DM_ReportData(Status_1);//向串口2发送“已开门”数据
				LOCK_Close;   //关门
				printf("已经开门(%.2f V)\r\n",ADC_ConvertedValueLocal);	
				break;
			}
			else
			{
				Delay_ms(100); //延时.01s
			}	
		}
		
		if(num==100)
		{ 
			LOCK_Close;
			UART_DM_ReportData(Status_3);//向串口2发送“超时未开门，门关闭”数据
			printf("开门超时已关门(%.2f V)\r\n",ADC_ConvertedValueLocal);
			Led_ADC_Close();
		}
	}
	
	
	if(ADC_ConvertedValueLocal < 3 && ADC_flag==1)
	{
		while(1)
		{
		  ADC_Local();
			if(ADC_ConvertedValueLocal >= 3 && ADC_flag==1)
			{	 
				Delay_ms(100);
				ADC_Local();
				if(ADC_ConvertedValueLocal >= 3 && ADC_flag==1)
				{ 
					UART_DM_ReportData(Status_2);//向串口2发送“超时未开门，已关门”数据
					printf("已经关门(%.2f V)\r\n",ADC_ConvertedValueLocal);
					Led_ADC_Close();
					break;
				}
			}
		}
	
	}	
  
}



/*
*********************************************************************************************************
*                                                LED关函数
*********************************************************************************************************
*/

void Led_ADC_Close(void)
{ 
	if(ADC_ConvertedValueLocal > 3)
	{
		printf("开始关灯延时\n"); 
		Delay_ms(3000);
		LED_GPIO_OFF;
		printf("已经关灯\n"); 
	}
}




