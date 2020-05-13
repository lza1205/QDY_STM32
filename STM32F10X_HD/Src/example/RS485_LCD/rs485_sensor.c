#define  __RS485_SENSOR_C__

#include<stdio.h>
#include<math.h>


#include "all.h"
#include "rs485_sensor.h"
#include "uart_lcd.h"




struct sensor_rs485_data sensor_data[] = {
	{
		.id = SENSOR_ID_temp,
		.is_rs485_data = TRUE,
		.data = {SENSOR_GET_FLOAT_WD},
		.sensor_val = 0.0,
		.ui_name = "t200",
		.read_k_b = {0xff},
		.set_k_b = { 0xff},
		.adjust_data_1 = {0xff},
		.adjust_data_ok_1 = {0xff},
		.adjust_data_ok_2 = {0xff},
	},
	{
		.id = SENSOR_ID_RongYang,
		.is_rs485_data = TRUE,
		.data = {SENSOR_GET_FLOAT_RY},
		.sensor_val = 0.0,
		.ui_name = "t207",
		.read_k_b = {0x02, 0x03 , 0x00 , 0x60 , 0x00 , 0x04 , 0x44 , 0x17 },
		.set_k_b = { 0x02,0x10,0x00 ,0x60 ,0x00 ,0x04,0x08,0x00,0x00,0x80,0x3F,0x00,0x00,0x00,0x00,0x3d,0x3f},
	},
	{
		.id = SENSOR_ID_RongYangBFB,
		.data = {SENSOR_GET_FLOAT_RY_BFB},
		.sensor_val = 0.0,
		.ui_name = "t201",
		.read_k_b = {0x02, 0x03 , 0x00 , 0x60 , 0x00 , 0x04 , 0x44 , 0x17 },
		.set_k_b = { 0x02,0x10,0x00 ,0x60 ,0x00 ,0x04,0x08,0x00,0x00,0x80,0x3F,0x00,0x00,0x00,0x00,0x3d,0x3f},
	},

	//氨氮
	{
		.id = SENSOR_ID_ph,
		.is_rs485_data = TRUE,
		.data = {SENSOR_GET_FLOAT_PH},
		.sensor_val = 0.0,
		.ui_name = "t208",
		.read_k_b = {0x05, 0x03 , 0x00 , 0xC4 , 0x00 , 0x04 , 0x05 , 0xF4},
		.set_k_b = { 0x05,0x10,0x00 ,0xC4 ,0x00 ,0x04,0x08,0x00,0x00,0x80,0x3F,0x00,0x00,0x00,0x00,0x4F,0x31},
	},

	//浊度
	{
		.id = SENSOR_ID_ZhuoDu,
		.data = {SENSOR_GET_FLOAT_ZD},
		.sensor_val = 0.0,
		.ui_name = "t202",
		.read_k_b = {0x03, 0x03 , 0x00 , 0x60 , 0x00 , 0x04 , 0x44 , 0x17 },
		.set_k_b = { 0x03,0x10,0x00 ,0x60 ,0x00 ,0x04,0x08,0x00,0x00,0x80,0x3F,0x00,0x00,0x00,0x00,0x3d,0x3f},
	},
	
	{
		.id = SENSOR_ID_nh4,
		.is_rs485_data = TRUE,
		.data = {SENSOR_GET_FLOAT_NH4},
		.sensor_val = 0.0,
		.ui_name = "t203",
		.read_k_b = {0x05, 0x03 , 0x00 , 0x60 , 0x00 , 0x04 , 0x44 , 0x17 },
		.set_k_b = { 0x05,0x10,0x00 ,0x60 ,0x00 ,0x04,0x08,0x00,0x00,0x80,0x3F,0x00,0x00,0x00,0x00,0x3d,0x3f},
	},
	
	{
		.id = SENSOR_ID_XiaoSuanGen,
		.is_rs485_data = TRUE,
		.data = {SENSOR_GET_FLOAT_XSG},
		.sensor_val = 0.0,
		.ui_name = "t204",
		.read_k_b = {0xff},
		.set_k_b = { 0xff},
		.adjust_data_1 = {0x06,0x10,0x00,0x36,0x00,0x02,0x04,0x00,0x00,0x41,0x20,0x41,0x19},
		.adjust_data_ok_1 = {0x06,0x06,0x00,0x3e,0x00,0xff,0xa8,0x46},
		.adjust_data_ok_2 = {0x06,0x06,0x00,0x3f,0x00,0xff,0xf9,0x86},
		.adjust_get_ad_data = {0x06,0x03,0x00,0x66,0x00,0x01,0x64,0x15},
		.adjust_data_2 = {0x06,0x10,0x00,0x38,0x00,0x02,0x04,0x00,0x00,0x42,0xC8,0x91,0x96},
	},
	
	{
		.id = SENSOR_ID_YuLv,
		.is_rs485_data = TRUE,
		.data = {SENSOR_GET_FLOAT_YL},
		.sensor_val = 0.0,
		.ui_name = "t205",
		.read_k_b = {0xff},
		.set_k_b = { 0xff},
		.adjust_data_1 = {0x07,0x10,0x00,0x24,0x00,0x02,0x04,0x00,0x00,0x3f,0x80,0xe0,0x14},
		.adjust_data_ok_1 = {0x07,0x06,0x00,0x3e,0x00,0xff,0xa8,0x46},
		.adjust_data_ok_2 = {0x07,0x06,0x00,0x3f,0x00,0xff,0xf9,0x86},
		.adjust_get_ad_data = {0x07,0x03,0x00,0x66,0x00,0x01,0x64,0x15},
	},

	{
		.id = SENSOR_ID_YangHuaHuanYuan,
		.is_rs485_data = TRUE,
		.data = {SENSOR_GET_FLOAT_YHHY},
		.sensor_val = 0.0,
		.ui_name = "t213",
		.read_k_b = {0x01, 0x03 , 0x00 , 0xAC , 0x00 , 0x04 , 0x84 , 0x28},
		.set_k_b = { 0x01,0x10,0x00 ,0xAC ,0x00 ,0x04,0x08,0x00,0x00,0x80,0x3F,0x00,0x00,0x00,0x00,0x2E,0x6E},
	},
	
	//电导性
	{
		.id = SENSOR_ID_DianDaoXing,
		.is_rs485_data = TRUE,
		.data = {SENSOR_GET_FLOAT_DDX},
		.sensor_val = 0.0,
		.ui_name = "t209",
		.read_k_b = {0x04, 0x03 , 0x00 , 0x60 , 0x00 , 0x04 , 0x44 , 0x17 },
		.set_k_b = { 0x04,0x10,0x00 ,0x60 ,0x00 ,0x04,0x08,0x00,0x00,0x80,0x3F,0x00,0x00,0x00,0x00,0x3d,0x3f},
	},

	{
		.id = SENSOR_ID_nh3,
		.is_rs485_data = FALSE,
		.data = {SENSOR_DATA_NULL},
		.sensor_val = 0.0,
		.ui_name = "t210",
		.read_k_b = {0xff},
		.set_k_b = { 0xff},
	},

	
	{
		.id = SENSOR_ID_YaXiaoSuanGen,
		.is_rs485_data = FALSE,
		.data = {SENSOR_DATA_NULL},
		.sensor_val = 0.0,
		.ui_name = "t211",
		.read_k_b = {0xff},
		.set_k_b = { 0xff},
	},
	{
		.id = SENSOR_ID_ShuiYingDu,
		.is_rs485_data = FALSE,
		.data = {SENSOR_DATA_NULL},
		.sensor_val = 0.0,
		.ui_name = "t206",
		.read_k_b = {0xff},
		.set_k_b = { 0xff},
	},

	{
		.id = SENSOR_ID_YanDu,
		.is_rs485_data = FALSE,
		.data = {SENSOR_DATA_NULL},
		.sensor_val = 0.0,
		.ui_name = "t212",
		.read_k_b = {0xff},
		.set_k_b = { 0xff},
	},
};

void rs485_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;				//定义一个GPIO_InitTypeDef类型的GPIO初始化结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);			//使能GPIOB的外设时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	//选择要初始化的GPIOB引脚(PB5,PB6,PB7,PB8,PB9)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//设置引脚工作模式为通用推挽输出		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//设置引脚输出最大速率为50MHz
	GPIO_Init(GPIOG, &GPIO_InitStructure);			//调用库函数中的GPIO初始化函数，

	GPIO_ResetBits(GPIOG, GPIO_Pin_1);
}

void sensor_init(void)
{
	//寄存器初始化，主要是重新计算CRC值

	int i;
	u16 crc = 0;

	//rs485_init();

	for(i = 0; i < sizeof(sensor_data) / sizeof(sensor_data[0]); i ++)
	{
		crc = crc16(sensor_data[i].data, sizeof(sensor_data[i].data) - 2);
		sensor_data[i].data[6] = crc >> 8;
		sensor_data[i].data[7] = crc & 0x00ff;

		crc = crc16(sensor_data[i].read_k_b, sizeof(sensor_data[i].read_k_b) - 2);
		sensor_data[i].read_k_b[6] = crc >> 8;
		sensor_data[i].read_k_b[7] = crc & 0x00ff;

		crc = crc16(sensor_data[i].set_k_b, sizeof(sensor_data[i].set_k_b) - 2);
		sensor_data[i].set_k_b[15] = crc >> 8;
		sensor_data[i].set_k_b[16] = crc & 0x00ff;

		crc = crc16(sensor_data[i].adjust_data_1, sizeof(sensor_data[i].adjust_data_1) - 2);
		sensor_data[i].adjust_data_1[11] = crc >> 8;
		sensor_data[i].adjust_data_1[12] = crc & 0x00ff;

		crc = crc16(sensor_data[i].adjust_data_2, sizeof(sensor_data[i].adjust_data_2) - 2);
		sensor_data[i].adjust_data_2[11] = crc >> 8;
		sensor_data[i].adjust_data_2[12] = crc & 0x00ff;

		crc = crc16(sensor_data[i].adjust_data_ok_1, sizeof(sensor_data[i].adjust_data_ok_1) - 2);
		sensor_data[i].adjust_data_ok_1[6] = crc >> 8;
		sensor_data[i].adjust_data_ok_1[7] = crc & 0x00ff;

		crc = crc16(sensor_data[i].adjust_data_ok_2, sizeof(sensor_data[i].adjust_data_ok_2) - 2);
		sensor_data[i].adjust_data_ok_2[6] = crc >> 8;
		sensor_data[i].adjust_data_ok_2[7] = crc & 0x00ff;

		crc = crc16(sensor_data[i].adjust_get_ad_data, sizeof(sensor_data[i].adjust_get_ad_data) - 2);
		sensor_data[i].adjust_get_ad_data[6] = crc >> 8;
		sensor_data[i].adjust_get_ad_data[7] = crc & 0x00ff;
	}
}



void send_rs485_data(u8 *data, u8 len)
{
	hexdump("\r\n== RS485 send ==",  
                (char *)data,  
                len);
	UART3_SendData(data, len);
}

u16 recv_rs485_data(u8 *buf, u8 len)
{
	u16 ret;
	
	memset(buf, 0, len);
	ret = recv_uart_3_data(buf, len, 2000);

	if(ret != 0)
	{
		hexdump("== RS485 recv ==",  
                (char *)buf,  
                ret);
	}

	return ret;
}


u8 recv_rs485_buf[50];


u16 read_sensor_ad(enum sensor_type id) 
{
	int i;
	u8 index;
	u16 val;
	val = 0.0;

	send_rs485_data(sensor_data[id].adjust_get_ad_data, sizeof(sensor_data[id].adjust_get_ad_data));
	recv_rs485_data(recv_rs485_buf, sizeof(recv_rs485_buf));

	
	index = 3;
	//测试结束
	*((char *)(&val) + 1) = recv_rs485_buf[index++];
	*((char *)(&val)) = recv_rs485_buf[index++];
	
	return val;
}

float read_sensor(enum sensor_type id) 
{
	u16 ret;
	int i;
	u8 index;
	float val;
	val = 0.0;
	
	switch(id)
	{
		case SENSOR_ID_nh3:
			val = sensor_data[SENSOR_ID_nh4].sensor_val * 0.15;
			sensor_data[id].sensor_val = val;
			sensor_data[id].sensor_val_flg = sensor_data[SENSOR_ID_nh4].sensor_val_flg;
			break; 
			
		case SENSOR_ID_YaXiaoSuanGen:
			val = sensor_data[SENSOR_ID_XiaoSuanGen].sensor_val * 0.02;
			sensor_data[id].sensor_val = val;
			sensor_data[id].sensor_val_flg = sensor_data[SENSOR_ID_XiaoSuanGen].sensor_val_flg;
			break;
			
		case SENSOR_ID_YanDu:
			val = sensor_data[SENSOR_ID_DianDaoXing].sensor_val * 1000 * 0.0005;
			sensor_data[id].sensor_val = val;
			sensor_data[id].sensor_val_flg = sensor_data[SENSOR_ID_DianDaoXing].sensor_val_flg;
			break;
			
		case SENSOR_ID_ShuiYingDu:
			val = 1.0017 * log10(sensor_data[SENSOR_ID_DianDaoXing].sensor_val) + 8.386;
			sensor_data[id].sensor_val_flg = sensor_data[SENSOR_ID_DianDaoXing].sensor_val_flg;
			break;

	 	default:
			
			send_rs485_data(sensor_data[id].data, sizeof(sensor_data[id].data));
			ret = recv_rs485_data(recv_rs485_buf, sizeof(recv_rs485_buf));
			if(ret == 0)
			{
				sensor_data[id].sensor_val_flg = 0;
			}else{
				sensor_data[id].sensor_val_flg = 1;
			}

			if(recv_rs485_buf[0] != sensor_data[id].data[0])
			{	
				return sensor_data[id].sensor_val;
			}

			if(recv_rs485_buf[2] != 4)
			{
				return sensor_data[id].sensor_val;
			}
			
			index = 3;
			//测试
			if(recv_rs485_buf[3] == 0 && recv_rs485_buf[4] == 0 
				&& recv_rs485_buf[5] == 0 && recv_rs485_buf[6] == 0)
			{
				recv_rs485_buf[3] = 0x2b;
				recv_rs485_buf[4] = 0x87;
				recv_rs485_buf[5] = 0xEE;
				recv_rs485_buf[6] = 0x41;
			}
			index = 3;
			//余氯硝酸根不一样呀
			if(recv_rs485_buf[0] == 6 || recv_rs485_buf[0]  == 7)
			{
				//测试结束
				*((char *)(&val) + 1) = recv_rs485_buf[index++];
				*((char *)(&val)) = recv_rs485_buf[index++];
				*((char *)(&val) + 3) = recv_rs485_buf[index++];
				*((char *)(&val) + 2) = recv_rs485_buf[index++];
			}else{
				//测试结束
				*((char *)(&val)) = recv_rs485_buf[index++];
				*((char *)(&val) + 1) = recv_rs485_buf[index++];
				*((char *)(&val) + 2) = recv_rs485_buf[index++];
				*((char *)(&val) + 3) = recv_rs485_buf[index++];
			}

			if(SENSOR_ID_RongYangBFB == id)
			{
				val = val * 100;
			}

			sensor_data[id].sensor_val = val;
			
			
			break;
	}

	return val;
}

#include "uart_lcd.h"

int read_all_flg = 0;

void read_all_sensor(void)
{
	int i;

	if(read_all_flg = 1)
	{
		//return ;
	}

	read_all_flg = 1;

	for(i = 0; i < sizeof(sensor_data) / sizeof(sensor_data[0]); i ++)
	{
		sensor_data[i].sensor_val = read_sensor(i);
		qdy_process();

		if(get_lcd_machine_state() == LCD_MACHINE_STATE_READ_SENSOR)
		{
			printf("LCD_MACHINE_STATE_READ_SENSOR  exir read all \r\n");

			read_all_flg = 0;
			return ;
		}
		Delay_nMs(50);
	}

	read_all_flg = 0;
}


void show_all_sensor(void)
{
	int i;
	u8 send_buf[100];
	
	for(i = 0; i < sizeof(sensor_data)/sizeof(sensor_data[0]); i ++)
	{
		memset(send_buf, 0, sizeof(send_buf));

		if(sensor_data[i].sensor_val_flg == 0)
		{
			sprintf(send_buf, "%s.txt=\"NA\"", sensor_data[i].ui_name);
		}else{
			if(sensor_data[i].id == SENSOR_ID_DianDaoXing)
			{
				sprintf(send_buf, "%s.txt=\"%4.3f\"", sensor_data[i].ui_name, sensor_data[i].sensor_val/10);
			}else{
				sprintf(send_buf, "%s.txt=\"%4.3f\"", sensor_data[i].ui_name, sensor_data[i].sensor_val);
			}
		}
		uart_lcd_send(send_buf);
	}
}

void show_one_sensor(u8 *txt, enum sensor_type id)
{
	u8 send_buf[20];

	sprintf(send_buf, "%s.txt=\"%4.3f\"", txt, sensor_data[id].sensor_val);
	uart_lcd_send(send_buf);
}

struct sensor_adjust_info sensor_adjust[SENSOR_ID_MAX];

//进入传感器状态,有些需要先把  k  写 1  和b写 0
void enter_adjust_sensor(enum sensor_type id)
{
	//先保存原本的 k  和 b
	//读取k 和 b

	float k,b;
	u8 index;

	switch(id)
	{
		case SENSOR_ID_RongYangBFB:
		case SENSOR_ID_ph:		
		case SENSOR_ID_ZhuoDu:	
		case SENSOR_ID_nh4:			
		//case SENSOR_ID_YangHuaHuanYuan:  暂时没有
		case SENSOR_ID_DianDaoXing:
		case SENSOR_ID_YangHuaHuanYuan:
			//读取
			send_rs485_data(sensor_data[id].read_k_b, sizeof(sensor_data[id].read_k_b));
			recv_rs485_data(recv_rs485_buf, sizeof(recv_rs485_buf));

			index = 7;
			//测试结束
			*((char *)(&k)) = recv_rs485_buf[index++];
			*((char *)(&k) + 1) = recv_rs485_buf[index++];
			*((char *)(&k) + 2) = recv_rs485_buf[index++];
			*((char *)(&k) + 3) = recv_rs485_buf[index++];

			index = 11;
			//测试结束
			*((char *)(&b)) = recv_rs485_buf[index++];
			*((char *)(&b) + 1) = recv_rs485_buf[index++];
			*((char *)(&b) + 2) = recv_rs485_buf[index++];
			*((char *)(&b) + 3) = recv_rs485_buf[index++];

			//保存 k  和 b
			sensor_adjust[id].k_old = k;
			sensor_adjust[id].b_old = b;

			//写k=1  b=0
			sensor_adjust[id].adjust_flg = 1;	//记得要恢复
			send_rs485_data(sensor_data[id].set_k_b, sizeof(sensor_data[id].set_k_b));
			break;

			case SENSOR_ID_YuLv:

				break;
				
			case SENSOR_ID_XiaoSuanGen:	
			
			
			break;
#if 0
		case SENSOR_ID_XiaoSuanGen:	
		case SENSOR_ID_YuLv:
			float val = 0.0;
			u16 crc;
			u8 *p_data;

			if(sensor_adjust[id].adjust_index == 1)
			{
				val = sensor_adjust[id].A1;
				p_data = sensor_data[id].adjust_data_1;
			}else{
				val = sensor_adjust[id].A2;
				p_data = sensor_data[id].adjust_data_2;
			}

			if(id == SENSOR_ID_YuLv)
			{
				val = sensor_adjust[id].A2;
				p_data = sensor_data[id].adjust_data_1;
			}
			
			index = 7;
			sensor_data[id].adjust_data_1[index++] = *((char *)(&val));
			sensor_data[id].adjust_data_1[index++] = *((char *)(&val) + 1);
			sensor_data[id].adjust_data_1[index++] = *((char *)(&val) + 2);
			sensor_data[id].adjust_data_1[index++] = *((char *)(&val) + 3);

			crc = crc16(sensor_data[id].adjust_data_1, sizeof(sensor_data[id].adjust_data_1) - 2);
			sensor_data[id].adjust_data_1[9] = crc >> 8;
			sensor_data[id].adjust_data_1[10] = crc & 0x00ff;

			send_rs485_data(sensor_data[id].adjust_data_1, sizeof(sensor_data[id].adjust_data_1));
			
			break;
#endif
	}
}


void save_sensor(enum sensor_type id)
{
	float val = 0.0;
	u16 crc;
	u8 *p_data;
	u8 index;

	switch(id)
	{
		case SENSOR_ID_YuLv:
			
			printf("A1 %f  A2  %f	\r\n", 
			sensor_adjust[id].A1, sensor_adjust[id].A2);
			
			val = sensor_adjust[id].A2;
			p_data = sensor_data[id].adjust_data_1;
			
			index = 7;

			p_data[index++] = *((char *)(&val) + 1);
			p_data[index++] = *((char *)(&val));
			p_data[index++] = *((char *)(&val) + 3);
			p_data[index++] = *((char *)(&val) + 2);
			

			crc = crc16(p_data, sizeof(sensor_data[id].adjust_data_1) - 2);
			p_data[11] = crc >> 8;
			p_data[12] = crc & 0x00ff;

			printf("______ 余氯 写 低位\r\n");
			send_rs485_data(p_data, sizeof(sensor_data[id].adjust_data_1));

			break;
			
		case SENSOR_ID_XiaoSuanGen:	
			printf("A1 %f  A2  %f   \r\n", 
				sensor_adjust[id].A1, sensor_adjust[id].A2);
			
			val = sensor_adjust[id].A1;
			p_data = sensor_data[id].adjust_data_1;
			
			index = 7;
			
			p_data[index++] = *((char *)(&val) + 1);
			p_data[index++] = *((char *)(&val));
			p_data[index++] = *((char *)(&val) + 3);
			p_data[index++] = *((char *)(&val) + 2);

			crc = crc16(p_data, sizeof(sensor_data[id].adjust_data_1) - 2);
			p_data[11] = crc >> 8;
			p_data[12] = crc & 0x00ff;

			printf("______ 硝酸根 写 低位\r\n");
			send_rs485_data(p_data, sizeof(sensor_data[id].adjust_data_1));


			Delay_nMs(100);
			
			val = sensor_adjust[id].A2;
			p_data = sensor_data[id].adjust_data_2;

			
			if(id == SENSOR_ID_YuLv)
			{
				val = sensor_adjust[id].A2;
				p_data = sensor_data[id].adjust_data_1;
			}
			
			index = 7;
		
			p_data[index++] = *((char *)(&val) + 1);
			p_data[index++] = *((char *)(&val));
			p_data[index++] = *((char *)(&val) + 3);
			p_data[index++] = *((char *)(&val) + 2);

			crc = crc16(p_data, sizeof(sensor_data[id].adjust_data_1) - 2);
			p_data[11] = crc >> 8;
			p_data[12] = crc & 0x00ff;

			printf("______ 硝酸根 写 高位\r\n");
			send_rs485_data(p_data, sizeof(sensor_data[id].adjust_data_1));

			break;
	}

}

void exit_adjust_sensor(enum sensor_type id)
{
	//把kb 写回去
	float k, b;
	u8 index;
	u16 crc = 0;
	u8 send_buf[SENSOR_SET_KB_MAX];

	if(sensor_adjust[id].adjust_flg == 1)
	{
		k = sensor_adjust[id].k_old;
		b = sensor_adjust[id].b_old;

		memcpy(send_buf, sensor_data[id].set_k_b, sizeof(send_buf));

		index = 7;
		send_buf[index++] = *((char *)(&k));
		send_buf[index++] = *((char *)(&k) + 1);
		send_buf[index++] = *((char *)(&k) + 2);
		send_buf[index++] = *((char *)(&k) + 3);

		index = 11;
		send_buf[index++] = *((char *)(&b));
		send_buf[index++] = *((char *)(&b) + 1);
		send_buf[index++] = *((char *)(&b) + 2);
		send_buf[index++] = *((char *)(&b) + 3);

		crc = crc16(send_buf, sizeof(send_buf) - 2);
		send_buf[15] = crc >> 8;
		send_buf[16] = crc & 0x00ff;

		send_rs485_data(send_buf, sizeof(send_buf));
	}
}


int adjust_sensor(enum sensor_type id)
{
	//计算K B
	float k, b;
	u8 index;
	u16 crc = 0;
	u8 send_buf[SENSOR_SET_KB_MAX];

	switch(id)
	{
		case SENSOR_ID_RongYangBFB:
		case SENSOR_ID_ph:		
		case SENSOR_ID_ZhuoDu:	
		case SENSOR_ID_nh4:			
		case SENSOR_ID_DianDaoXing:
		case SENSOR_ID_YangHuaHuanYuan:

			if(id == SENSOR_ID_RongYangBFB)
			{
				sensor_adjust[id].A1 = 0;
				sensor_adjust[id].B1 = 0;
				sensor_adjust[id].A2 = 100;
			}
			sensor_adjust[id].adjust_flg = 0;	//不用恢复

			printf("A1 %f  A2  %f   B1 %f  B2  %f \r\n", 
				sensor_adjust[id].A1, sensor_adjust[id].A2,
				sensor_adjust[id].B1, sensor_adjust[id].B2);
			k = (sensor_adjust[id].A2 - sensor_adjust[id].A1)/(sensor_adjust[id].B2 - sensor_adjust[id].B1);
			b = sensor_adjust[id].A2 - (k * sensor_adjust[id].B2);

			printf("设置的k值是: %f  b值是 %f \r\n", k, b);

/*
			if(k<0.5 || k > 2)
			{
				printf("k应该在0.5 ~ 1\r\n");
				return -1;
			}

			if(b < -1 || b > 1)
			{
				printf("b应该在-1 ~ 1\r\n");
				return -1;
			}
			*/
			memcpy(send_buf, sensor_data[id].set_k_b, sizeof(send_buf));

			index = 7;
			send_buf[index++] = *((char *)(&k));
			send_buf[index++] = *((char *)(&k) + 1);
			send_buf[index++] = *((char *)(&k) + 2);
			send_buf[index++] = *((char *)(&k) + 3);

			index = 11;
			send_buf[index++] = *((char *)(&b));
			send_buf[index++] = *((char *)(&b) + 1);
			send_buf[index++] = *((char *)(&b) + 2);
			send_buf[index++] = *((char *)(&b) + 3);

			crc = crc16(send_buf, sizeof(send_buf) - 2);
			send_buf[15] = crc >> 8;
			send_buf[16] = crc & 0x00ff;

			send_rs485_data(send_buf, sizeof(send_buf));

			break;

		case SENSOR_ID_YuLv:	
		case SENSOR_ID_XiaoSuanGen:	
			float val = 0.0;
			u16 crc;
			u8 *p_data;
			if(sensor_adjust[id].adjust_index == 1)
			{
				val = sensor_adjust[id].B1;
				p_data = sensor_data[id].adjust_data_ok_1;
			}else{
				val = sensor_adjust[id].B2;
				p_data = sensor_data[id].adjust_data_ok_2;
			}
			

			crc = crc16(p_data, sizeof(sensor_data[id].adjust_data_ok_1) - 2);
			p_data[sizeof(sensor_data[id].adjust_data_ok_1) - 2] = crc >> 8;
			p_data[sizeof(sensor_data[id].adjust_data_ok_1) - 1] = crc & 0x00ff;

			send_rs485_data(p_data, sizeof(sensor_data[id].adjust_data_ok_1));
			
			break;

			
#if 0
		case SENSOR_ID_XiaoSuanGen:	
		case SENSOR_ID_YuLv:
			float val = 0.0;
			u16 crc;
			u8 *p_data;
			if(sensor_adjust[id].adjust_index == 1)
			{
				val = sensor_adjust[id].B1;
				p_data = sensor_data[id].adjust_data_ok_1;
			}else{
				val = sensor_adjust[id].B2;
				p_data = sensor_data[id].adjust_data_ok_2;
			}
			
			index = 7;
			p_data[index++] = *((char *)(&val));
			p_data[index++] = *((char *)(&val) + 1);
			p_data[index++] = *((char *)(&val) + 2);
			p_data[index++] = *((char *)(&val) + 3);

			crc = crc16(p_data, sizeof(sensor_data[id].adjust_data_ok_1) - 2);
			p_data[sizeof(sensor_data[id].adjust_data_ok_1) - 2] = crc >> 8;
			p_data[sizeof(sensor_data[id].adjust_data_ok_1) - 1] = crc & 0x00ff;

			send_rs485_data(p_data, sizeof(sensor_data[id].adjust_data_ok_1));
			
			break;
#endif
	}

	return 0;
}


u8 start_motor_data[] = { 0x01, 0x10, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0E, 0x0C};

void start_motor(void)
{
	send_rs485_data(start_motor_data, sizeof(start_motor_data));
}


u8 get_motor_data[] = { 0x01,0x03,0x00,0x1A,0x00,0x01,0xA5,0xCD};

int get_motor(void)
{
	int index;
	u16 time;
	
	send_rs485_data(get_motor_data, sizeof(get_motor_data));
	recv_rs485_data(recv_rs485_buf, sizeof(recv_rs485_buf));

	index = 3;
	//测试
	if(recv_rs485_buf[3] == 0 && recv_rs485_buf[4] == 0)
	{
		recv_rs485_buf[3] = 0x00;
		recv_rs485_buf[4] = 0x1e;
	}
	index = 3;
	//测试结束
	*((char *)(&time) + 1) = recv_rs485_buf[index++];
	*((char *)(&time)) = recv_rs485_buf[index++];

	return time;
}

u8 set_motor_data[] = {0x01, 0x10, 0x00, 0x1A, 0x00, 0x01, 0x02, 0x1E, 0x00, 0xAD, 0xCA};
void set_motor(u16 time)
{
	int index;
	u16 crc = 0;
	
	index = 7;
	set_motor_data[index++] = *((char *)(&time));
	set_motor_data[index++] = *((char *)(&time) + 1);

	crc = crc16(set_motor_data, sizeof(set_motor_data) - 2);
	set_motor_data[9] = crc >> 8;
	set_motor_data[10] = crc & 0x00ff;

	send_rs485_data(set_motor_data, sizeof(set_motor_data));
}

