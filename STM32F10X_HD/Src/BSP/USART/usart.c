/**********************************************************************************
 * �ļ���  ��usart.c
 * ����    ��usart1 Ӧ�ú�����          
 * ʵ��ƽ̨��NiRen_TwoHeartϵͳ��
 * Ӳ�����ӣ�TXD(PB9)  -> �ⲿ����RXD     
 *           RXD(PB10) -> �ⲿ����TXD      
 *           GND	   -> �ⲿ����GND 
 * ��汾  ��ST_v3.5
**********************************************************************************/
#include <string.h>
#include <stdio.h>
#include "all.h"	

#include "usart.h"	  
	
vu8 Usart1_R_Buff[USART1_REC_MAXLEN];	//����1���ݽ��ջ����� 
vu8 Usart1_R_State=0;					//����1����״̬
vu16 Usart1_R_Count=0;					//��ǰ�������ݵ��ֽ��� 	  

vu8 Usart3_R_Buff[USART3_REC_MAXLEN];	//����1���ݽ��ջ����� 
vu8 Usart3_R_State=0;					//����1����״̬
vu16 Usart3_R_Count=0;					//��ǰ�������ݵ��ֽ��� 	  


vu8 Usart5_R_Buff[USART5_REC_MAXLEN];	//����1���ݽ��ջ����� 
vu8 Usart5_R_State=0;					//����1����״̬
vu16 Usart5_R_Count=0;					//��ǰ�������ݵ��ֽ��� 	  

/*******************************************************************************
* ������  : USART1_Init_Config
* ����    : USART1��ʼ������
* ����    : bound��������(���ã�2400��4800��9600��19200��38400��115200��)
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void USART1_Init_Config(u32 bound)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	/*ʹ��USART1��GPIOA����ʱ��*/  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	

	/*��λ����1*/
 	USART_DeInit(USART1);  
	
	/*USART1_GPIO��ʼ������*/ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			//USART1_TXD(PA.9)     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//������������������Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);				//���ÿ⺯���е�GPIO��ʼ����������ʼ��USART1_TXD(PA.9)  
   
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				//USART1_RXD(PA.10)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);					//���ÿ⺯���е�GPIO��ʼ����������ʼ��USART1_RXD(PA.10)


   /*USART1 ��ʼ������*/
	USART_InitStructure.USART_BaudRate = bound;										//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							//1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;								//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//����ģʽ����Ϊ�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure);										//��ʼ������1

   /*Usart1 NVIC����*/
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;	//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);							//����ָ���Ĳ�����ʼ��VIC�Ĵ��� 
	  
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			//ʹ�ܴ���1�����ж�

    USART_Cmd(USART1, ENABLE);                    			//ʹ�ܴ��� 
	USART_ClearFlag(USART1, USART_FLAG_TC);					//���������ɱ�־
}


/*******************************************************************************
* ������  : UART1_SendString
* ����    : USART1�����ַ���
* ����    : *s�ַ���ָ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void UART1_SendString(char* s)
{
	while(*s)//����ַ���������
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
		USART_SendData(USART1 ,*s++);//���͵�ǰ�ַ�
	}
}


/*******************************************************************************
* ������  : UART1_SendData
* ����    : USART1�����ַ���
* ����    : *s�ַ���ָ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void UART1_SendData(u8* s, u32 len)
{
	while(len --)//����ַ���������
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
		USART_SendData(USART1 ,*s++);//���͵�ǰ�ַ�
	}
}


/*******************************************************************************
* ������  : UART1_SendByte
* ����    : USART1�����ַ���
* ����    : *s�ַ���ָ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void UART1_SendByte(char s)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
	USART_SendData(USART1 ,s);//���͵�ǰ�ַ�
}


//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
}  

#endif 

/*****************************************************
*function:	д�ַ��ļ�����
*param1:	������ַ�
*param2:	�ļ�ָ��
*return:	����ַ���ASCII��
******************************************************/
int fputc(int ch, FILE *f)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
	USART_SendData(USART1 ,ch);//���͵�ǰ�ַ�
	return ch;
}


vu32 __delay_uart_1 = 0;
vu8 _uart_1_data_flg = 0;

vu32 __delay_uart_3 = 0;
vu8 _uart_3_data_flg = 0;

vu32 __delay_uart_5 = 0;
vu8 _uart_5_data_flg = 0;

/*******************************************************************************
* ������  : USART1_IRQHandler
* ����    : ����1�жϷ������
* ����    : ��
* ����    : �� 
* ˵��    : 1)��ֻ������USART1�жϽ��գ�δ����USART1�жϷ��͡�
*           2)�����յ�0x0d 0x0a(�س���"\r\n")����֡���ݽ������
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
		Usart1_R_Buff[Usart1_R_Count] = Res;  	  //�����յ����ַ����浽������
		Usart1_R_Count++;                			//����ָ������ƶ�
		if(Usart1_R_Count > USART1_REC_MAXLEN)       		//���������,������ָ��ָ�򻺴���׵�ַ
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
* ������  : USART1_Init_Config
* ����    : USART1��ʼ������
* ����    : bound��������(���ã�2400��4800��9600��19200��38400��115200��)
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void USART2_Init_Config(u32 bound)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	/*ʹ��USART2����ʱ��*/  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	/*��λ����2*/
 	USART_DeInit(USART2);  
	
	/*USART2_GPIO��ʼ������*/ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			//USART2_TXD(PA.2)     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//������������������Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);				//���ÿ⺯���е�GPIO��ʼ����������ʼ��USART1_TXD(PA.9)  
   
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				//USART2_RXD(PA.3)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);					//���ÿ⺯���е�GPIO��ʼ����������ʼ��USART1_RXD(PA.10)


   /*USART2 ��ʼ������*/
	USART_InitStructure.USART_BaudRate = bound;										//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							//1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;								//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//����ģʽ����Ϊ�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure);										//��ʼ������2

   /*Usart1 NVIC����*/
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);							//����ָ���Ĳ�����ʼ��VIC�Ĵ��� 
	  
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);			//ʹ�ܴ���2�����ж�

  USART_Cmd(USART2, ENABLE);                    			//ʹ�ܴ��� 
	USART_ClearFlag(USART2, USART_FLAG_TC);					//���������ɱ�־
}
/*******************************************************************************
* ������  : UART2_SendString
* ����    : USART2�����ַ���
* ����    : *s�ַ���ָ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void UART2_SendString(char* s)
{
	while(*s)//����ַ���������
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET); 
		USART_SendData(USART2 ,*s++);//���͵�ǰ�ַ�
	}
}

/*******************************************************************************
* ������  : USART1_Init_Config
* ����    : USART1��ʼ������
* ����    : bound��������(���ã�2400��4800��9600��19200��38400��115200��)
* ���    : ��
* ����    : �� 
* ˵��    : ��
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
* ������  : USART1_IRQHandler
* ����    : ����1�жϷ������
* ����    : ��
* ����    : �� 
* ˵��    : 1)��ֻ������USART1�жϽ��գ�δ����USART1�жϷ��͡�
*           2)�����յ�0x0d 0x0a(�س���"\r\n")����֡���ݽ������
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
		Usart3_R_Buff[Usart3_R_Count] = Res;  	  //�����յ����ַ����浽������
		Usart3_R_Count++;                			//����ָ������ƶ�
		if(Usart3_R_Count > USART3_REC_MAXLEN)       		//���������,������ָ��ָ�򻺴���׵�ַ
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
* ������  : UART1_SendData
* ����    : USART1�����ַ���
* ����    : *s�ַ���ָ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void UART3_SendData(u8* s, u32 len)
{
	while(len --)//����ַ���������
	{
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); 
		USART_SendData(USART3 ,*s++);//���͵�ǰ�ַ�
	}
}


/*******************************************************************************
* ������  : UART1_SendByte
* ����    : USART1�����ַ���
* ����    : *s�ַ���ָ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void UART3_SendByte(char s)
{
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); 
	USART_SendData(USART3 ,s);//���͵�ǰ�ַ�
}




int (*process_uart5)(unsigned char *buf, int len);

/*******************************************************************************
* ������  : USART1_Init_Config
* ����    : USART1��ʼ������
* ����    : bound��������(���ã�2400��4800��9600��19200��38400��115200��)
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void USART5_Init_Config(u32 bound)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//ʹ��UART5��GPIOBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	//ʹ��GPIOC/Dʱ��
	USART_DeInit(UART5);  //��λ����5
	//USART5_TX   PC12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��PC12
	//USART5_RX   PD2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_Init(GPIOD, &GPIO_InitStructure);	//��ʼ��PB11
 
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
 
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
	USART_Init(UART5, &USART_InitStructure); //��ʼ������
 
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(UART5, ENABLE);					 //ʹ�ܴ���

	
	USART_ClearFlag(USART2, USART_FLAG_TC);					//���������ɱ�־
}


/*******************************************************************************
* ������  : USART1_IRQHandler
* ����    : ����1�жϷ������
* ����    : ��
* ����    : �� 
* ˵��    : 1)��ֻ������USART1�жϽ��գ�δ����USART1�жϷ��͡�
*           2)�����յ�0x0d 0x0a(�س���"\r\n")����֡���ݽ������
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
		Usart5_R_Buff[Usart5_R_Count] = Res;  	  //�����յ����ַ����浽������
		Usart5_R_Count++;                			//����ָ������ƶ�
		if(Usart5_R_Count > USART5_REC_MAXLEN)       		//���������,������ָ��ָ�򻺴���׵�ַ
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
* ������  : UART2_SendString
* ����    : USART2�����ַ���
* ����    : *s�ַ���ָ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void UART5_SendString(char* s)
{
	while(*s)//����ַ���������
	{
		while(USART_GetFlagStatus(UART5, USART_FLAG_TC)==RESET); 
		USART_SendData(UART5 ,*s++);//���͵�ǰ�ַ�
	}
}

void UART5_SendByte(char s)
{
	while(USART_GetFlagStatus(UART5, USART_FLAG_TC)==RESET); 
	USART_SendData(UART5 ,s);//���͵�ǰ�ַ�
}


