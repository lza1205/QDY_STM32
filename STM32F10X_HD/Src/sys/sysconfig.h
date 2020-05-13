#ifndef __SYS_CONFIG_H__
#define __SYS_CONFIG_H__

#ifdef __SYS_CONFIG_C__
#define __SYS_CONFIG_EXT__
#else
#define __SYS_CONFIG_EXT__	extern
#endif

#include "all.h"

struct st_sys_config{
	u32 device_id[3];
	u8 netword_type;	//Õ¯¬Á¿‡–Õ
};


__SYS_CONFIG_EXT__	struct st_sys_config sys_config;


//__SYS_CONFIG_EXT__	u8 global_temp_buff[1024];


//BC26 nbiot
#define	NETWORD_TYPE_BC26		1
//EC20	4G
#define	NETWORD_TYPE_EC20		2
//esp8266 wifi
#define	NETWORD_TYPE_ESP8266	3




void init_sys_config(void);




#endif

