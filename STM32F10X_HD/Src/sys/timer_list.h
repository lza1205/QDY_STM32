#ifndef __TIMER_LIST_H__
#define __TIMER_LIST_H__

#include "all.h"

//一次
#define TIMER_LIST_ONCE		0
//循环
#define TIMER_LIST_ALL		1

struct timer{
	u8 flg;
	u8 enable;
	u32 timercnt;
	u32 timer_d;	//间隔
	int (*process)(void *pdata);
	void *pdata;
	struct list_head list;
};

#endif
