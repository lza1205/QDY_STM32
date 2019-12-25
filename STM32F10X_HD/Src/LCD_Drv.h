#ifndef __LCD_Drv_h
#define __LCD_Drv_h
 void DrawString(u16 x, u16 y, u8 *pStr, u16 LineColor,u16 FillColor, u8 Mod); //文字
 void DispSmallPic(u16 x, u16 y, u16 w, u16 h, const u8*str);	//图片
 void Color_transition(void); //色条
 void DispOneColor(u16 Color);	//全屏填充
 void LCD_Init(void);//初始化
 void LCD_WR_REG(unsigned int index);//写寄存器
 void LCD_WR_CMD(unsigned int index,unsigned int val); //写命令
 void LCD_WR_Data(unsigned int val);//写数据
 void SysTickDelay(u16 dly_ms);//1MS 时延
 extern const u8 LOGO[19530];
#endif 

