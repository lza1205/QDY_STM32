#ifndef __rs485_sensor_h__
#define __rs485_sensor_h__

#ifdef __RS485_SENSOR_C__
#define __RS485_SENSOR_EXT__	
#else
#define __RS485_SENSOR_EXT__	extern
#endif

#include "all.h"



#define SENSOR_DATA_NULL	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff

/*  ==========     浊度传感器=============*/
//浊度
#define SENSOR_GET_FLOAT_ZD	0x03,0x03,0x00,0x36,0x00,0x02,0x24,0x05



/*  ==========     余氯传感器=============*/
//余氯
#define SENSOR_GET_FLOAT_YL	0x07,0x03,0x00,0x01,0x00,0x02,0x95,0xCB



/*  ==========     氨氮传感器=============*/
//PH
#define SENSOR_GET_FLOAT_PH	0x05,0x03,0x00,0x4A,0x00,0x02,0xE5,0xDD
//NH4
#define SENSOR_GET_FLOAT_NH4	0x05,0x03,0x00,0x52,0x00,0x02,0x65,0xDA
//NH3 = NH4 * 0.15
//氧化还原反应
#define SENSOR_GET_FLOAT_YHHY	0x05,0x03,0x00,0x4C,0x00,0x02,0x65,0xDA




/*  ==========     电导传感器=============*/
//电导性
#define SENSOR_GET_FLOAT_DDX	0x04,0x03,0x00,0x38,0x00,0x02,0x45,0xC6
//盐度= 电导性*1000*0.0005
//硬度= 1.0017*log(电导性) + 8.386



/*  ==========     硝酸根=============*/
//硝酸根传感器
#define SENSOR_GET_FLOAT_XSG	0x06,0x03,0x00,0x01,0x00,0x02,0x95,0xCB
//亚硝酸根 = 硝酸根 * 0.002



/*  ==========     DO 溶氧传感器 =============*/
//温度
#define SENSOR_GET_FLOAT_WD	0x02,0x03,0x00,0x30,0x00,0x02,0xC4,0x04
//溶氧
#define SENSOR_GET_FLOAT_RY	0x02,0x03,0x00,0x32,0x00,0x02,0x65,0xC4
//溶氧百分比
#define SENSOR_GET_FLOAT_RY_BFB	0x02,0x03,0x00,0x34,0x00,0x02,0x85,0xC5



/*
struct sensor_info{
	float temp;				//温度
	float RongYang;			//溶氧
	float RongYangBFB;		//溶氧百分比
	float ph;				//PH
	float ZhuoDu;			//浊度
	float DianDaoXing;		//电导性
	float nh4;				//NH4
	float nh3;				//NH3
	float XiaoSuanGen;		//硝酸根
	float YaXiaoSuanGen;	//亚硝酸根
	float YuLv;				//余氯
	float YanDu;			//盐度
	float ShuiYingDu;		//水硬度
	float YangHuaHuanYuan;	//氧化还原
};
*/


enum sensor_type{
	//可以直接读寄存器
	SENSOR_ID_temp = 0,
	SENSOR_ID_RongYang,
	SENSOR_ID_RongYangBFB,
	SENSOR_ID_ph,		
	SENSOR_ID_ZhuoDu,		
	SENSOR_ID_nh4,			
 	SENSOR_ID_XiaoSuanGen,	
	SENSOR_ID_YuLv,			
	SENSOR_ID_YangHuaHuanYuan,
	SENSOR_ID_DianDaoXing,

	//需要计算
	SENSOR_ID_nh3,
	SENSOR_ID_YaXiaoSuanGen,
	SENSOR_ID_ShuiYingDu,
	SENSOR_ID_YanDu,

	SENSOR_ID_MAX,
};

#define SENSOR_SET_KB_MAX	17

struct sensor_rs485_data{
	enum sensor_type id;
	u8 is_rs485_data;
	u8 data[8];
	float sensor_val;
	u8 sensor_val_flg;
	u8 ui_name[10];

	u8 read_k_b[8];
	u8 set_k_b[SENSOR_SET_KB_MAX];

	u8 adjust_data_1[13];
	u8 adjust_data_ok_1[8];
	u8 adjust_data_ok_2[8];
	u8 adjust_get_ad_data[8];
	u8 adjust_data_2[13];
};

struct sensor_adjust_info{
	float A1;
	float A2;
	float B1;
	float B2;

	u16 intB1;
	u16 intB2;

	float k_old;
	float b_old;

	u8 adjust_flg;

	u8 adjust_index;	//对于余氯 硝酸根，要指明用那组数据校验
};


__RS485_SENSOR_EXT__ struct sensor_rs485_data sensor_data[];

__RS485_SENSOR_EXT__ void read_all_sensor(void);

__RS485_SENSOR_EXT__ float read_sensor(enum sensor_type id) ;

__RS485_SENSOR_EXT__ u16 read_sensor_ad(enum sensor_type id)  ;

__RS485_SENSOR_EXT__ int adjust_sensor(enum sensor_type id);


#endif
