#ifndef __LCD_Drv_h
#define __LCD_Drv_h
 void DrawString(u16 x, u16 y, u8 *pStr, u16 LineColor,u16 FillColor, u8 Mod); //����
 void DispSmallPic(u16 x, u16 y, u16 w, u16 h, const u8*str);	//ͼƬ
 void Color_transition(void); //ɫ��
 void DispOneColor(u16 Color);	//ȫ�����
 void LCD_Init(void);//��ʼ��
 void LCD_WR_REG(unsigned int index);//д�Ĵ���
 void LCD_WR_CMD(unsigned int index,unsigned int val); //д����
 void LCD_WR_Data(unsigned int val);//д����
 void SysTickDelay(u16 dly_ms);//1MS ʱ��
 extern const u8 LOGO[19530];
#endif 

