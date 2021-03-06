/**********************************************************************************
 * 文件名  ：usart.c
 * 描述    ：usart1 应用函数库          
 * 实验平台：NiRen_TwoHeart系统板
 * 硬件连接：TXD(PB9)  -> 外部串口RXD     
 *           RXD(PB10) -> 外部串口TXD      
 *           GND	   -> 外部串口GND 
 * 库版本  ：ST_v3.5
**********************************************************************************/
#include <string.h>
#include <stdio.h>
#include "all.h"	

#include "usart.h"	  
	
vu8 Usart1_R_Buff[USART1_REC_MAXLEN];	//串口1数据接收缓冲区 
vu8 Usart1_R_State=0;					//串口1接收状态
vu16 Usart1_R_Count=0;					//当前接收数据的字节数 	  

vu8 Usart3_R_Buff[USART3_REC_MAXLEN];	//串口1数据接收缓冲区 
vu8 Usart3_R_State=0;					//串口1接收状态
vu16 Usart3_R_Count=0;					//当前接收数据的字节数 	  


vu8 Usart5_R_Buff[USART5_REC_MAXLEN];	//串口1数据接收缓冲区 
vu8 Usart5_R_State=0;					//串口1接收状态
vu16 Usart5_R_Count=0;					//当前接收数据的字节数 	  

/*******************************************************************************
* 函数名  : USART1_Init_Config
* 描述    : USART1初始化配置
* 输入    : bound：波特率(常用：2400、4800、9600、19200、38400、115200等)
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void USART1_Init_Config(u32 bound)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	/*使能USART1和GPIOA外设时钟*/  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	

	/*复位串口1*/
 	USART_DeInit(USART1);  
	
	/*USART1_GPIO初始化设置*/ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			//USART1_TXD(PA.9)     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//设置引脚输出最大速率为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);				//调用库函数中的GPIO初始化函数，初始化USART1_TXD(PA.9)  
   
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				//USART1_RXD(PA.10)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);					//调用库函数中的GPIO初始化函数，初始化USART1_RXD(PA.10)


   /*USART1 初始化设置*/
	USART_InitStructure.USART_BaudRate = bound;										//设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;								//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//工作模式设置为收发模式
    USART_Init(USART1, &USART_InitStructure);										//初始化串口1

   /*Usart1 NVIC配置*/
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;	//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//从优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);							//根据指定的参数初始化VIC寄存器 
	  
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			//使能串口1接收中断

    USART_Cmd(USART1, ENABLE);                    			//使能串口 
	USART_ClearFlag(USART1, USART_FLAG_TC);					//清除发送完成标志
}


/*******************************************************************************
* 函数名  : UART1_SendString
* 描述    : USART1发送字符串
* 输入    : *s字符串指针
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void UART1_SendString(char* s)
{
	while(*s)//检测字符串结束符
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
		USART_SendData(USART1 ,*s++);//发送当前字符
	}
}


/*******************************************************************************
* 函数名  : UART1_SendData
* 描述    : USART1发送字符串
* 输入    : *s字符串指针
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void UART1_SendData(u8* s, u32 len)
{
	while(len --)//检测字符串结束符
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
		USART_SendData(USART1 ,*s++);//发送当前字符
	}
}


/*******************************************************************************
* 函数名  : UART1_SendByte
* 描述    : USART1发送字符串
* 输入    : *s字符串指针
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void UART1_SendByte(char s)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
	USART_SendData(USART1 ,s);//发送当前字符
}


//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
}  

#endif 

/*****************************************************
*function:	写字符文件函数
*param1:	输出的字符
*param2:	文件指针
*return:	输出字符的ASCII码
******************************************************/
int fputc(int ch, FILE *f)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
	USART_SendData(USART1 ,ch);//发送当前字符
	return ch;
}


vu32 __delay_uart_1 = 0;
vu8 _uart_1_data_flg = 0;

vu32 __delay_uart_3 = 0;
vu8 _uart_3_data_flg = 0;

vu32 __delay_uart_5 = 0;
vu8 _uart_5_data_flg = 0;

/*******************************************************************************
* 函数名  : USART1_IRQHandler
* 描述    : 串口1中断服务程序
* 输入    : 无
* 返回    : 无 
* 说明    : 1)、只启动了USART1中断接收，未启动USART1中断发送。
*           2)、接收到0x0d 0x0a(回车、"\r\n")代表帧数据接收完成
*******************************************************************************/
void USART1_IRQHandler(void)                	
{
	if (USART_GetFlagStatus(USART1, USART_FLAG_PE) != RESET)
	{
		USART_ReceiveData(USART1);
		USART_ClearFlag(USART1, USART_FLAG_PE);
	}
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
	{
		USART_ReceiveData(USART1);
		USART_ClearFlag(USART1, USART_FLAG_ORE);
	}
	if (USART_GetFlagStatus(USART1, USART_FLAG_FE) != RESET)
	{
		USART_ReceiveData(USART1);
		USART_ClearFlag(USART1, USART_FLAG_FE);
	}
    
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {   
			
		u8 Res=0;
		Res =USART_ReceiveData(USART1);
		Usart1_R_Buff[Usart1_R_Count] = Res;  	  //将接收到的字符串存到缓存中
		Usart1_R_Count++;                			//缓存指针向后移动
		if(Usart1_R_Count > USART1_REC_MAXLEN)       		//如果缓存满,将缓存指针指向缓存的首地址
		{
			Usart1_R_Count = 0;
		}

		__delay_uart_1 = 50;
		_uart_1_data_flg = 1;
        USART_ClearFlag(USART1, USART_FLAG_RXNE);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        
    }

} 	


u16 process_uart_1_data(void)
{
	if(__delay_uart_1 > 0)
	{

		return 0;
	}
	else
	{
		//printf("recv data \r\n");
		if(_uart_1_data_flg)
		{
			_uart_1_data_flg = 0;

			command_format(Usart1_R_Buff);

			memset(Usart1_R_Buff, 0, sizeof(Usart1_R_Buff));
			Usart1_R_Count = 0;
			printf("qdy # ");
		}
	}
}





/*******************************************************************************
* 函数名  : USART1_Init_Config
* 描述    : USART1初始化配置
* 输入    : bound：波特率(常用：2400、4800、9600、19200、38400、115200等)
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void USART2_Init_Config(u32 bound)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	/*使能USART2外设时钟*/  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	/*复位串口2*/
 	USART_DeInit(USART2);  
	
	/*USART2_GPIO初始化设置*/ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			//USART2_TXD(PA.2)     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//设置引脚输出最大速率为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);				//调用库函数中的GPIO初始化函数，初始化USART1_TXD(PA.9)  
   
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				//USART2_RXD(PA.3)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);					//调用库函数中的GPIO初始化函数，初始化USART1_RXD(PA.10)


   /*USART2 初始化设置*/
	USART_InitStructure.USART_BaudRate = bound;										//设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;								//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//工作模式设置为收发模式
  USART_Init(USART2, &USART_InitStructure);										//初始化串口2

   /*Usart1 NVIC配置*/
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//从优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);							//根据指定的参数初始化VIC寄存器 
	  
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);			//使能串口2接收中断

  USART_Cmd(USART2, ENABLE);                    			//使能串口 
	USART_ClearFlag(USART2, USART_FLAG_TC);					//清除发送完成标志
}
/*******************************************************************************
* 函数名  : UART2_SendString
* 描述    : USART2发送字符串
* 输入    : *s字符串指针
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void UART2_SendString(char* s)
{
	while(*s)//检测字符串结束符
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET); 
		USART_SendData(USART2 ,*s++);//发送当前字符
	}
}

/*******************************************************************************
* 函数名  : USART1_Init_Config
* 描述    : USART1初始化配置
* 输入    : bound：波特率(常用：2400、4800、9600、19200、38400、115200等)
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void USART3_Init_Config(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;						 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;			   
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3,&USART_InitStructure);				   
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		
	NVIC_Init(&NVIC_InitStructure); 						
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);			 
	USART_Cmd(USART3,ENABLE);
}



int (*process_uart3)(unsigned char *buf, int len);

/*******************************************************************************
* 函数名  : USART1_IRQHandler
* 描述    : 串口1中断服务程序
* 输入    : 无
* 返回    : 无 
* 说明    : 1)、只启动了USART1中断接收，未启动USART1中断发送。
*           2)、接收到0x0d 0x0a(回车、"\r\n")代表帧数据接收完成
*******************************************************************************/
void USART3_IRQHandler(void)                	
{
	if (USART_GetFlagStatus(USART3, USART_FLAG_PE) != RESET)
	{
		USART_ReceiveData(USART3);
		USART_ClearFlag(USART3, USART_FLAG_PE);
	}
	if (USART_GetFlagStatus(USART3, USART_FLAG_ORE) != RESET)
	{
		USART_ReceiveData(USART3);
		USART_ClearFlag(USART3, USART_FLAG_ORE);
	}
	if (USART_GetFlagStatus(USART3, USART_FLAG_FE) != RESET)
	{
		USART_ReceiveData(USART3);
		USART_ClearFlag(USART3, USART_FLAG_FE);
	}
    
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {   
			
		u8 Res=0;
		Res =USART_ReceiveData(USART3);
		Usart3_R_Buff[Usart3_R_Count] = Res;  	  //将接收到的字符串存到缓存中
		Usart3_R_Count++;                			//缓存指针向后移动
		if(Usart3_R_Count > USART3_REC_MAXLEN)       		//如果缓存满,将缓存指针指向缓存的首地址
		{
			Usart3_R_Count = 0;
		}

		__delay_uart_3 = 100;
		_uart_3_data_flg = 1;
        USART_ClearFlag(USART3, USART_FLAG_RXNE);
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
        
    }

} 	


u16 process_uart_3_data(void)
{
	if(__delay_uart_3 > 0)
	{

		return 0;
	}
	else
	{
		//printf("recv data \r\n");
		if(_uart_3_data_flg)
		{
			_uart_3_data_flg = 0;

			memset(Usart3_R_Buff, 0, sizeof(Usart3_R_Buff));
			Usart3_R_Count = 0;
		}
	}
}


void set_uart3_callback(int (*proocess)(unsigned char *buf, int len))
{
	process_uart3 = proocess;
}

u8 __timer_uart3_flg = 0;


int __timer_uart3_process(void * pdata)
{
	__timer_uart3_flg = 0;
}

vu32 delay3_cont = 0;

u16 recv_uart_3_data(u8* buf, u32 len, u32 delay_time)
{
	u32 ret = 0;
	
	//add_irq_timer(TIMER_LIST_ONCE, delay_time, __timer_uart3_process, NULL);

	__timer_uart3_flg = 1;
	delay3_cont = delay_time;
	
	while(__timer_uart3_flg)
	{
		
		if(delay3_cont == 0)
			return 0;
		
		if((_uart_3_data_flg) && (__delay_uart_3 == 0))
		{
			_uart_3_data_flg = 0;

			ret = min(Usart3_R_Count, len);
			memcpy(buf, (void *)Usart3_R_Buff, min(Usart3_R_Count, len));

			memset(Usart3_R_Buff, 0, sizeof(Usart3_R_Buff));
			Usart3_R_Count = 0;

			return ret;
		}
	}
	_uart_3_data_flg = 0;
	return 0;
}

/*******************************************************************************
* 函数名  : UART1_SendData
* 描述    : USART1发送字符串
* 输入    : *s字符串指针
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void UART3_SendData(u8* s, u32 len)
{
	while(len --)//检测字符串结束符
	{
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); 
		USART_SendData(USART3 ,*s++);//发送当前字符
	}
}


/*******************************************************************************
* 函数名  : UART1_SendByte
* 描述    : USART1发送字符串
* 输入    : *s字符串指针
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void UART3_SendByte(char s)
{
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); 
	USART_SendData(USART3 ,s);//发送当前字符
}




int (*process_uart5)(unsigned char *buf, int len);

/*******************************************************************************
* 函数名  : USART1_Init_Config
* 描述    : USART1初始化配置
* 输入    : bound：波特率(常用：2400、4800、9600、19200、38400、115200等)
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void USART5_Init_Config(u32 bound)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//使能UART5，GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	//使能GPIOC/D时钟
	USART_DeInit(UART5);  //复位串口5
	//USART5_TX   PC12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化PC12
	//USART5_RX   PD2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);	//初始化PB11
 
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
 
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
	USART_Init(UART5, &USART_InitStructure); //初始化串口
 
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(UART5, ENABLE);					 //使能串口

	
	USART_ClearFlag(USART2, USART_FLAG_TC);					//清除发送完成标志
}


/*******************************************************************************
* 函数名  : USART1_IRQHandler
* 描述    : 串口1中断服务程序
* 输入    : 无
* 返回    : 无 
* 说明    : 1)、只启动了USART1中断接收，未启动USART1中断发送。
*           2)、接收到0x0d 0x0a(回车、"\r\n")代表帧数据接收完成
*******************************************************************************/
	
void UART5_IRQHandler(void)              	
{
	if (USART_GetFlagStatus(UART5, USART_FLAG_PE) != RESET)
	{
		USART_ReceiveData(UART5);
		USART_ClearFlag(UART5, USART_FLAG_PE);
	}
	if (USART_GetFlagStatus(UART5, USART_FLAG_ORE) != RESET)
	{
		USART_ReceiveData(UART5);
		USART_ClearFlag(UART5, USART_FLAG_ORE);
	}
	if (USART_GetFlagStatus(UART5, USART_FLAG_FE) != RESET)
	{
		USART_ReceiveData(UART5);
		USART_ClearFlag(UART5, USART_FLAG_FE);
	}
    
    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
    {   
			
		u8 Res=0;
		Res =USART_ReceiveData(UART5);
		Usart5_R_Buff[Usart5_R_Count] = Res;  	  //将接收到的字符串存到缓存中
		Usart5_R_Count++;                			//缓存指针向后移动
		if(Usart5_R_Count > USART5_REC_MAXLEN)       		//如果缓存满,将缓存指针指向缓存的首地址
		{
			Usart5_R_Count = 0;
		}

		__delay_uart_5 = 50;
		_uart_5_data_flg = 1;
        USART_ClearFlag(UART5, USART_FLAG_RXNE);
        USART_ClearITPendingBit(UART5, USART_IT_RXNE);
        
    }

} 	


void set_uart5_callback(int (*proocess)(unsigned char *buf, int len))
{
	process_uart5 = proocess;
}

u8 __timer_uart5_flg = 0;
u8 __timer_uart5_delay = 0;

u16 process_uart_5_data(void)
{
	if(__delay_uart_5 > 0)
	{

		return 0;
	}
	else
	{
		//printf("recv data \r\n");
		if(_uart_5_data_flg)
		{
			_uart_5_data_flg = 0;

			if(process_uart5 != NULL)
			{
				process_uart5(Usart5_R_Buff, Usart5_R_Count);
			}

			memset(Usart5_R_Buff, 0, sizeof(Usart5_R_Buff));
			Usart5_R_Count = 0;
		}
	}
}




int __timer_uart5_process(void * pdata)
{
	__timer_uart5_flg = 0;
}

void clear_uart5_data(void)
{
	memset(Usart5_R_Buff, 0, sizeof(Usart5_R_Buff));
	Usart5_R_Count = 0;
}

vu32 delay5_cont = 0;

u16 recv_uart_5_data(u8* buf, u32 len, u32 delay_time)
{
	u32 ret = 0;

	
	//struct timer * t = add_irq_timer(TIMER_LIST_ONCE, delay_time, __timer_uart5_process, NULL);

	__timer_uart5_flg = 1;
	delay5_cont = delay_time;

	while(1)
	{
		if(delay5_cont == 0)
		{
			return 0;
		}
			
		if((_uart_5_data_flg) && (__delay_uart_5 == 0))
		{
			_uart_5_data_flg = 0;

			ret = min(Usart5_R_Count, len);
			memcpy(buf, (void *)Usart5_R_Buff, min(Usart5_R_Count, len));

			memset(Usart5_R_Buff, 0, sizeof(Usart5_R_Buff));
			Usart5_R_Count = 0;

			__timer_uart5_flg = 0;
			return ret;
		}
	}
	_uart_5_data_flg = 0;
	return 0;
}


/*******************************************************************************
* 函数名  : UART2_SendString
* 描述    : USART2发送字符串
* 输入    : *s字符串指针
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void UART5_SendString(char* s)
{
	while(*s)//检测字符串结束符
	{
		while(USART_GetFlagStatus(UART5, USART_FLAG_TC)==RESET); 
		USART_SendData(UART5 ,*s++);//发送当前字符
	}
}

void UART5_SendByte(char s)
{
	while(USART_GetFlagStatus(UART5, USART_FLAG_TC)==RESET); 
	USART_SendData(UART5 ,s);//发送当前字符
}


