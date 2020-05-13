#ifndef __TIMER_LIST_H__
#define __TIMER_LIST_H__

#include "all.h"

//һ��
#define TIMER_LIST_ONCE		0
//ѭ��
#define TIMER_LIST_ALL		1

struct timer{
	u8 flg;
	u8 enable;
	u32 timercnt;
	u32 timer_d;	//���
	int (*process)(void *pdata);
	void *pdata;
	struct list_head list;
};

#endif
