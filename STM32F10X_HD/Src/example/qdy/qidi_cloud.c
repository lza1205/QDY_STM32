#include "stm32f10x.h"
#include "usart.h"
#include "SysTick.h"
#include "timer.h"
#include "string.h"


#include "gsm_code.h"
#include "gsm_base.h"
#include "esp8266.h"

#include "all.h"



void qd_cloud_main(void)
{
	u32 ret;
	Delay_nMs(2000);

	Motor_Init();
	connet_server("106.13.62.194", 8080);
	
	while(1)
	{
		client_main();
	}

}

