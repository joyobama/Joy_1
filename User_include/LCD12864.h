//############################################################
// FILE:  LCD122864.h
// Created on: 2016��3��5��
// Author: XY
// summary: Header file  and definition
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//��Ȩ���У�����ؾ�
//DSP/STM32������ƿ�����
//˶������
//��ַ: https://shuolidianzi.taobao.com
//�޸�����:2016/5/23
//�汾��V16.3-1
//Author-QQ: 616264123
//�������QQȺ��314306105
//############################################################

#ifndef LCD12864_H
#define LCD12864_H
#include "DSP2833x_Project.h"
extern unsigned char  DAT_IC1[32],DAT_IC2[32],DAT_IC3[32],DAT_IC4[32];


#define LCD_RS GpioDataRegs.GPCDAT.bit.GPIO66
#define LCD_RW GpioDataRegs.GPCDAT.bit.GPIO65
#define LCD_EN GpioDataRegs.GPCDAT.bit.GPIO64
#define LCD_REST GpioDataRegs.GPBDAT.bit.GPIO52
#define LCD_DATA GpioDataRegs.GPBDAT.all



//unsigned char LCD_DATAZHUHUAN(unsigned char Data);
//void LCD_write_command(unsigned char command);
//void LCD_write_data(unsigned char Data);
//void LCD12864_init(void);
//void  Lcd_ShowStr(unsigned char x,unsigned char y,unsigned char *adder);
//unsigned char LCD_Read(void);
//void LCD_Read_Buy(void);

void TransferData(unsigned char Data,unsigned char DI);
unsigned char Lcd_Read(void);
void Buy_Read(void);
void Show_Clr_All(void);
void Lcd_Clera(void);
void LCD12864_init(void);
void Lcd_ShowStr(unsigned char x,unsigned char y, unsigned char *adder);
void Lcd_ShowStr1(unsigned char x,unsigned char y,unsigned char *adder);
void Show_Point(unsigned char x,unsigned char y,unsigned char color);
void Show_Picture(unsigned char  *adder);
void Show_Byte(unsigned char x,unsigned char y,unsigned char Data,unsigned char ATunm);
void Show_Picture_Area(unsigned char x,unsigned char y,const unsigned char *Data,unsigned char W,unsigned char H);
void Show_Draw_Run(unsigned char x,unsigned char y,unsigned char y1,unsigned char H);
void Show_Clr_Area(unsigned char x,unsigned char y,unsigned char Data,unsigned char W,unsigned char H);
void StrCopyBTA(unsigned char *str1, unsigned char *str2,unsigned char a);
void sFormatLong(int lData, unsigned int uStyle,  unsigned char *pStr);


#endif



