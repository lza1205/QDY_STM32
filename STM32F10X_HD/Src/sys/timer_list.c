#include "all.h"
#include "timer_list.h"
#include "string.h"

extern vu32 __timer3_cnt;

LIST_HEAD(timer_list_head);		//定义并初始化一个链表头


struct timer *add_timer(u8 flg, u32 timercnt, int (*process)(void *pdata), void *pdata)
{
	struct timer *t = NULL;

	t = (struct timer *)malloc(sizeof(struct timer));

	if(t == NULL)
	{
		return NULL;
	}

	t->flg = flg;
	t->enable = 1;
	t->timercnt = timercnt + __timer3_cnt;
	t->timer_d = timercnt;
	t->process = process;
	t->pdata = pdata;

	list_add(&t->list,&timer_list_head);
	return t;
}


void del_timer(struct timer *t)
{
	list_del(&t->list);
	free(t);
	return ;
}

static int process_timer_flg = 0;
void process_timer_list(void)
{
	struct timer *pos, *n;

	if(process_timer_flg == 0)
	{
		process_timer_flg = 1;
		list_for_each_entry_safe_reverse(pos,n,&timer_list_head,list, struct timer)
		{
			if((__timer3_cnt >= pos->timercnt) && (pos->enable == 1))
			{
				pos->enable = 0;
				pos->process(pos->pdata);
				if(pos->flg == TIMER_LIST_ONCE)
				{
					del_timer(pos);
				}else if(pos->flg == TIMER_LIST_ALL){
					pos->enable = 1;
					pos->timercnt = __timer3_cnt + pos->timer_d;
				}
			}
		}
	}

	process_timer_flg = 0;
}



#if 1

LIST_HEAD(irq_timer_list_head);		//定义并初始化一个链表头


struct timer *add_irq_timer(u8 flg, u32 timercnt, int (*process)(void *pdata), void *pdata)
{
	struct timer *t = NULL;

	t = (struct timer *)malloc(sizeof(struct timer));

	if(t == NULL)
	{
		return NULL;
	}

	t->flg = flg;
	t->enable = 1;
	t->timercnt = timercnt + __timer3_cnt;
	t->timer_d = timercnt;
	t->process = process;
	t->pdata = pdata;

	__disable_irq();
	list_add(&t->list,&irq_timer_list_head);
	__enable_irq();
	
	return t;
}


void del_irq_timer(struct timer *t)
{
	__disable_irq();
	list_del(&t->list);
	__enable_irq();
	
	free(t);
	return ;
}


void process_irq_timer_list(void)
{
	struct timer *pos, *n;

	list_for_each_entry_safe_reverse(pos,n,&irq_timer_list_head,list, struct timer)
	{
		if((__timer3_cnt >= pos->timercnt) && (pos->enable == 1))
		{
			pos->enable = 0;
			pos->process(pos->pdata);
			if(pos->flg == TIMER_LIST_ONCE)
			{
				del_irq_timer(pos);
			}else if(pos->flg == TIMER_LIST_ALL){
				pos->enable = 1;
				pos->timercnt = __timer3_cnt + pos->timer_d;
			}
		}
	}
}

#endif

