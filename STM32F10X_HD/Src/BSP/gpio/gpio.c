
#include "gpio.h"
#include "stm32f10x_rcc.h"


struct st_pin_info out_pin_1 = {

	.GPIO_RCC	= RCC_APB2Periph_GPIOD,
	.GPIOx		= GPIOD,
	.pin		= GPIO_Pin_13,

};

struct st_pin_info out_pin_2 = {

	.GPIO_RCC	= RCC_APB2Periph_GPIOD,
	.GPIOx		= GPIOD,
	.pin		= GPIO_Pin_13,

};



struct st_pin_info input_pin_1 = {

	.GPIO_RCC	= RCC_APB2Periph_GPIOA,
	.GPIOx		= GPIOA,
	.pin		= GPIO_Pin_9,

};



struct st_pin_info* out_pin_group[] = {
	&out_pin_1,
	&out_pin_2,
};

struct st_pin_info*	input_pin_group[] = {
	&input_pin_1,
	&input_pin_1,
};



void __gpio_bsp_init(struct st_pin_info *pin_info)
{
	GPIO_InitTypeDef  GPIO_InitStructure;				//定义一个GPIO_InitTypeDef类型的GPIO初始化结构体
	
	RCC_APB2PeriphClockCmd(pin_info->GPIO_RCC, ENABLE);			//使能GPIOB的外设时钟	
	
	GPIO_InitStructure.GPIO_Pin = pin_info->pin;	//选择要初始化的GPIOB引脚(PB5,PB6,PB7,PB8,PB9)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//设置引脚工作模式为通用推挽输出		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//设置引脚输出最大速率为50MHz
	GPIO_Init(pin_info->GPIOx, &GPIO_InitStructure);			//调用库函数中的GPIO初始化函数，初始化GPIOB中的PB5,PB6,PB7,PB8,PB9引脚
				 
}


void gpio_bsp_init(void)
{
	int i;
	for(i = 0; i < sizeof(out_pin_group)/sizeof(out_pin_group[0]); i ++)
	{
		__gpio_bsp_init(out_pin_group[i]);
	}
}


