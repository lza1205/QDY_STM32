#ifndef __NETWORK_API_H__
#define __NETWORK_API_H__


#ifdef __NETWORK_API_C__
#define __NETWORK_API_EXT__
#else
#define __NETWORK_API_EXT__	extern
#endif

__NETWORK_API_EXT__	u8 network_sendbuff[1024];


void connet_server(char *ip, u16 port);
void network_send(u8 *buf, int len);
int network_recv(u8 *buf, u32 size);


#endif

