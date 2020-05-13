/***********************************************************
�ļ���	:	command_server.c
����		:	Faker
�汾��	:	1.0
����		:	2015.05.15

˵��:	
	������֧�ֵ�������

***********************************************************/


#include "all.h"
#include "command.h"

#include "string.h"

extern char *gp_comman_tag[10];		//�����в���


/********************************************
������: __help
����:		help
*********************************************/

static void __help(void)
{
	int i;
	printf("/------------------- Welcome to Faks -------------------/\r\n");
	printf("You can enter the following command : \r\n");

	for(i = 0; gt_comman[i].name != NULL; i++)	//һ�����ȶ�
	{
		printf("[%d]%s       :   %s \r\n", i, gt_comman[i].name, gt_comman[i].help);
	}

	printf("/------------------- --------------- -------------------/\r\n");
}


static void __setenv(void)
{
	//��������
	if(0 == strcmp(__ENV_NETWORK_TYPE, gp_comman_tag[1]))
	{
		if(0 == strcmp(__ENV_NETWORK_TYPE_BC26, gp_comman_tag[2]))
		{
			sys_config.netword_type = NETWORD_TYPE_BC26;
		}
		else if(0 == strcmp(__ENV_NETWORK_TYPE_EC20, gp_comman_tag[2]))
		{
			sys_config.netword_type = NETWORD_TYPE_EC20;
		}
		else if(0 == strcmp(__ENV_NETWORK_TYPE_ESP8266, gp_comman_tag[2]))
		{
			sys_config.netword_type = NETWORD_TYPE_ESP8266;
		}
	}
}

static void __printenv(void)
{
	printf("\r\n");

	
	printf("device id is %lx %lx %lx \r\n\r\n", 
		sys_config.device_id[0], sys_config.device_id[1], sys_config.device_id[2]);
	
	printf("network type is ");
	switch(sys_config.netword_type)
	{
		case NETWORD_TYPE_ESP8266:
			printf("ESP8266\r\n");
			break;

		case NETWORD_TYPE_BC26:
			printf("BC26\r\n");
			break;

		case NETWORD_TYPE_EC20:
			printf("EC20\r\n");
			break;
	}

	printf("\r\n");
}

struct command_t gt_comman_server[] = {
	{
		.name		= __CMD_SETENV,
		.com_fun	= __setenv,
		.tag_num	= 0,
		.tag_p		= NULL,
		.help 		= "set env",
	},

	{
		.name		= __CMD_PRINTENV,
		.com_fun	= __printenv,
		.tag_num	= 0,
		.tag_p		= NULL,
		.help 		= "set env",
	},
	
	{
		.name		= "help",
		.com_fun	= __help,
		.tag_num	= 0,
		.tag_p		= NULL,
		.help 		= "show help",
	},
	
	{
		.name		= "?",
		.com_fun	= __help,
		.tag_num	= 0,
		.tag_p		= NULL,
		.help 		= "show help",
	},
	{
		.name		= NULL,
		.com_fun 	= NULL,
		.tag_num	= 0,
		.tag_p		= NULL,
	},
};


void server_command_init(void)
{
	gt_comman = gt_comman_server;
}


