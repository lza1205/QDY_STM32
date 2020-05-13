
#ifndef __ESP8266_H__
#define __ESP8266_H__


#ifdef __ESP8266_C__
#define __ESP8266_EXT__
#else
#define __ESP8266_EXT__	extern
#endif



__ESP8266_EXT__ void esp8266_Connect_Server(char *ip, u16 port);
__ESP8266_EXT__ void esp8266_tcp_send(u8 *buf, int len);
__ESP8266_EXT__ int esp8266_tcp_recv(u8 *buf, u32 size);





#endif 


