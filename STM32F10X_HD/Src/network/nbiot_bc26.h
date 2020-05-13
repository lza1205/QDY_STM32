
#ifndef __NBIOT_BC26_H__
#define __NBIOT_BC26_H__


#ifdef __NBIOT_BC26_C__
#define __NBIOT_BC26_EXT__
#else
#define __NBIOT_BC26_EXT__	extern
#endif


#include "all.h"


__NBIOT_BC26_EXT__ void esp8266_Connect_Server(char *ip, u16 port);
__NBIOT_BC26_EXT__ void esp8266_tcp_send(u8 *buf, int len);
__NBIOT_BC26_EXT__ int esp8266_tcp_recv(u8 *buf, u32 size);





#endif 


