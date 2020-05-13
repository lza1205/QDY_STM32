
#include "all.h"


void qdy_system_init(void)
{
	init_sys_config();

	server_command_init();

	printf("欢迎使用 qd 系统\r\n");
	printf("qdy # ");
}


void qdy_process(void)
{
	process_uart_1_data();
	process_uart_5_data();
	process_timer_list();
}




/*ModBus 计算CRC码的步骤为：

(1).预置16位寄存器为FFFFH。称此寄存器为CRC寄存器；

(2).把第一个8位数据与CRC寄存器的低位相异或，把结果放于CRC寄存器；

(3).把寄存器的内容右移一位(朝低位)，用0填补最高位，检查最低位；

(4).如果最低位为0：重复第3步(再次移位)如果最低位为1：CRC寄存器与多项式A001（1010 0000 0000 0001）进行异或；

(5).重复步骤3和4，直到右移8次，这样整个8位数据全部进行了处理；

(6).重复步骤2到步骤5，进行下一个8位数据的处理；

(7).最后得到的CRC寄存器即为CRC码。(CRC码 = CRC_L +CRC_H)

*/

/*****************crc校验**********************************************/

//crc生成函数，并将crc存储在预先定于的数组中

//调用方式crc16（指向数据的指针，需要校验的数据长度）



u16 crc16(u8 *ptr,u8 len)
{
	unsigned long wcrc=0XFFFF;//预置16位crc寄存器，初值全部为1

	int i=0,j=0;//定义计数

	for(i=0;i<len;i++)//循环计算每个数据
    {

		wcrc^=*ptr++;//将八位数据与crc寄存器亦或.指针地址增加，指向下个数据

		for(j=0;j<8;j++)//循环计算数据的
		{
			if(wcrc&0X0001)//判断右移出的是不是1，如果是1则与多项式进行异或。
			{
				wcrc=wcrc>>1^0XA001;//先将数据右移一位再与上面的多项式进行异或
			}
			else//如果不是1，则直接移出
			{
				wcrc>>=1;//直接移出
			}
		}
    }
	return wcrc<<8|wcrc>>8;//低八位在前，高八位在后
}




/* 打印数据 */
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


