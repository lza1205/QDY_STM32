

#include "all.h"

#include "gsm_code.h"
#include "gsm_base.h"
#include "usart.h"




void printf_hex(u8 *buf, int len)
{
	int i;
	u8 tmp; 
	for(i = 0; i < len; i ++)
	{
		tmp = (buf[i] >> 4);
		if(tmp > 9)
		{
			printf_c((tmp - 10) + 'A');
		}
		else
		{
			printf_c(tmp + '0');
		}

		tmp = (buf[i] & 0x0f);
		if(tmp > 9)
		{
			printf_c((tmp - 10) + 'A');
		}
		else
		{
			printf_c(tmp + '0');
		}

		printf_c(' ');
	}
}




/*******************************************************************************
* ������ : CLR_Buf2
* ����   : �������2��������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void CLR_Buf2(void)
{
	u16 k;
	for(k=0;k<Buf2_Max;k++)      //��������������
	{
		Uart2_Buf[k] = 0x00;
	}
    First_Int = 0;              //�����ַ�������ʼ�洢λ��

	clean_delay_uart();
}

/*******************************************************************************
* ������ : Find
* ����   : �жϻ������Ƿ���ָ�����ַ���
* ����   : 
* ���   : 
* ����   : unsigned char:1 �ҵ�ָ���ַ���0 δ�ҵ�ָ���ַ� 
* ע��   : 
*******************************************************************************/

u8 Find(char *a)
{ 
  if(strstr(Uart2_Buf,a)!=NULL)
	    return 1;
	else
			return 0;
}



/*******************************************************************************
* ������ : Second_AT_Command
* ����   : ����ATָ���
* ����   : �������ݵ�ָ�롢���͵ȴ�ʱ��(��λ��S)
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/

void Second_AT_Command(char *b)         
{
	CLR_Buf2(); 
 
	for (; *b!='\0';b++)
	{
		gsm_base_send_char(*b);//UART2_SendData(*b);
	}
	gsm_base_send_lr();	

}

u8 Second_AT_Command_Try(char *b,char *a,u8 wait_cnt)         
{
	u8 cnt = 0;

	CLR_Buf2(); 

	while(!Find(a)) 
	{
		Second_AT_Command(b);
		Delay_nMs(500);
		cnt ++;
		if(cnt > wait_cnt)
		{
			printf("send AT[%s] error !\r\n", b);
			return 1;
		}
	}

	return 0;
}



/*******************************************************************************
* ������ : Second_AT_Data
* ����   : ����ATָ���
* ����   : �������ݵ�ָ�롢���͵ȴ�ʱ��(��λ��S)  ���ӳ�ʱ�˳�����
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Second_AT_Data(char *b,char *a, u32 len, u8 wait_time)         
{
	u32 j;
	
	CLR_Buf2(); 

	for (j = 0; j < len; j++)
	{
		gsm_base_send_char(*b);
		b++;
	}
	gsm_base_send_char(0x1A);//UART2_SendData(*b);
	
}


//��������
void gsm_send_data(char *buf, u32 len)
{
	char *b = buf;
	u32 j;

	CLR_Buf2(); 
	
	for (j = 0; j < len; j++)
	{
		//printf("%s %d %d %d\r\n", __FILE__, __LINE__, len, j);
		gsm_base_send_char(*b);//UART2_SendData(*b);
		b++;
	}
}


/*******************************************************************************
* ������ : Wait_CREG
* ����   : �ȴ�ģ��ע��ɹ�
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Wait_CREG(void)
{
	u32 i;
	u32 k;
	i = 0;
	CLR_Buf2();
  	while(i == 0)        			
	{
		CLR_Buf2();        
		gsm_base_send_string("AT+CREG?");
		gsm_base_send_lr();
		Delay_nMs(5000);

	    for(k=0;k<Buf2_Max;k++)      			
    	{
			if(Uart2_Buf[k] == ':')
			{
				if((Uart2_Buf[k+4] == '1')||(Uart2_Buf[k+4] == '5'))
				{
					i = 1;
					UART1_SendLR();
				  break;
				}
			}
		}
		UART1_SendString("ע����.....");
	}
}

/*******************************************************************************
* ������ : Set_ATE0
* ����   : ȡ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Set_ATE0(void)
{
	Second_AT_Command("ATE0");								//ȡ������		
}



