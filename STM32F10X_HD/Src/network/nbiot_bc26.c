

#define __NBIOT_BC26_C__

#include "all.h"
#include "gsm_base.h"
#include "stdio.h"
//TCP ����
static const char *__string = "AT+QSOCON=1,6666,\"106.13.62.194\"";	//IP��¼������

/*******************************************************************************
* ������ : Connect_Server
* ����   : GPRS���ӷ���������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void bc26_Connect_Server(char *ip, u16 port)
{
	char connect_str[100];
	u32 ret;

	Wait_CREG();	//�ȴ�����ע��

	printf("����ע��ɹ�\r\n");
	
	Second_AT_Command("AT+CESQ");
	Delay_nMs(10);

	Set_ATE0();

	Second_AT_Command("AT+QGACT=1,1,\"iot\"");
	Delay_nMs(10);

	Second_AT_Command("AT+CGPADDR=1");
	Delay_nMs(10);

	Second_AT_Command("AT+QSOC=1,1,1");
	Delay_nMs(10);

	memset(connect_str, 0, 100);
	sprintf(connect_str, "AT+QSOCON=1,%d,\"%s\"", port, ip);
	
	//tcp ���ӵ�������
	if(connect_str != NULL)
	{
		Second_AT_Command_Try((char*)connect_str,"OK",10);
	}
	else
	{
		Second_AT_Command_Try((char*)__string,"OK",10);
	}

	printf("���� �ɹ�\r\n");
	
	//Connect_Server(NULL);
	
	CLR_Buf2();
}

/*******************************************************************************
* ������ : tcp_heart_beat
* ����   : ��������Ӧ���������ָ��ú�������������
					1�����յ������������ݺ�Ӧ�������
					2�����������·�����ʱ��ÿ��10�뷢��һ֡���������������������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/

void bc26_Send_OK(void)
{
	Second_AT_Command_Try("AT+CIPSEND",">",2);
	Second_AT_Command_Try("OK\32\0","SEND OK",8);;			//�ظ�OK 
}


void bc26_tcp_send(u8 *buf, int len)
{
	u8 send_head[30];
	u8 ret ;
	
	ret = byte_to_string(buf, len);

	memset(send_head, 0, sizeof(send_head));
	sprintf(send_head, "AT+QSOSEND=1,%d", ret);
	gsm_send_data(send_head,strlen(send_head));
	
	gsm_send_data(network_sendbuff, ret);

	gsm_base_send_lr();	
}

int bc26_tcp_recv(u8 *buf, u32 size)
{
	int ret = recv_gsm_data(buf, size);
	if(ret != 0)
	{
		CLR_Buf2();
	}
	return ret;
}

