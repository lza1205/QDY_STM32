#include "timer.h"

extern vu8 Timer0_start;
extern u8 shijian;
extern u8 Times;
/*******************************************************************************
* 函数名  : Timer2_Init_Config
* 描述    : Timer2初始化配置
* 输入    : 无
* 输出    : 无
* 返回    : 无 
* 说明    : 1s延时
*******************************************************************************/
void Timer2_Init_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		//使能Timer2时钟
	
	TIM_TimeBaseStructure.TIM_Period = 9999;					//设置在下一个更新事件装入活动的自动重装载寄存器周期的值(计数到10000为1s)
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;					//设置用来作为TIMx时钟频率除数的预分频值(10KHz的计数频率)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//设置时钟分割:TDTS = TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);				//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	/*中断优先级NVIC设置*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;				//TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//从优先级1级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能IRQ通道
	NVIC_Init(&NVIC_InitStructure); 							//初始化NVIC寄存器
	 
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE ); 				//使能TIM2指定的中断
	
	TIM_Cmd(TIM2, ENABLE);  									//使能TIMx外设
}	 


/*******************************************************************************
* 函数名  : TIM2_IRQHandler
* 描述    : 定时器2中断断服务函数
* 输入    : 无
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void TIM2_IRQHandler(void)   //TIM3中断
{
	static u8 flag =1;

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
	}	
}


/*******************************************************************************
* 函数名  : Timer2_Init_Config
* 描述    : Timer2初始化配置
* 输入    : 无
* 输出    : 无
* 返回    : 无 
* 说明    : 1s延时
*******************************************************************************/
void Timer3_Init_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		//使能Timer3时钟
	
	TIM_TimeBaseStructure.TIM_Period = 9;					//设置在下一个更新事件装入活动的自动重装载寄存器周期的值(计数到10000为1s)
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;					//设置用来作为TIMx时钟频率除数的预分频值(10KHz的计数频率)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//设置时钟分割:TDTS = TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);				//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	/*中断优先级NVIC设置*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;				//TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//从优先级1级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能IRQ通道
	NVIC_Init(&NVIC_InitStructure); 							//初始化NVIC寄存器
	 
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE ); 				//使能TIM2指定的中断
	
	TIM_Cmd(TIM3, ENABLE);  									//使能TIMx外设
}	 




vu32 __timer3_cnt = 0;


extern  vu32 __delay_uart;
extern  vu32 uart3_delay_time;

extern vu32 __delay_uart_1;
extern vu8 _uart_1_data_flg;

extern vu32 __delay_uart_5;
extern vu8 _uart_5_data_flg;

extern vu32 __delay_uart_3;
extern vu8 _uart_3_data_flg;

extern vu32 delay3_cont ;
extern vu32 delay5_cont ;


/*******************************************************************************
* 函数名  : TIM3_IRQHandler
* 描述    : 定时器2中断断服务函数
* 输入    : 无
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void TIM3_IRQHandler(void)   //TIM3中断
{

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 

		if(__delay_uart > 0)
		{
			__delay_uart -- ;
		}

		if(__delay_uart_1> 0)
		{
			__delay_uart_1 -- ;
		}

		if(__delay_uart_3 > 0)
		{
			__delay_uart_3 -- ;
		}

		if(__delay_uart_5> 0)
		{
			__delay_uart_5 -- ;
		}


		if(delay5_cont > 0)
		{
			delay5_cont --;
		}

		if(delay3_cont > 0)
		{
			delay3_cont --;
		}

		__timer3_cnt ++;

		//process_irq_timer_list();
	}	
}




