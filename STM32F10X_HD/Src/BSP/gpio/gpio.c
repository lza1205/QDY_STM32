
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
	GPIO_InitTypeDef  GPIO_InitStructure;				//����һ��GPIO_InitTypeDef���͵�GPIO��ʼ���ṹ��
	
	RCC_APB2PeriphClockCmd(pin_info->GPIO_RCC, ENABLE);			//ʹ��GPIOB������ʱ��	
	
	GPIO_InitStructure.GPIO_Pin = pin_info->pin;	//ѡ��Ҫ��ʼ����GPIOB����(PB5,PB6,PB7,PB8,PB9)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������Ź���ģʽΪͨ���������		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//������������������Ϊ50MHz
	GPIO_Init(pin_info->GPIOx, &GPIO_InitStructure);			//���ÿ⺯���е�GPIO��ʼ����������ʼ��GPIOB�е�PB5,PB6,PB7,PB8,PB9����
				 
}


void gpio_bsp_init(void)
{
	int i;
	for(i = 0; i < sizeof(out_pin_group)/sizeof(out_pin_group[0]); i ++)
	{
		__gpio_bsp_init(out_pin_group[i]);
	}
}


