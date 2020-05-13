

#define __ESP8266_C__

#include "all.h"
#include "gsm_base.h"
#include "stdio.h"
//TCP 连接
static const char *__string = "AT+CIPSTART=\"UDP\",\"106.13.62.194\",8000";	//IP登录服务器

/*******************************************************************************
* 函数名 : Connect_Server
* 描述   : GPRS连接服务器函数
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void esp8266_Connect_Server(char *ip, u16 port)
{
	char connect_str[100];
	u32 ret;

	Second_AT_Command("AT+CWMODE=1");
	Delay_nMs(10);

	Set_ATE0();

	printf("扫描wifi\r\n");

	Second_AT_Command("AT+CWLAP");
	Delay_nMs(2000);

	ret = recv_gsm_data(connect_str, sizeof(connect_str));
	UART1_SendData((u8 *)connect_str, ret);

	Second_AT_Command_Try("AT+CWJAP_DEF=\"HUAWEI\",\"076812345678\"", "OK", 20);
	printf("连接 wifi 成功\r\n");
	
	//单连接
	Second_AT_Command("AT+CIPMUX=0");
	Delay_nMs(50);

	memset(connect_str, 0, 100);
	sprintf(connect_str, "AT+CIPSTART=\"TCP\",\"%s\",%d", ip, port);
	
	//tcp 连接到服务器
	if(connect_str != NULL)
	{
		Second_AT_Command_Try((char*)connect_str,"OK",10);
	}
	else
	{
		Second_AT_Command_Try((char*)__string,"OK",10);
	}

	printf("TCP 连接 成功\r\n");
	
	//Connect_Server(NULL);
	
	//进入透传模式
	Second_AT_Command("AT+CIPMODE=1");
	Delay_nMs(50);
	Second_AT_Command("AT+CIPSEND");
	Delay_nMs(100);
	CLR_Buf2();
}

/*******************************************************************************
* 函数名 : tcp_heart_beat
* 描述   : 发送数据应答服务器的指令，该函数在有两功能
					1：接收到服务器的数据后，应答服务器
					2：服务器无下发数据时，每隔10秒发送一帧心跳，保持与服务器连接
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/

void Send_OK(void)
{
	Second_AT_Command_Try("AT+CIPSEND",">",2);
	Second_AT_Command_Try("OK\32\0","SEND OK",8);;			//回复OK 
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

