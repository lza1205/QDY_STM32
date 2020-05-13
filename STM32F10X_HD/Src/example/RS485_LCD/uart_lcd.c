#define __UART_LCD_C__

#include "all.h"
#include <stdlib.h>

#include "uart_lcd.h"
#include "rs485_sensor.h"

#include "string.h"

struct uart_lcd_pcb lcd_config[] = {
	{
		.id = LCD_RY_READ_1,
		.data = {LCD_RY_READ_1_DATA},
	},
	{
		.id = LCD_RY_READ_2,
		.data = {LCD_RY_READ_2_DATA},
	},
	{
		.id = LCD_RY_SAVE_1,
		.data = {LCD_RY_SAVE_1_DATA},
	},
	{
		.id = LCD_RY_SAVE_2,
		.data = {LCD_RY_SAVE_2_DATA},
	},
	{
		.id = LCD_RY_ADJUST_Y,
		.data = {LCD_RY_ADJUST_Y_DATA},
	},
	{
		.id = LCD_RY_ADJUST_N,
		.data = {LCD_RY_ADJUST_N_DATA},
	},

	//
	{
		.id = LCD_ZD_READ_1,
		.data = {LCD_ZD_READ_1_DATA},
	},
	{
		.id = LCD_ZD_READ_2,
		.data = {LCD_ZD_READ_2_DATA},
	},
	{
		.id = LCD_ZD_SAVE_1,
		.data = {LCD_ZD_SAVE_1_DATA},
	},
	{
		.id = LCD_ZD_SAVE_2,
		.data = {LCD_ZD_SAVE_2_DATA},
	},
	{
		.id = LCD_ZD_ADJUST_Y,
		.data = {LCD_ZD_ADJUST_Y_DATA},
	},
	{
		.id = LCD_ZD_ADJUST_N,
		.data = {LCD_ZD_ADJUST_N_DATA},
	},

	//
	{
		.id = LCD_DDX_READ_1,
		.data = {LCD_DDX_READ_1_DATA},
	},
	{
		.id = LCD_DDX_READ_2,
		.data = {LCD_DDX_READ_2_DATA},
	},
	{
		.id = LCD_DDX_SAVE_1,
		.data = {LCD_DDX_SAVE_1_DATA},
	},
	{
		.id = LCD_DDX_SAVE_2,
		.data = {LCD_DDX_SAVE_2_DATA},
	},
	{
		.id = LCD_DDX_ADJUST_Y,
		.data = {LCD_DDX_ADJUST_Y_DATA},
	},
	{
		.id = LCD_DDX_ADJUST_N,
		.data = {LCD_DDX_ADJUST_N_DATA},
	},

	//
	{
		.id = LCD_PH_READ_1,
		.data = {LCD_PH_READ_1_DATA},
	},
	{
		.id = LCD_PH_READ_2,
		.data = {LCD_PH_READ_2_DATA},
	},
	{
		.id = LCD_PH_SAVE_1,
		.data = {LCD_PH_SAVE_1_DATA},
	},
	{
		.id = LCD_PH_SAVE_2,
		.data = {LCD_PH_SAVE_2_DATA},
	},
	{
		.id = LCD_PH_ADJUST_Y,
		.data = {LCD_PH_ADJUST_Y_DATA},
	},
	{
		.id = LCD_PH_ADJUST_N,
		.data = {LCD_PH_ADJUST_N_DATA},
	},

	//
	{
		.id = LCD_NH4_READ_1,
		.data = {LCD_NH4_READ_1_DATA},
	},
	{
		.id = LCD_NH4_READ_2,
		.data = {LCD_NH4_READ_2_DATA},
	},
	{
		.id = LCD_NH4_SAVE_1,
		.data = {LCD_NH4_SAVE_1_DATA},
	},
	{
		.id = LCD_NH4_SAVE_2,
		.data = {LCD_NH4_SAVE_2_DATA},
	},
	{
		.id = LCD_NH4_ADJUST_Y,
		.data = {LCD_NH4_ADJUST_Y_DATA},
	},
	{
		.id = LCD_NH4_ADJUST_N,
		.data = {LCD_NH4_ADJUST_N_DATA},
	},

	//
	{
		.id = LCD_XSG_READ_1,
		.data = {LCD_XSG_READ_1_DATA},
	},
	{
		.id = LCD_XSG_READ_2,
		.data = {LCD_XSG_READ_2_DATA},
	},
	{
		.id = LCD_XSG_SAVE_1,
		.data = {LCD_XSG_SAVE_1_DATA},
	},
	{
		.id = LCD_XSG_ADJUST_1,
		.data = {LCD_XSG_ADJUST_1_DATA},
	},
	{
		.id = LCD_XSG_ADJUST_2,
		.data = {LCD_XSG_ADJUST_2_DATA},
	},

	//
	{
		.id = LCD_YL_READ_1,
		.data = {LCD_YL_READ_1_DATA},
	},
	{
		.id = LCD_YL_READ_2,
		.data = {LCD_YL_READ_2_DATA},
	},
	{
		.id = LCD_YL_SAVE_1,
		.data = {LCD_YL_SAVE_1_DATA},
	},
	{
		.id = LCD_YL_ADJUST_1,
		.data = {LCD_YL_ADJUST_1_DATA},
	},
	{
		.id = LCD_YL_ADJUST_2,
		.data = {LCD_YL_ADJUST_2_DATA},
	},

	//
	{
		.id = LCD_YHHY_READ_1,
		.data = {LCD_YHHY_READ_1_DATA},
	},
	{
		.id = LCD_YHHY_READ_2,
		.data = {LCD_YHHY_READ_2_DATA},
	},
	{
		.id = LCD_YHHY_SAVE_1,
		.data = {LCD_YHHY_SAVE_1_DATA},
	},
	{
		.id = LCD_YHHY_SAVE_2,
		.data = {LCD_YHHY_SAVE_2_DATA},
	},
	{
		.id = LCD_YHHY_ADJUST_Y,
		.data = {LCD_YHHY_ADJUST_Y_DATA},
	},
	{
		.id = LCD_YHHY_ADJUST_N,
		.data = {LCD_YHHY_ADJUST_N_DATA},
	},

	{
		.id = LCD_READ_SENSOR,
		.data = {LCD_READ_SENSOR_DATA_1},
	},

	{
		.id = LCD_READ_SENSOR,
		.data = {LCD_READ_SENSOR_DATA_2},
	},
	{
		.id = LCD_READ_SENSOR,
		.data = {LCD_READ_SENSOR_DATA_3},
	},
	{
		.id = LCD_READ_SENSOR,
		.data = {LCD_READ_SENSOR_DATA_4},
	},
	{
		.id = LCD_READ_SENSOR,
		.data = {LCD_READ_SENSOR_DATA_5},
	},
	{
		.id = LCD_READ_SENSOR,
		.data = {LCD_READ_SENSOR_DATA_6},
	},
	{
		.id = LCD_READ_SENSOR,
		.data = {LCD_READ_SENSOR_DATA_7},
	},
	{
		.id = LCD_READ_SENSOR,
		.data = {LCD_READ_SENSOR_DATA_8},
	},
	{
		.id = LCD_READ_SENSOR,
		.data = {LCD_READ_SENSOR_DATA_9},
	},
	{
		.id = LCD_READ_SENSOR,
		.data = {LCD_READ_SENSOR_DATA_10},
	},
	{
		.id = LCD_REFRESH_SENSOR,
		.data = {LCD_REFRESH_SENSOR_DATA},
	},

	{
		.id = LCD_ADJUST_DATE_TIME,
		.data = {LCD_ADJUST_DATE_TIME_DATA},
	},

	{
		.id = LCD_EXIT_DATE_TIME,
		.data = {LCD_EXIT_DATE_TIME_DATA},
	},

	{
		.id = LCD_START_MOTOR,
		.data = {LCD_START_MOTOR_DATA},
	},
	{
		.id = LCD_GET_MOTOR,
		.data = {LCD_GET_MOTOR_DATA},
	},
	{
		.id = LCD_SET_MOTOR,
		.data = {LCD_SET_MOTOR_DATA},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_SENSOR,
		.data = {LCD_READ_ENTER_ADJUST_SENSOR_DATA_1},
	},

	{
		.id = LCD_READ_ENTER_ADJUST_SENSOR,
		.data = {LCD_READ_ENTER_ADJUST_SENSOR_DATA_2},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_SENSOR,
		.data = {LCD_READ_ENTER_ADJUST_SENSOR_DATA_3},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_SENSOR,
		.data = {LCD_READ_ENTER_ADJUST_SENSOR_DATA_4},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_SENSOR,
		.data = {LCD_READ_ENTER_ADJUST_SENSOR_DATA_5},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_SENSOR,
		.data = {LCD_READ_ENTER_ADJUST_SENSOR_DATA_6},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_SENSOR,
		.data = {LCD_READ_ENTER_ADJUST_SENSOR_DATA_7},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_SENSOR,
		.data = {LCD_READ_ENTER_ADJUST_SENSOR_DATA_8},
	},

	{
		.id = LCD_READ_ENTER_ADJUST_MOTOR,
		.data = {LCD_READ_ENTER_ADJUST_MOTOR_DATA_1},
	},

	{
		.id = LCD_READ_ENTER_ADJUST_MOTOR,
		.data = {LCD_READ_ENTER_ADJUST_MOTOR_DATA_2},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_MOTOR,
		.data = {LCD_READ_ENTER_ADJUST_MOTOR_DATA_3},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_MOTOR,
		.data = {LCD_READ_ENTER_ADJUST_MOTOR_DATA_4},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_MOTOR,
		.data = {LCD_READ_ENTER_ADJUST_MOTOR_DATA_5},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_MOTOR,
		.data = {LCD_READ_ENTER_ADJUST_MOTOR_DATA_6},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_MOTOR,
		.data = {LCD_READ_ENTER_ADJUST_MOTOR_DATA_7},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_MOTOR,
		.data = {LCD_READ_ENTER_ADJUST_MOTOR_DATA_8},
	},
	{
		.id = LCD_READ_ENTER_ADJUST_MOTOR,
		.data = {LCD_READ_ENTER_ADJUST_MOTOR_DATA_9},
	},
};


struct sensor_lcd_info sensor_lcd_map[RS485_ID_MAX] = {
	{
		.sensor_id = SENSOR_ID_RongYangBFB,
		.lcd_id = RS485_ID_RY,
	},
	{
		.sensor_id = SENSOR_ID_ZhuoDu,
		.lcd_id = RS485_ID_ZD,
	},
	{
		.sensor_id = SENSOR_ID_DianDaoXing,
		.lcd_id = RS485_ID_DDX,
	},
	{
		.sensor_id = SENSOR_ID_ph,
		.lcd_id = RS485_ID_PH,
	},
	{
		.sensor_id = SENSOR_ID_nh4,
		.lcd_id = RS485_ID_NH4,
	},
	{
		.sensor_id = SENSOR_ID_XiaoSuanGen,
		.lcd_id = RS485_ID_XSG,
	},
	{
		.sensor_id = SENSOR_ID_YuLv,
		.lcd_id = RS485_ID_YL,
	},
	{
		.sensor_id = SENSOR_ID_YangHuaHuanYuan,
		.lcd_id = RS485_ID_YHHY,
	},
};

extern struct sensor_adjust_info sensor_adjust[SENSOR_ID_MAX];




enum LCD_MACHINE_STATE lcd_state;

void set_lcd_machine_state(enum LCD_MACHINE_STATE state)
{
	printf("set state %d \r\n", state);
	lcd_state = state;
}

enum LCD_MACHINE_STATE get_lcd_machine_state()
{
	return lcd_state;
}


void uart_lcd_send(u8 *cmd)
{
	UART5_SendString(cmd);
	UART5_SendByte(0xff);
	UART5_SendByte(0xff);
	UART5_SendByte(0xff);
}

void show_date_time(void)
{
	u8 date_str[40];
	u8 time_str[40];
	RTC_Get();

	memset(date_str, 0, sizeof(date_str));
	memset(time_str, 0, sizeof(time_str));

	sprintf(date_str, "t100.txt=\"%d-%d-%d\"", calendar.w_year, calendar.w_month, calendar.w_date);
	uart_lcd_send(date_str);

	sprintf(time_str, "t101.txt=\"%d:%d\"", calendar.hour, calendar.min);
	uart_lcd_send(time_str);
}

void show_txt(u8 *txtname, u8 *str)
{
	u8 date_str[40];
	RTC_Get();

	memset(date_str, 0, sizeof(date_str));

	sprintf(date_str, "%s.txt=\"%s\"", txtname, str);
	uart_lcd_send(date_str);

}

void show_int(u8 *txtname, u32 val)
{
	u8 date_str[40];
	RTC_Get();

	memset(date_str, 0, sizeof(date_str));

	sprintf(date_str, "%s.txt=\"%d\"", txtname, val);
	uart_lcd_send(date_str);

}

void show_float(u8 *txtname, float val)
{
	u8 date_str[40];
	RTC_Get();

	memset(date_str, 0, sizeof(date_str));

	sprintf(date_str, "%s.txt=\"%4.2f\"", txtname, val);
	uart_lcd_send(date_str);

}


int __get_txt_val(u8 *txtname, u8 *tmp_recv, u8 tmp_recv_len)
{
	int i;
	u8 send_buf[50];
	u8 recv_buf[50];

	clear_uart5_data();
	
	memset(send_buf, 0, sizeof(send_buf));
	sprintf(send_buf, "get %s.txt", txtname);
	uart_lcd_send(send_buf);

	memset(recv_buf, 0, sizeof(recv_buf));
	recv_uart_5_data(recv_buf, sizeof(recv_buf), 500);

	memset(tmp_recv, 0, tmp_recv_len);
	for(i = 1; i < tmp_recv_len; i++)
	{
		if(recv_buf[i] == 0xff)
		{
			break;
		}
		tmp_recv[i -1] = recv_buf[i];
	}
}

int get_txt_intval(u8 *txtname)
{
	u8 tmp_recv[20];
	__get_txt_val(txtname, tmp_recv, sizeof(tmp_recv));
	return atoi(tmp_recv);
}

float get_txt_floatval(u8 *txtname)
{
	double dval;
	float fval;
	u8 tmp_recv[20];
	__get_txt_val(txtname, tmp_recv, sizeof(tmp_recv));

	dval = atof(tmp_recv);
	fval = dval;
	return fval;
}

u32 cur_lcd_id;
u32 adjust_lcd_id;
u32 adjust_flg = 0;
//没有任何动作
#define ADJUST_NULL	0	
//准备校准中
#define ADJUST_ING	1
//确认校准了
#define ADJUST_DONE	2

void adjust_date_time(void)
{
	u16 year;
	u8 mon, date, hour, min;
		
	year = get_txt_intval("t0");
	mon = get_txt_intval("t1");
	date = get_txt_intval("t2");
	hour = get_txt_intval("t3");
	min = get_txt_intval("t4");

	RTC_Set(year,mon, date, hour, min,0);

	show_txt("t5","校准成功");
}
void __process_read(u32 ui_id)
{
	u32 id = ui_id / 10;

	printf("___ id is %d\r\n", id);
}



void __process_read_sensor(u32 ui_id)
{
	u8 i;
	u32 id = ui_id / 10;
	u32 sub_id = ui_id % 10;
	u8 new_adjust_flg = 0;
	
	printf("___ id is %d\r\n", id);

	switch(id)
	{
		case RS485_ID_XSG:
		case RS485_ID_YL:
			new_adjust_flg = 1;
			break;
	}


	for(i = 0; i < RS485_ID_MAX; i ++)
	{
		if(id == sensor_lcd_map[i].lcd_id)
		{
			//READ 1
			if(sub_id == 0)
			{
				if(new_adjust_flg == 1)
				{
					sensor_adjust[sensor_lcd_map[i].sensor_id].intB1 = read_sensor_ad(sensor_lcd_map[i].sensor_id);
					show_int("t2", sensor_adjust[sensor_lcd_map[i].sensor_id].intB1);
				}else{
					sensor_adjust[sensor_lcd_map[i].sensor_id].B1 = read_sensor(sensor_lcd_map[i].sensor_id);
					show_one_sensor("t2", sensor_lcd_map[i].sensor_id);
				}
			}
			//READ 2
			else if(sub_id == 1)
			{	
				if(new_adjust_flg == 1)
				{
					sensor_adjust[sensor_lcd_map[i].sensor_id].intB2 = read_sensor_ad(sensor_lcd_map[i].sensor_id);
					show_int("t3", sensor_adjust[sensor_lcd_map[i].sensor_id].intB2);
				}else{
					sensor_adjust[sensor_lcd_map[i].sensor_id].B2 = read_sensor(sensor_lcd_map[i].sensor_id);
					show_one_sensor("t3", sensor_lcd_map[i].sensor_id);
				}
			}
		}
	}
}

void __process_enter_adjust_sensor(u32 ui_id)
{
	u8 i;
	u32 id = ui_id / 10;
	u32 sub_id = ui_id % 10;

	printf("___ id is %d\r\n", id);

	adjust_lcd_id = ui_id;
	adjust_flg = ADJUST_ING;

	for(i = 0; i < RS485_ID_MAX; i ++)
	{
		if(id == sensor_lcd_map[i].lcd_id)
		{
			switch(ui_id)
			{
				case LCD_XSG_READ_1:
				case LCD_XSG_READ_2:
				case LCD_YL_READ_1:
				case LCD_YL_READ_2:
					sensor_adjust[sensor_lcd_map[i].sensor_id].A1 = get_txt_floatval("t0");
					sensor_adjust[sensor_lcd_map[i].sensor_id].A2 = get_txt_floatval("t1");
					sensor_adjust[sensor_lcd_map[i].sensor_id].B1 = get_txt_floatval("t2");
					sensor_adjust[sensor_lcd_map[i].sensor_id].B2 = get_txt_floatval("t3");
					if(sub_id == 0)
					{
						sensor_adjust[sensor_lcd_map[i].sensor_id].adjust_index = 1;
					}else if(sub_id == 1){
						sensor_adjust[sensor_lcd_map[i].sensor_id].adjust_index = 2;
					}
					break;
			}
			enter_adjust_sensor(sensor_lcd_map[i].sensor_id);
		}
	}

}

void __process_exit_adjust_sensor(u32 ui_id)
{
	u8 i;
	u32 id = ui_id / 10;
	u32 sub_id = ui_id % 10;

	printf("___ id is %d\r\n", id);

	adjust_lcd_id = ui_id;
	adjust_flg = ADJUST_NULL;

	for(i = 0; i < RS485_ID_MAX; i ++)
	{
		if(id == sensor_lcd_map[i].lcd_id)
		{
			exit_adjust_sensor(sensor_lcd_map[i].sensor_id);
		}
	}

}

void __process_save_sensor(u32 ui_id)
{
	u8 i;
	u32 id = ui_id / 10;
	u32 sub_id = ui_id % 10;

	printf("___ id is %d\r\n", id);

	for(i = 0; i < RS485_ID_MAX; i ++)
	{
		if(id == sensor_lcd_map[i].lcd_id)
		{
			//获取A1  A2
			sensor_adjust[sensor_lcd_map[i].sensor_id].A1 = get_txt_floatval("t0");
			sensor_adjust[sensor_lcd_map[i].sensor_id].A2 = get_txt_floatval("t1");
			//READ 1
			if(sub_id == 2)
			{
				sensor_adjust[sensor_lcd_map[i].sensor_id].B1 = get_txt_floatval("t2");
			}else if(sub_id == 3){
				sensor_adjust[sensor_lcd_map[i].sensor_id].B2 = get_txt_floatval("t3");
			}

			
			save_sensor(sensor_lcd_map[i].sensor_id);

			if(sub_id == 2)
			{
				show_txt("t12","保存成功");
			}else{
				show_txt("t11","保存成功");
			}
		}
	}
}

void __process_adjust_sensor(u32 ui_id)
{
	int ret;
	u8 i;
	u32 id = ui_id / 10;
	u32 sub_id = ui_id % 10;

	printf("___ id is %d\r\n", id);

	adjust_lcd_id = ui_id;
	adjust_flg = ADJUST_DONE;

	for(i = 0; i < RS485_ID_MAX; i ++)
	{
		if(id == sensor_lcd_map[i].lcd_id)
		{
			switch(ui_id)
			{
				case LCD_XSG_ADJUST_1:
				case LCD_XSG_ADJUST_2:
				case LCD_YL_ADJUST_1:
				case LCD_YL_ADJUST_2:
					sensor_adjust[sensor_lcd_map[i].sensor_id].A1 = get_txt_floatval("t0");
					sensor_adjust[sensor_lcd_map[i].sensor_id].A2 = get_txt_floatval("t1");
					sensor_adjust[sensor_lcd_map[i].sensor_id].B1 = get_txt_floatval("t2");
					sensor_adjust[sensor_lcd_map[i].sensor_id].B2 = get_txt_floatval("t3");
					if(sub_id == 2)
					{
						sensor_adjust[sensor_lcd_map[i].sensor_id].adjust_index = 1;
					}else if(sub_id == 3){
						sensor_adjust[sensor_lcd_map[i].sensor_id].adjust_index = 2;
					}
					break;
			}

			
			sensor_adjust[sensor_lcd_map[i].sensor_id].A1 = get_txt_floatval("t0");
			sensor_adjust[sensor_lcd_map[i].sensor_id].A2 = get_txt_floatval("t1");
			sensor_adjust[sensor_lcd_map[i].sensor_id].B1 = get_txt_floatval("t2");
			sensor_adjust[sensor_lcd_map[i].sensor_id].B2 = get_txt_floatval("t3");

			ret = adjust_sensor(sensor_lcd_map[i].sensor_id);
			if(ret == 0)
			{
				if(sub_id == 5)
				{
					show_txt("t12","校准成功");
				}else{
					show_txt("t11","校准成功");
				}
			}else{
				if(sub_id == 5)
				{
					show_txt("t12","校准失败");
				}else{
					show_txt("t11","校准失败");
				}
			}
		}
	}
}

void __process_data(u32 ui_id)
{
	

	switch(ui_id)
	{
		case LCD_YHHY_READ_1:
		case LCD_YHHY_READ_2:
		case LCD_RY_READ_1:
		case LCD_RY_READ_2:
		case LCD_ZD_READ_1:
		case LCD_ZD_READ_2:
		case LCD_DDX_READ_1:
		case LCD_DDX_READ_2:
		case LCD_PH_READ_1:
		case LCD_PH_READ_2:
		case LCD_NH4_READ_1:
		case LCD_NH4_READ_2:
		case LCD_XSG_READ_1:
		case LCD_XSG_READ_2:
		case LCD_YL_READ_1:
		case LCD_YL_READ_2:

			//校准传感器状态
			set_lcd_machine_state( LCD_MACHINE_STATE_READ_SENSOR);
			cur_lcd_id = ui_id;
			//__process_read_sensor(ui_id);
			__process_enter_adjust_sensor(ui_id);
			__process_read_sensor(ui_id);

			break;

		case LCD_YHHY_SAVE_1:
		case LCD_YHHY_SAVE_2:
		case LCD_RY_SAVE_1:
		case LCD_RY_SAVE_2:
		case LCD_ZD_SAVE_1:
		case LCD_ZD_SAVE_2:
		case LCD_DDX_SAVE_1:
		case LCD_DDX_SAVE_2:
		case LCD_PH_SAVE_1:
		case LCD_PH_SAVE_2:
		case LCD_NH4_SAVE_1:
		case LCD_NH4_SAVE_2:
		//case LCD_XSG_SAVE_1:
		//case LCD_XSG_SAVE_2:
		//case LCD_YL_SAVE_1:
		//case LCD_YL_SAVE_2:
		case LCD_XSG_SAVE_1:
		case LCD_YL_SAVE_1:
			
			set_lcd_machine_state( LCD_MACHINE_STATE_SAVE_SENSOR);
			__process_save_sensor(ui_id);

			break;

		
		
		case LCD_YHHY_ADJUST_Y:
		case LCD_RY_ADJUST_Y:
		case LCD_ZD_ADJUST_Y:
		case LCD_DDX_ADJUST_Y:
		case LCD_PH_ADJUST_Y:
		case LCD_NH4_ADJUST_Y:
		case LCD_XSG_ADJUST_1:
		case LCD_XSG_ADJUST_2:
		case LCD_YL_ADJUST_1:
		case LCD_YL_ADJUST_2:

			set_lcd_machine_state( LCD_MACHINE_STATE_ADJUST_SENSOR);
			cur_lcd_id = ui_id;
			__process_adjust_sensor(ui_id);

			break;

		case LCD_YHHY_ADJUST_N:
		case LCD_RY_ADJUST_N:
		case LCD_ZD_ADJUST_N:
		case LCD_DDX_ADJUST_N:
		case LCD_PH_ADJUST_N:
		case LCD_NH4_ADJUST_N:

			__process_exit_adjust_sensor(ui_id);
			
			break;
			
		case LCD_READ_SENSOR:
			if(adjust_flg == ADJUST_ING)	//没有校准
			{
				__process_exit_adjust_sensor(adjust_lcd_id);
			}
			adjust_flg = ADJUST_NULL;

			set_lcd_machine_state( LCD_MACHINE_STATE_IDLE);

			show_all_sensor();
			
			read_all_sensor();
			
			show_all_sensor();

			show_date_time();

			break;

		case LCD_READ_ENTER_ADJUST_MOTOR:
			if(adjust_flg == ADJUST_ING)	//没有校准
			{
				__process_exit_adjust_sensor(adjust_lcd_id);
			}
			adjust_flg = ADJUST_NULL;

			set_lcd_machine_state( LCD_MACHINE_STATE_ENTER_MOTOR);

			break;
			
		case LCD_READ_ENTER_ADJUST_SENSOR:
			if(adjust_flg == ADJUST_ING)	//没有校准
			{
				__process_exit_adjust_sensor(adjust_lcd_id);
			}
			adjust_flg = ADJUST_NULL;

			set_lcd_machine_state( LCD_MACHINE_STATE_IDLE);

			break;
		case LCD_REFRESH_SENSOR:
			show_all_sensor();
			
			read_all_sensor();

			show_all_sensor();

			show_date_time();

			break;

		case LCD_ADJUST_DATE_TIME:
			adjust_date_time();
			show_date_time();
			break;

		case LCD_EXIT_DATE_TIME:

			show_all_sensor();
			
			read_all_sensor();

			show_all_sensor();

			show_date_time();
			break;

		case LCD_START_MOTOR:
			start_motor();
			break;

		case LCD_GET_MOTOR:
			show_int("t0", get_motor());
			break;
			
		case LCD_SET_MOTOR:
			set_motor(get_txt_intval("t1"));
			break;
	}
}

void process_data(u8 *data, u32 len)
{
	u32 i = 0;
	for(i = 0; i < sizeof(lcd_config)/sizeof(lcd_config[0]); i ++)
	{
		if(memcmp(lcd_config[i].data, data, 7) == 0)
		{
			printf("___ ui id is %d\r\n", lcd_config[i].id);
			__process_data(lcd_config[i].id);
			return ;
		}
	}

	//这里判断下是不是读取变量名0X70 0X61 0X62 0X63 0XFF 0XFF 0XFF
	//if()
}





int RS485_timer(void * pdata)
{
	

	switch(get_lcd_machine_state())
	{
		case LCD_MACHINE_STATE_READ_SENSOR:
			{
				__process_read_sensor(cur_lcd_id);
			}
			break;
		case LCD_MACHINE_STATE_IDLE:
			{
				read_all_sensor();

				show_all_sensor();

				show_date_time();
			}
			break;
	
	}
}


void uart_lcd_init(void)
{
	set_uart5_callback(process_data);
}


void rs485_lcd_main(void)
{
	uart_lcd_init();
	sensor_init();
	
	add_timer(TIMER_LIST_ALL, 2000, RS485_timer,NULL);

	RS485_timer(NULL);
	
	while(1)
	{
		qdy_process();
	}
}



/*

u8 send_buf[20];
u8 recv_buf[50];

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t200.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t201.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t202.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t203.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t204.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t205.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t206.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t207.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t208.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t209.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t210.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t211.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t212.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);

memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "t213.txt=\"%d\"", test_cnt);
uart_lcd_send(send_buf);


memset(send_buf, 0, sizeof(send_buf));
sprintf(send_buf, "get t213.txt", test_cnt);
uart_lcd_send(send_buf);

memset(recv_buf, 0, sizeof(recv_buf));
recv_uart_5_data(recv_buf, 50, 1000);

test_cnt++;

*/

