

#define __NBIOT_BC26_C__

#include "all.h"
#include "gsm_base.h"
#include "stdio.h"
//TCP 连接
static const char *__string = "AT+QSOCON=1,6666,\"106.13.62.194\"";	//IP登录服务器

/*******************************************************************************
* 函数名 : Connect_Server
* 描述   : GPRS连接服务器函数
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void bc26_Connect_Server(char *ip, u16 port)
{
	char connect_str[100];
	u32 ret;

	Wait_CREG();	//等待网络注册

	printf("网络注册成功\r\n");
	
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
	
	//tcp 连接到服务器
	if(connect_str != NULL)
	{
		Second_AT_Command_Try((char*)connect_str,"OK",10);
	}
	else
	{
		Second_AT_Command_Try((char*)__string,"OK",10);
	}

	printf("连接 成功\r\n");
	
	//Connect_Server(NULL);
	
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

void bc26_Send_OK(void)
{
	Second_AT_Command_Try("AT+CIPSEND",">",2);
	Second_AT_Command_Try("OK\32\0","SEND OK",8);;			//回复OK 
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

