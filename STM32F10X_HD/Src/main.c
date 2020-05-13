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



#include "all.h"


/*******************************************************************************
* ������ : main 
* ����   : ������
* ����   : 
* ���   : 
* ����   : 
*******************************************************************************/
int main(void)
{
	SysTick_Init_Config();
	gpio_bsp_init();
	USART1_Init_Config(115200);
	USART2_Init_Config(115200);
	USART3_Init_Config(9600);
	USART5_Init_Config(9600);
	Timer2_Init_Config();
	Timer3_Init_Config();
	RTC_Init();

	qdy_system_init();


	//���ﲻ��
	#if  EXAMPLE_DEMO == EXAMPLE_QDY
		qd_cloud_main();
	#endif

	//��������Ҫ����ں���
	#if  EXAMPLE_DEMO == EXAMPLE_RS485_LCD
		rs485_lcd_main();
	#endif

	while(1)
	{
		
		
	}
}

