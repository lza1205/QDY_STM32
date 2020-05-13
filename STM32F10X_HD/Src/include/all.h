
#ifndef __ALL_H__
#define __ALL_H__


#define min(x,y) ( (x)>(y)?(y):(x) )

#define __max(a,b)        (((a) > (b)) ? (a) : (b))
#define __min(a,b)        (((a) < (b)) ? (a) : (b))

#define TRUE		1
#define FALSE		0

#include "stm32f10x.h"

#include "config.h"
#include "my_list.h"
#include "timer_list.h"


#include "usart.h"
#include "SysTick.h"
#include "timer.h"
#include "string.h"
#include "RTC.h"


#include "gsm_code.h"
#include "gsm_base.h"

#include "esp8266.h"

#include "network_api.h"

#include "sysconfig.h"
#include "qdy_system.h"


#endif


