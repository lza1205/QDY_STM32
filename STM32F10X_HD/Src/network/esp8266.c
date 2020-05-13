

#define __ESP8266_C__

#include "all.h"
#include "gsm_base.h"
#include "stdio.h"
//TCP ����
static const char *__string = "AT+CIPSTART=\"UDP\",\"106.13.62.194\",8000";	//IP��¼������

/*******************************************************************************
* ������ : Connect_Server
* ����   : GPRS���ӷ���������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void esp8266_Connect_Server(char *ip, u16 port)
{
	char connect_str[100];
	u32 ret;

	Second_AT_Command("AT+CWMODE=1");
	Delay_nMs(10);

	Set_ATE0();

	printf("ɨ��wifi\r\n");

	Second_AT_Command("AT+CWLAP");
	Delay_nMs(2000);

	ret = recv_gsm_data(connect_str, sizeof(connect_str));
	UART1_SendData((u8 *)connect_str, ret);

	Second_AT_Command_Try("AT+CWJAP_DEF=\"HUAWEI\",\"076812345678\"", "OK", 20);
	printf("���� wifi �ɹ�\r\n");
	
	//������
	Second_AT_Command("AT+CIPMUX=0");
	Delay_nMs(50);

	memset(connect_str, 0, 100);
	sprintf(connect_str, "AT+CIPSTART=\"TCP\",\"%s\",%d", ip, port);
	
	//tcp ���ӵ�������
	if(connect_str != NULL)
	{
		Second_AT_Command_Try((char*)connect_str,"OK",10);
	}
	else
	{
		Second_AT_Command_Try((char*)__string,"OK",10);
	}

	printf("TCP ���� �ɹ�\r\n");
	
	//Connect_Server(NULL);
	
	//����͸��ģʽ
	Second_AT_Command("AT+CIPMODE=1");
	Delay_nMs(50);
	Second_AT_Command("AT+CIPSEND");
	Delay_nMs(100);
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

void Send_OK(void)
{
	Second_AT_Command_Try("AT+CIPSEND",">",2);
	Second_AT_Command_Try("OK\32\0","SEND OK",8);;			//�ظ�OK 
}


void esp8266_tcp_send(u8 *buf, int len)
{
	gsm_send_data(buf,len);
}

int esp8266_tcp_recv(u8 *buf, u32 size)
{
	int ret = recv_gsm_data(buf, size);
	if(ret != 0)
	{
		CLR_Buf2();
	}
	return ret;
}

