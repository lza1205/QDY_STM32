
#define __SYS_CONFIG_C__

#include "sysconfig.h"

#define UID_BASE              0x1FFFF7E8UL    /*!< Unique device ID register base address */

void init_sys_config(void)
{
	sys_config.device_id[0] = (u32)(READ_REG(*((u32 *)UID_BASE)));
	sys_config.device_id[1] = (u32)(READ_REG(*((u32 *)(UID_BASE + 4U))));
	sys_config.device_id[2] = (u32)(READ_REG(*((u32 *)(UID_BASE + 8U))));

	sys_config.netword_type = NETWORD_TYPE_ESP8266;

}





