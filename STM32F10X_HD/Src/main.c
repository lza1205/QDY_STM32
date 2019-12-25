/**********************************************************************************
 * ������  :GPRS
 * ����    :lza1205
 * ����    :https://blog.csdn.net/aa120515692
**********************************************************************************/

#include "stm32f10x.h"
#include "usart.h"
#include "SysTick.h"
#include "timer.h"
#include "string.h"


#include "gsm_code.h"
#include "gsm_base.h"
#include "tcp_base.h"

#include "all.h"


/*******************************************************************************
* ������ : main 
* ����   : ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : ����2������MG323ģ��ͨ�ţ�����1���ڴ��ڵ��ԣ����Ա��������س���ʱ����
					 �����͵�ģ��
*******************************************************************************/
int main(void)
{
	SysTick_Init_Config();

	USART1_Init_Config(115200);
	USART2_Init_Config(115200);
	Timer2_Init_Config();
	
	UART1_SendString("GPRSģ��GPRS���Գ���\r\n");
	UART1_SendString("GPRSģ����ע������\r\n");
	Wait_CREG();
	UART1_SendString("GPRSģ��ע��ɹ�\r\n");
	UART1_SendString("GPRSģ�鿪ʼ���ӷ�����\r\n");
	Set_ATE0();

	Connect_Server(NULL);
	UART1_SendString("GPRSģ�����ӷ����� �ɹ�\r\n");
	while(1)
	{
		#if 0
		LED1_ON();
		Delay_nMs(2000);
		LED1_OFF();
		Delay_nMs(2000);
		#else
		//loop_3a_machine();
		client_main();
		#endif

		/*
		Rec_Server_Data();
		
		tcp_heart_beat();
		*/
	}
}

