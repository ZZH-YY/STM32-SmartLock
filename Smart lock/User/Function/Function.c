#include "lock.h"
#include "led.h"
#include "usart.h"
#include "usart2.h"
#include "bsp_adc.h"
#include "Function.h"
#include "SysTick.h"
extern uint8_t buffer[3];  //���崮�ڻ����������
extern uint8_t rec_flag;   //���崮�ڽ��ձ�־ 1-���ڽ��� 
extern int Communication_Decode_flag; //������ɱ�־λ�� 1-���ܽ���
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal; 

int ADC_flag; //����״̬��־λ��0-δ���� 1-�ѿ��ţ�


/*
*********************************************************************************************************
*                                               ״̬�������ݰ�
*********************************************************************************************************
*/
unsigned char Status_0[4]   = { 0xff, 0x00, 0x00, 0xff };               //�ѿ���
unsigned char Status_1[4]   = { 0xff, 0x00, 0x01, 0xff };               //�ѿ���
unsigned char Status_2[4]   = { 0xff, 0x00, 0x02, 0xff };               //�ѹ���
unsigned char Status_3[4]   = { 0xff, 0x00, 0x03, 0xff };               //��ʱδ���ţ��Źر�


void Communication_Decode(void)
{
	if(Communication_Decode_flag)
	 {
			Communication_Decode_flag=0;
				switch(buffer[0])
        {
					case 0x01:
						LOCK_Open;      //����
						UART_DM_ReportData(Status_0);//�򴮿�2���͡��ѿ���������
					  LED_GPIO_ON;    //����
						ADC_flag=0;     //��־��δ����
						Door_ADC_Control(); //�ſغ���
						return;
				}
		}
}




/*
*********************************************************************************************************
*                                          ADCת������
*********************************************************************************************************
*/
void ADC_Local(void)
{
	ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
}
/*
*********************************************************************************************************
*                                          ADC��� �ſغ���
*********************************************************************************************************
*/
uint8_t i;
uint8_t num;
void Door_ADC_Control(void)
{	
	ADC_Local();//��ȡ��ѹ
	if(ADC_ConvertedValueLocal > 3 )
	{
		printf("���ڵȴ�����(%.2f V)\r\n",ADC_ConvertedValueLocal);
		for(i=1;i<=100;i++)
		{ 
			num = i;
			ADC_Local();//��ȡ��ѹ 
			if(ADC_ConvertedValueLocal <= 3)
			{
				ADC_flag = 1; //�ѿ��ţ���־λ��1
				UART_DM_ReportData(Status_1);//�򴮿�2���͡��ѿ��š�����
				LOCK_Close;   //����
				printf("�Ѿ�����(%.2f V)\r\n",ADC_ConvertedValueLocal);	
				break;
			}
			else
			{
				Delay_ms(100); //��ʱ.01s
			}	
		}
		
		if(num==100)
		{ 
			LOCK_Close;
			UART_DM_ReportData(Status_3);//�򴮿�2���͡���ʱδ���ţ��Źرա�����
			printf("���ų�ʱ�ѹ���(%.2f V)\r\n",ADC_ConvertedValueLocal);
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
					UART_DM_ReportData(Status_2);//�򴮿�2���͡���ʱδ���ţ��ѹ��š�����
					printf("�Ѿ�����(%.2f V)\r\n",ADC_ConvertedValueLocal);
					Led_ADC_Close();
					break;
				}
			}
		}
	
	}	
  
}



/*
*********************************************************************************************************
*                                                LED�غ���
*********************************************************************************************************
*/

void Led_ADC_Close(void)
{ 
	if(ADC_ConvertedValueLocal > 3)
	{
		printf("��ʼ�ص���ʱ\n"); 
		Delay_ms(3000);
		LED_GPIO_OFF;
		printf("�Ѿ��ص�\n"); 
	}
}




