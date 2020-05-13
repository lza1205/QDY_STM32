/***********************************************************
文件名	:	command.h
作者		:	Faker
版本号	:	1.0
日期		:	2015.05.15

说明:	
	命令行的核心代码

***********************************************************/

#ifndef __COMMAND_H_
#define __COMMAND_H_

#ifdef __COMMAND_C_
#define __COMMAND_EXT_
#else
#define __COMMAND_EXT_	extern
#endif

#include "all.h"

/* 命令行结构体 */
struct command_t{
	char *name;
	void (*com_fun)(void);
	char tag_num;
	char *tag_p;
	char *help;
//	struct list_head list;
};

__COMMAND_EXT_ struct command_t *gt_comman;


void command_format(char *str);




#define __CMD_SETENV	"setenv"



#define __ENV_NETWORK_TYPE		"network"
#define __ENV_NETWORK_TYPE_BC26	"bc26"
#define __ENV_NETWORK_TYPE_ESP8266	"esp8266"
#define __ENV_NETWORK_TYPE_EC20	"ec29"


#define __CMD_PRINTENV	"printenv"


#endif


