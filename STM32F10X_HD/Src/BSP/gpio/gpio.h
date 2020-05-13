#ifndef __GPIO_H__
#define __GPIO_H__

#include "all.h"


struct st_pin_info{
	uint32_t GPIO_RCC;
	GPIO_TypeDef* GPIOx;
	u16	pin;
};


struct st_pin_group{
	struct st_pin_info	*pin_info;
};



#endif
