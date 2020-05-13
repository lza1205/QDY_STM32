#ifndef __rs485_sensor_h__
#define __rs485_sensor_h__

#ifdef __RS485_SENSOR_C__
#define __RS485_SENSOR_EXT__	
#else
#define __RS485_SENSOR_EXT__	extern
#endif

#include "all.h"



#define SENSOR_DATA_NULL	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff

/*  ==========     �Ƕȴ�����=============*/
//�Ƕ�
#define SENSOR_GET_FLOAT_ZD	0x03,0x03,0x00,0x36,0x00,0x02,0x24,0x05



/*  ==========     ���ȴ�����=============*/
//����
#define SENSOR_GET_FLOAT_YL	0x07,0x03,0x00,0x01,0x00,0x02,0x95,0xCB



/*  ==========     ����������=============*/
//PH
#define SENSOR_GET_FLOAT_PH	0x05,0x03,0x00,0x4A,0x00,0x02,0xE5,0xDD
//NH4
#define SENSOR_GET_FLOAT_NH4	0x05,0x03,0x00,0x52,0x00,0x02,0x65,0xDA
//NH3 = NH4 * 0.15
//������ԭ��Ӧ
#define SENSOR_GET_FLOAT_YHHY	0x05,0x03,0x00,0x4C,0x00,0x02,0x65,0xDA




/*  ==========     �絼������=============*/
//�絼��
#define SENSOR_GET_FLOAT_DDX	0x04,0x03,0x00,0x38,0x00,0x02,0x45,0xC6
//�ζ�= �絼��*1000*0.0005
//Ӳ��= 1.0017*log(�絼��) + 8.386



/*  ==========     �����=============*/
//�����������
#define SENSOR_GET_FLOAT_XSG	0x06,0x03,0x00,0x01,0x00,0x02,0x95,0xCB
//������� = ����� * 0.002



/*  ==========     DO ���������� =============*/
//�¶�
#define SENSOR_GET_FLOAT_WD	0x02,0x03,0x00,0x30,0x00,0x02,0xC4,0x04
//����
#define SENSOR_GET_FLOAT_RY	0x02,0x03,0x00,0x32,0x00,0x02,0x65,0xC4
//�����ٷֱ�
#define SENSOR_GET_FLOAT_RY_BFB	0x02,0x03,0x00,0x34,0x00,0x02,0x85,0xC5



/*
struct sensor_info{
	float temp;				//�¶�
	float RongYang;			//����
	float RongYangBFB;		//�����ٷֱ�
	float ph;				//PH
	float ZhuoDu;			//�Ƕ�
	float DianDaoXing;		//�絼��
	float nh4;				//NH4
	float nh3;				//NH3
	float XiaoSuanGen;		//�����
	float YaXiaoSuanGen;	//�������
	float YuLv;				//����
	float YanDu;			//�ζ�
	float ShuiYingDu;		//ˮӲ��
	float YangHuaHuanYuan;	//������ԭ
};
*/


enum sensor_type{
	//����ֱ�Ӷ��Ĵ���
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

	//��Ҫ����
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

	u8 adjust_index;	//�������� �������Ҫָ������������У��
};


__RS485_SENSOR_EXT__ struct sensor_rs485_data sensor_data[];

__RS485_SENSOR_EXT__ void read_all_sensor(void);

__RS485_SENSOR_EXT__ float read_sensor(enum sensor_type id) ;

__RS485_SENSOR_EXT__ u16 read_sensor_ad(enum sensor_type id)  ;

__RS485_SENSOR_EXT__ int adjust_sensor(enum sensor_type id);


#endif
