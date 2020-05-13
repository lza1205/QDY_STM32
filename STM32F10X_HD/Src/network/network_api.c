#define __NETWORK_API_C__

#include "all.h"


void connet_server(char *ip, u16 port)
{
	switch(sys_config.netword_type)
	{
		case NETWORD_TYPE_ESP8266:
			esp8266_Connect_Server(ip, port);
			break;

		case NETWORD_TYPE_BC26:
			bc26_Connect_Server(ip, port);
			break;
	}
}


void network_send(u8 *buf, int len)
{
	switch(sys_config.netword_type)
	{
		case NETWORD_TYPE_ESP8266:
			esp8266_tcp_send(buf, len);
			break;

		case NETWORD_TYPE_BC26:
			bc26_tcp_send(buf, len);
			break;
	}
}



int network_recv(u8 *buf, u32 size)
{
	switch(sys_config.netword_type)
	{
		case NETWORD_TYPE_ESP8266:

			return esp8266_tcp_recv(buf, size);
			
			break;

		case NETWORD_TYPE_BC26:
			
			break;
	}
	
	return 0;
}



//数组转成字符串
u16 byte_to_string(u8 *buf, u16 len)
{
	u16 i;
	u16 size = min(len, sizeof(network_sendbuff));
	
	memset(network_sendbuff, 0, sizeof(network_sendbuff));
	for(i = 0; i < size; i++)
	{
		sprintf(network_sendbuff + (i * 2), "%x", buf[i]);
	}

	return (size * 2);
}

