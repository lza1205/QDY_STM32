#include "stm32f10x.h"
#include "LCD_Drv.h"
#include "ascii hex(8x16).h"
#include "Hz_zimo.h"

#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ADDR
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ADDR

#define RED     0xf800
#define GREEN   0x07e0
#define BLUE    0x001f
#define WHITE   0xffff
#define BLACK   0x0000
#define YELLOW   0xFFE0

void LCD_RST(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
    SysTickDelay(4);					   
    GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 
	SysTickDelay(10);	
}

//写寄存器地址函数
void LCD_WR_REG(unsigned int index)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= index;
}

//写寄存器数据函数
void LCD_WR_CMD(unsigned int index,unsigned int val)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= index;	
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}

//写16位数据函数
void  LCD_WR_Data(unsigned int val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}

//读16位数据函数
unsigned int LCD_RD_data(void)
{
	unsigned int a=0;
	a=*(__IO uint16_t *) (Bank1_LCD_D); //L
	return(a);	
}


//初始化函数
void LCD_Init(void)
{
	LCD_RST();	 

	LCD_WR_CMD(0x00E5, 0x8000); 	 // Set the internal vcore voltage
	LCD_WR_CMD(0x0000, 0x0001); 	 // Start internal OSC.
	SysTickDelay(10);
	LCD_WR_CMD(0x0001, 0x0100);	 // set SS and SM bit
	LCD_WR_CMD(0x0002, 0x0700);	 // set 1 line inveLCD_RSion
	LCD_WR_CMD(0x0003, 0x1030);	 // set GRAM write direction and BGR=1.
	LCD_WR_CMD(0x0004, 0x0000);	 // Resize register

	LCD_WR_CMD(0x0008, 0x0202);	 // set the back porch and front porch
	LCD_WR_CMD(0x0009, 0x0000);	 // set non-display area refresh cycle ISC[3:0]
	LCD_WR_CMD(0x000A, 0x0000);	 // FMARK function
	LCD_WR_CMD(0x000C, 0x0000);		 // RGB interface setting
	LCD_WR_CMD(0x000D, 0x0000);	 // Frame marker Position
	LCD_WR_CMD(0x000F, 0x0000);		 // RGB interface polarity
	LCD_WR_CMD(0x002b, 0x0020);   //frame rate and color control(0x0000)

	//*************Power On sequence ****************
	LCD_WR_CMD(0x0010, 0x0000);		 // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WR_CMD(0x0011, 0x0004);		 // DC1[2:0], DC0[2:0], VC[2:0]
	LCD_WR_CMD(0x0012, 0x0000);		 // VREG1OUT voltage
	LCD_WR_CMD(0x0013, 0x0000);		 // VDV[4:0] for VCOM amplitude
	SysTickDelay(200);				// Dis-charge capacitor power voltage

	LCD_WR_CMD(0x0010, 0x17B0);		 // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WR_CMD(0x0011, 0x0001);		 // DC1[2:0], DC0[2:0], VC[2:0]
	SysTickDelay(50);					 // Delay 50ms
	LCD_WR_CMD(0x0012, 0x013e);		 // VREG1OUT voltage
	SysTickDelay(50);					 // Delay 50ms
	LCD_WR_CMD(0x0013, 0x1c00);		 // VDV[4:0] for VCOM amplitude
	LCD_WR_CMD(0x0029, 0x001e);		 // VCM[4:0] for VCOMH
	SysTickDelay(50);

	LCD_WR_CMD(0x0020, 0x0000);		 // GRAM horizontal Address
	LCD_WR_CMD(0x0021, 0x0000);		 // GRAM Vertical Address

	// ----------- Adjust the Gamma	Curve ----------//
	LCD_WR_CMD(0x0030, 0x0002);
	LCD_WR_CMD(0x0031, 0x0606);
	LCD_WR_CMD(0x0032, 0x0501);


	LCD_WR_CMD(0x0035, 0x0206);
	LCD_WR_CMD(0x0036, 0x0504);
	LCD_WR_CMD(0x0037, 0x0707);
	LCD_WR_CMD(0x0038, 0x0306);
	LCD_WR_CMD(0x0039, 0x0007);

	LCD_WR_CMD(0x003C, 0x0700);
	LCD_WR_CMD(0x003D, 0x0700);

	//------------------ Set GRAM area ---------------//
	LCD_WR_CMD(0x0050, 0x0000);		// Horizontal GRAM Start Address
	LCD_WR_CMD(0x0051, 0x00EF);		// Horizontal GRAM End Address
	LCD_WR_CMD(0x0052, 0x0000);		// Vertical GRAM Start Address
	LCD_WR_CMD(0x0053, 0x013F);		// Vertical GRAM Start Address


	//LCD_WR_CMD(0x0060, 0xA700);		// Gate Scan Line
	LCD_WR_CMD(0x0060, 0x2700);		// Gate Scan Line
	LCD_WR_CMD(0x0061, 0x0001);		// NDL,VLE, REV
	LCD_WR_CMD(0x006A, 0x0000);		// set scrolling line

	//-------------- Partial Display Control ---------//
	LCD_WR_CMD(0x0080, 0x0000);
	LCD_WR_CMD(0x0081, 0x0000);
	LCD_WR_CMD(0x0082, 0x0000);
	LCD_WR_CMD(0x0083, 0x0000);
	LCD_WR_CMD(0x0084, 0x0000);
	LCD_WR_CMD(0x0085, 0x0000);

	//-------------- Panel Control -------------------//
	LCD_WR_CMD(0x0090, 0x0010);
	LCD_WR_CMD(0x0092, 0x0000);
	LCD_WR_CMD(0x0093, 0x0003);
	LCD_WR_CMD(0x0095, 0x0110);
	LCD_WR_CMD(0x0097, 0x0000);
	LCD_WR_CMD(0x0098, 0x0000);


	LCD_WR_CMD(0x0007, 0x0173);		// 262K color and display ON
	LCD_WR_REG(0x0022);
	DispOneColor(0xffff);
	GPIO_ResetBits(GPIOE, GPIO_Pin_0); //开背光

}
/**************************************************************************************
* 名    称: DispOneColor
* 功    能: 全屏显示某种颜色
* 参    数: Color:颜色值
**************************************************************************************/
void DispOneColor(u16 Color)
{
    u8 i;
	u16 j;
    LCD_WR_CMD(0x0021,0);        //行首址0
    LCD_WR_CMD(0x0020,0);        //列首址0
    LCD_WR_REG(0x22);
    for(j=0;j<320;j++)
	{
        for(i=0;i<240;i++)
		{
			LCD_WR_Data(Color);
		}
	}
}
/**************************************************************************************
* 名    称: DispClear
* 功    能: 清除显示屏的显示内容 填充黑
* 参    数: 无
* 返 回 值: 无
**************************************************************************************/
void DispClear(void)
{
    DispOneColor(BLACK);
}
/**************************************************************************************
* 名    称: Set_ramaddr
* 功    能: 设置显示坐标
* 参    数: X轴 Y轴
* 返 回 值: 无
**************************************************************************************/
void Set_ramaddr(u16 x,u16 y)
{
    LCD_WR_CMD(0x0021,y);        //行首址
	LCD_WR_CMD(0x0020,x);        //列首址
}

/**************************************************************************************
* 名    称: DrawSingleAscii
* 功    能: 在指定的位置单个字符
* 参    数: x:x坐标  
*			y:y坐标                     
*           LineColor:字符的颜色
*           FillColor:字符背景颜色
*           Mod:是否透明
**************************************************************************************/
void DrawSingleAscii(u16 x, u16 y, u8 *pAscii, u16 LineColor,u16 FillColor,u8 Mod)
{
    u8 i, j;
    u8 str;
    u16 OffSet;

    OffSet = (*pAscii)*16;

    for (i=0;i<16;i++)
    {
        Set_ramaddr(x,y+i);
        LCD_WR_REG(0x22);
        str = *(AsciiLib + OffSet + i);  
        for (j=0;j<8;j++)
        {
            if ( str & (0x80>>j) )     //0x80>>j 滤出有效像素
            {
                LCD_WR_Data((u16)(LineColor&0xffff));
            }
            else
            {
                if (!Mod) 
                    LCD_WR_Data((u16)(FillColor&0xffff));
                else
                {
                    Set_ramaddr(x+j+1,y+i);
                    LCD_WR_REG(0x22);  
                }
            }               
        } 
    }
}
/**************************************************************************************
* 名    称: DrawSingleHz
* 功    能: 在指定的位置显示汉字
* 参    数: x:x坐标
*           y:y坐标
*           LineColor:汉字的颜色
*           FillColor:汉字背景颜色
*           Mod:是否透明
**************************************************************************************/

#define	HZ_column  16 //汉字字体大小
void DrawSingleHz(u16 x, u16 y, u16 Hz, u16 LineColor,u16 FillColor ,u8 Mod)
{
 u16 j=0,i=0,k=0;
 u16 str;

	/*在字库中查找*/
	for(j = 0;Hz_Code16[j].Hz_Index[0] != 0xff;j++)   
	    if(Hz==(Hz_Code16[j].Hz_Index[1]<<8|Hz_Code16[j].Hz_Index[0]))
		{
		  for (i=0;i<HZ_column;i++)
	        {
	            Set_ramaddr(x,y+i);
	            LCD_WR_REG(0x22);
	
	            str = Hz_Code16[j].Code[i*2]<<8|Hz_Code16[j].Code[i*2+1]; 
	
	            for (k=0;k<HZ_column;k++)
	            {
	                if ( str & (0x8000>>k) )     //0x8000>>k 滤出有效像素
	                {
	                    LCD_WR_Data((u16)(LineColor&0xffff));
	                }
	                else
	                {
	                    if (!Mod) 
	                        LCD_WR_Data((u16)(FillColor&0xffff));
	                    else
	                    {
	                        Set_ramaddr(x+k+1,y+i);
	                        LCD_WR_REG(0x22);  
	                    }
	                }               
	            } 
	        }
		}

}

/**************************************************************************************
* 名    称: DrawString
* 功    能: 在指定的位置显示多个字符
* 参    数:x: x坐标
*          y: y坐标
*          LineColor:字符的颜色
*          FillColor:字符背景颜色
*		   Mod:是否透明
**************************************************************************************/
void DrawString(u16 x, u16 y, u8 *pStr, u16 LineColor,u16 FillColor, u8 Mod)
{

    while(*pStr)
    {
        if (*pStr > 0x80)           //汉字
        {
            DrawSingleHz(x, y, *(u16*)pStr, LineColor, FillColor, Mod);
            x += HZ_column;
            pStr += 2;              
        }
        else                        //英文字符
        {
            DrawSingleAscii(x, y, pStr, LineColor, FillColor, Mod);
            x += 8;
            pStr += 1;              
        }
    }   
}

/**************************************************************************************
* 名    称: DispNum
* 功    能: 在指定的位置显示4位数字
* 参    数:x: x坐标
*          y: y坐标
*          num:需显示数值
**************************************************************************************/
void DispNum(u16 x, u16 y, u16 num)
{
    unsigned char str[5];

    str[0] = num/1000+0x30;
    str[1] = (num%1000)/100+0x30;
    str[2] = (num%1000)%100/10+0x30;
    str[3] = (num%1000)%100%10+0x30;
    str[4] = '\0';

    DrawString(x, y, str, RED, YELLOW, 0);
}
/**************************************************************************************
* 名    称: Color_transition
* 功    能: 显示过度色条
**************************************************************************************/
void Color_transition(void)
{
 	u16 R_data=0,G_data=0,B_data=0;
	u16 i=0,j=0; 
	Set_ramaddr(0,200);
	LCD_WR_REG(0x22);
 	R_data=0;G_data=0;B_data=0;  	
    for(j=0;j<20;j++)//红色渐强条
	{
        for(i=0;i<240;i++)
            {R_data=i/8;LCD_WR_Data(R_data<<11|G_data<<5|B_data);}
	}
    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<20;j++)
	{
        for(i=0;i<240;i++)
            {
			G_data=0x3f-(i/4);
			B_data=0x1f-(i/8);
			LCD_WR_Data(R_data<<11|G_data<<5|B_data);}
	}

	R_data=0;G_data=0;B_data=0;
    for(j=0;j<20;j++)//绿色渐强条
	{
        for(i=0;i<240;i++)
            {G_data=i/4;LCD_WR_Data(R_data<<11|G_data<<5|B_data);}
	}
    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<20;j++)
	{
        for(i=0;i<240;i++)
            {
			R_data=0x1f-(i/8);
			B_data=0x1f-(i/8);
			LCD_WR_Data(R_data<<11|G_data<<5|B_data);}
	}

	R_data=0;G_data=0;B_data=0;
    for(j=0;j<20;j++)//蓝色渐强条
	{
        for(i=0;i<240;i++)
            {B_data=i/8;LCD_WR_Data(R_data<<11|G_data<<5|B_data);}
	} 
	B_data=0; 
    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<20;j++)
	{
        for(i=0;i<240;i++)
            {
			G_data=0x3f-(i/4);
			R_data=0x1f-(i/8);
			LCD_WR_Data(R_data<<11|G_data<<5|B_data);}
	}
}

 /**************************************************************************************
* 名    称: DispSmallPic
* 功    能: 在指定的位置显示一张65K色的图片
* 参    数: str: 图片指针
**************************************************************************************/
void DispSmallPic(u16 x, u16 y, u16 w, u16 h, const u8*str)
{
    u16 i,j;
    for(j=0;j<h;j++)
    {
        Set_ramaddr(x,y+j);
        LCD_WR_REG(0x22); 
        for(i=0;i<w;i++)
        {   
			LCD_WR_Data(*(u16 *)(&str[(j*w+i)*2]));       	  //低位在前
        }
    }
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
