
#include "all.h"


void qdy_system_init(void)
{
	init_sys_config();

	server_command_init();

	printf("��ӭʹ�� qd ϵͳ\r\n");
	printf("qdy # ");
}


void qdy_process(void)
{
	process_uart_1_data();
	process_uart_5_data();
	process_timer_list();
}




/*ModBus ����CRC��Ĳ���Ϊ��

(1).Ԥ��16λ�Ĵ���ΪFFFFH���ƴ˼Ĵ���ΪCRC�Ĵ�����

(2).�ѵ�һ��8λ������CRC�Ĵ����ĵ�λ����򣬰ѽ������CRC�Ĵ�����

(3).�ѼĴ�������������һλ(����λ)����0����λ��������λ��

(4).������λΪ0���ظ���3��(�ٴ���λ)������λΪ1��CRC�Ĵ��������ʽA001��1010 0000 0000 0001���������

(5).�ظ�����3��4��ֱ������8�Σ���������8λ����ȫ�������˴���

(6).�ظ�����2������5��������һ��8λ���ݵĴ���

(7).���õ���CRC�Ĵ�����ΪCRC�롣(CRC�� = CRC_L +CRC_H)

*/

/*****************crcУ��**********************************************/

//crc���ɺ���������crc�洢��Ԥ�ȶ��ڵ�������

//���÷�ʽcrc16��ָ�����ݵ�ָ�룬��ҪУ������ݳ��ȣ�



u16 crc16(u8 *ptr,u8 len)
{
	unsigned long wcrc=0XFFFF;//Ԥ��16λcrc�Ĵ�������ֵȫ��Ϊ1

	int i=0,j=0;//�������

	for(i=0;i<len;i++)//ѭ������ÿ������
    {

		wcrc^=*ptr++;//����λ������crc�Ĵ������.ָ���ַ���ӣ�ָ���¸�����

		for(j=0;j<8;j++)//ѭ���������ݵ�
		{
			if(wcrc&0X0001)//�ж����Ƴ����ǲ���1�������1�������ʽ�������
			{
				wcrc=wcrc>>1^0XA001;//�Ƚ���������һλ��������Ķ���ʽ�������
			}
			else//�������1����ֱ���Ƴ�
			{
				wcrc>>=1;//ֱ���Ƴ�
			}
		}
    }
	return wcrc<<8|wcrc>>8;//�Ͱ�λ��ǰ���߰�λ�ں�
}




/* ��ӡ���� */
void hexdump(  
                char *title,  
                u8 *s,  
                int l)  
{  
#if 1
    int n = 0;  
  
    printf("%s", title);  
    for (; n < l; ++n) {  
        if ((n % 16) == 0) {  
                printf("\n%04x", n);  
        }  
        printf(" %02x", s[n]);  
    }  
  
    printf("\n");
#endif
}

void dump_data(unsigned char *buf, int len)
{

	hexdump("== data ==",  
                (char *)buf,  
                len);

}


