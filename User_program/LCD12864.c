//############################################################
// FILE:  LCD12864.c
// Created on: 2016��4��11��
// Author: XY
// summary:LCD12864
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

#include "LCD12864.h"
#include "GPIO_int.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned char Str_Length=0,y1old=0;

//**********************************************************//
//����
//**********************************************************//
const unsigned char DrawR[]={
0xFF,0x99,0xBD,0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0xFF,0xBD,0x99,0xFF
};



unsigned char LCD_DATAZHUHUAN(unsigned char DData)
{unsigned char ui=0;
	ui=(DData&0x01)<<7;
	ui|=(DData&0x02)<<5;
	ui|=(DData&0x04)<<3;
	ui|=(DData&0x08)<<1;
	ui|=(DData&0x10)>>1;
	ui|=(DData&0x20)>>3;
	ui|=(DData&0x40)>>5;
	ui|=(DData&0x80)>>7;
	return(ui);
}

unsigned char LCD_Read(void)
{   unsigned char Data=0;
	EALLOW;
	/***************LCD_D0*********************/
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO61 = 0;
	GpioCtrlRegs.GPBPUD.bit.GPIO61=0;
	GpioDataRegs.GPBCLEAR.bit.GPIO61=1;
	/***************LCD_D1*********************/
	GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO60 = 0;
	GpioCtrlRegs.GPBPUD.bit.GPIO60=0;
	GpioDataRegs.GPBCLEAR.bit.GPIO60=1;
	/***************LCD_D2*********************/
	GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO59 = 0;
	GpioCtrlRegs.GPBPUD.bit.GPIO59=0;
	GpioDataRegs.GPBCLEAR.bit.GPIO59=1;
	/***************LCD_D3*********************/
	GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;
	GpioCtrlRegs.GPBPUD.bit.GPIO58=0;
	GpioDataRegs.GPBCLEAR.bit.GPIO58=1;
	/***************LCD_D4*********************/
	GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO57 = 0;
	GpioCtrlRegs.GPBPUD.bit.GPIO57=0;
	GpioDataRegs.GPBCLEAR.bit.GPIO57=1;
	/***************LCD_D5*********************/
	GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO56 = 0;
	GpioCtrlRegs.GPBPUD.bit.GPIO56=0;
	GpioDataRegs.GPBCLEAR.bit.GPIO56=1;
	/***************LCD_D6*********************/
	GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO55 = 0;
	GpioCtrlRegs.GPBPUD.bit.GPIO55=0;
	GpioDataRegs.GPBCLEAR.bit.GPIO55=1;
	/***************LCD_D7*********************/
	GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO54 = 0;
	GpioCtrlRegs.GPBPUD.bit.GPIO54=0;
	GpioDataRegs.GPBCLEAR.bit.GPIO54=1;
	EDIS;
	DELAY_US(50);
	Data=GpioDataRegs.GPBDAT.bit.GPIO54<<7;
	DELAY_US(50);
	Data|=GpioDataRegs.GPBDAT.bit.GPIO55<<6;
	DELAY_US(50);
	Data|=GpioDataRegs.GPBDAT.bit.GPIO56<<5;
	DELAY_US(50);
	Data|=GpioDataRegs.GPBDAT.bit.GPIO57<<4;
	DELAY_US(50);
	Data|=GpioDataRegs.GPBDAT.bit.GPIO58<<3;
	DELAY_US(50);
	Data|=GpioDataRegs.GPBDAT.bit.GPIO59<<2;
	DELAY_US(50);
	Data|=GpioDataRegs.GPBDAT.bit.GPIO60<<1;
	DELAY_US(50);
	Data|=GpioDataRegs.GPBDAT.bit.GPIO61;
	DELAY_US(50);
	return(Data);
}

//*****************************************************//
//��LCDд˵ָ���д����******��������/ָ��
//��DI=0,����ָ��,��DI=1,��������
//*****************************************************//
void TransferData(unsigned char Data,unsigned char DI)
{
	    unsigned long Bi,Di;
	  	LCD_RW=0;         //д
	  	DELAY_US(100);
	  	if(DI==0) LCD_RS=0;  //ָ��
	  	else if(DI==1) LCD_RS=1; //����
	  	DELAY_US(100);
	  	LCD_EN=1;         //����
	  	DELAY_US(100);
	  	LCD_DATA&=~0X3FC00000;
	  	Bi=LCD_DATAZHUHUAN(Data);
	    Di=Bi<<22;
	    LCD_DATA|=Di;
	  	DELAY_US(100);
	  	LCD_EN=0;
	  	DELAY_US(100);
	  	LCD_RW=1;

}
//-----------------------------------------------------//
//��ȡLCD�ϵ�����
//----------------------------------------------------//
unsigned char Lcd_Read(void)
{
	unsigned char Data;
	LCD_RS=0;         //ָ��
	LCD_RW=1;         //��
	LCD_EN=1;         //����
	Data=0xff;
	DELAY_US(100);
	Data=LCD_Read();
	DELAY_US(100);
	LCD_EN=0;         //��ֹ
	Init_LCD12864_Gpio();
	return (Data);
}
//-----------------------------------------------------//
//��ȡLCD�ϵ�æλ
//----------------------------------------------------//
void Buy_Read(void)
{	unsigned char Data;
	LCD_RS=0;         //ָ��
	LCD_RW=1;         //��
	LCD_EN=1;         //����
	Data=0xff;
	DELAY_US(100);
	Data=LCD_Read();
	DELAY_US(100);
	while((Data & 0x80)==0x80);
	LCD_EN=0;         //��ֹ
	Init_LCD12864_Gpio();
}


//****************************************************************************//
//ȫ����� ���GDRAM
//****************************************************************************//
void  Show_Clr_All(void)
{	unsigned int i,j;
	TransferData(0x34,0);     //��չָ������
	TransferData(0x36,0);     //��չָ������
	for(i=0;i<64;i++)
	{	j=8*(i/32);
		TransferData(0x80+(i&0x1f),0);      //�趨�е�ַ(y����)
		TransferData(0x80+j,0);      //�趨�е�ַ(y����)
		for(j=0;j<8;j++)
		{
		TransferData(0x00 ,1);
		TransferData(0x00 ,1);
		}

	}
	TransferData(0x30,0);          //�ָ�������ָ�   */
}
//****************************************************************************//
//****************************************************************************//

//*****************************************************//
//LCD��������
//*****************************************************//
void  Lcd_Clera(void)
{
	unsigned char i;
	TransferData(0x80,0);
	for(i=0;i<64;i++)
	{	TransferData(0x20,1);
	}
}
//*****************************************************//
//LCD���ֿ��ʼ��
//*****************************************************//
void LCD12864_init(void)   //   LCD12864_init  Lcd_Init
{   LCD_REST=0;
	DELAY_US(50);//�ӳ�100ms
	LCD_REST=1;
	DELAY_US(50);
	TransferData(0x30,0);  //�����趨:RE=0:������ָ�,G=0 :�ر�ͼ����ʾ
	DELAY_US(20);
	TransferData(0x30,0);  //�ж��Ƿ����óɹ�
	DELAY_US(20);
	TransferData(0x08,0);  //������ʾ
	DELAY_US(20);
	TransferData(0x10,0);  //�������
	DELAY_US(20);
	TransferData(0x0C,0);  //��ʾ��
	DELAY_US(20);
	TransferData(0x01,0);  //����
	DELAY_US(20);
	TransferData(0x06,0);  //�������,�����������1λ�ƶ�
	DELAY_US(20);
}


//*****************************************************//
//LCD��ʾ����
//*****************************************************//
void Lcd_ShowStr1(unsigned char x,unsigned char y,unsigned char *adder)	 //������ʾ�ַ�
{	unsigned char i=0;
	if(x>16) {x=16;}
	else if(0<x<16) { }
	else if(x<=0) {x=0; }
	if(y>48) {y=48;}
	else if(0<y<48) { }
	else if(y<=0) {y=0;}
	if(y==48)  TransferData(0x80+x,0);  //����DDRAM��ʼ��ַ
	else if(y==32)  TransferData(0x90+x,0);  //����DDRAM��ʼ��ַ
	else if(y==16)  TransferData(0x88+x,0);  //����DDRAM��ʼ��ַ
	else if(y==0)  TransferData(0x98+x,0);  //����DDRAM��ʼ��ַ
	for(i=x;i<=15-x;i++)   //while(adder[j]!='\0')   //
	{
		TransferData(*adder,1);   //��������
	   	adder++;

	}
}

void Lcd_ShowStr(unsigned char x,unsigned char y,unsigned char *adder)
{	unsigned char i,j=0;
	switch(y)
	{	case 48:  i=0x80+x;
			break;
		case 32: i=0x90+x;
			break;
		case 16: i=0x88+x;
			break;
		case 0: i=0x98+x;
			break;
		default:
			break;
	}
	TransferData(i,0);
	while(adder[j]!='\0')
	{	TransferData(adder[j],1);   //��������
		j++;
	}
}
//****************************************************************************//
//****************************************************************************//


//****************************************************************************//
//LCD���   xΪ�������� yΪ��������
//color=1Ϊ�õ����1    color=0 Ϊ�õ����0
//*****************************************************//
void Show_Point(unsigned char x,unsigned char y,unsigned char color)
{	unsigned char x_Dyte,x_Bit;    //�����е�ַ���ֽڣ������ֽ��е���1λ
	unsigned char y_Dyte,y_Bit;    //������Ϊ����������(ȡֵΪ0��1)���е�ַ(ȡֵΪ0~31)
	unsigned char GDRAM_Hbit,GDRAM_Lbit;
	TransferData(0x36,0);     //��չָ������
	x_Dyte=x/16;        //������16���ֽ��е���һ��
	x_Bit=x&0x0f;        //�����ڸ��ֽ��е���һλ
	y_Dyte=y/32;        //0Ϊ�ϰ�����1Ϊ�°���
	y_Bit=y&0x1f;        //������0~31���е���һ��
	TransferData(0x80+y_Bit,0);      //�趨�е�ַ(y����)
	TransferData(0x80+x_Dyte+8*y_Dyte,0);    //�趨�е�ַ(x����)����ͨ��8*y_Dyteѡ��������
	Lcd_Read();         //Ԥ��ȡ����
	GDRAM_Hbit=Lcd_Read();      //��ȡ��ǰ��ʾ��8λ����
	GDRAM_Lbit=Lcd_Read();      //��ȡ��ǰ��ʾ��8λ����
	DELAY_US(1);
	TransferData(0x80+y_Bit,0);      //�趨�е�ַ(y����)
	TransferData(0x80+x_Dyte+8*y_Dyte,0);    //�趨�е�ַ(x����)����ͨ��8*y_Dyteѡ��������
	if(x_Bit<8)          //�ж����ڸ�8λ�������ڵ�8λ
	{
  		if(color==1)
  		{
   			TransferData(GDRAM_Hbit | (0x01<<(7-x_Bit)),1); //��λGDRAM����8λ��������Ӧ�ĵ�
  		}
  		else
   			TransferData(GDRAM_Hbit & (~(0x01<<(7-x_Bit))),1); //���GDRAM����8λ��������Ӧ�ĵ�

  			TransferData(GDRAM_Lbit,1);       //��ʾGDRAM����8λ����
	}
	else
	{	TransferData(GDRAM_Hbit,1);
  		if(color==1)
   			TransferData(GDRAM_Lbit|(0x01<<(15-x_Bit)),1); //��λGDRAM����8λ��������Ӧ�ĵ�
  		else
   			TransferData(GDRAM_Lbit & (~(0x01<<(15-x_Bit))),1);//���GDRAM����8λ��������Ӧ�ĵ�

	}
	TransferData(0x30,0);          //�ָ�������ָ�
}
//****************************************************************************//
//****************************************************************************//


//*******************************************************//
//LCD��ʾͼƬˢ��(������)
//*******************************************************//
void Show_Picture(unsigned char  *adder)
//void Show_Picture(void)
{   unsigned char i,j;
////******��ʾ�ϰ���Ļ********************//
 	TransferData(0x36,0);  //Extended Function Set RE=1: extended instruction
    //delay_us(10);
    for(i=0;i<32;i++)              //
    {
      TransferData((0x80 + i),0); //SET  ��ֱ��ַ VERTICAL ADD
      TransferData(0x80,0);       //SET  ˮƽ��ַ HORIZONTAL ADD
      for(j=0;j<16;j++)
       {
         TransferData(*adder,1);
		 //TransferData(0XFF,1);
         adder++;
       }
    }
//********��ʾ�°���Ļ*****************//
   for(i=0;i<32;i++)              //
    {
      TransferData((0x80 + i),0); //SET ��ֱ��ַ VERTICAL ADD
      TransferData(0x88,0);       //SET ˮƽ��ַ HORIZONTAL ADD
      for(j=0;j<16;j++)
       {	//TransferData(0XFF,1);
         TransferData(*adder,1);
         adder++;
       }
    }
	TransferData(0x30,0);  //Extended Function Set RE=1: extended instruction
}
//****************************************************************************//
//****************************************************************************//


//****************************************************************************//
//LCDдһ���ֽ�   xΪ�������� yΪ��������
//Data Ϊ8λ����
//ATunm����   1λ��ȡ��ǰ��λ�����ڻ�Ҫд������
//*****************************************************//
void Show_Byte(unsigned char x,unsigned char y,unsigned char Data,unsigned char ATunm)
{	unsigned char x_Dyte,x_Bit;    //�����е�ַ���ֽڣ������ֽ��е���1λ
	unsigned char y_Dyte,y_Bit;    //������Ϊ����������(ȡֵΪ0��1)���е�ַ(ȡֵΪ0~31)
	unsigned char GDRAM_Hbit,GDRAM_Lbit;
	TransferData(0x36,0);     //��չָ������
	x_Dyte=x/16;        //������16���ֽ��е���һ��
	x_Bit=x&0x0F;        //�����ڸ��ֽ��е���һλ
	y_Dyte=y/32;        //0Ϊ�ϰ�����1Ϊ�°���
	y_Bit=y&0x1f;        //������0~16���е���һ��
	TransferData(0x80+y_Bit,0);      //�趨�е�ַ(y����)
	TransferData(0x80+x_Dyte+8*y_Dyte,0);    //�趨�е�ַ(x����)����ͨ��8*y_Dyteѡ��������
	Lcd_Read();         //Ԥ��ȡ����
	GDRAM_Hbit=Lcd_Read();      //��ȡ��ǰ��ʾ��8λ����
	GDRAM_Lbit=Lcd_Read();      //��ȡ��ǰ��ʾ��8λ����
	//delay_us(1);
	TransferData(0x80+y_Bit,0);      //�趨�е�ַ(y����)
	TransferData(0x80+x_Dyte+8*y_Dyte,0);    //�趨�е�ַ(x����)����ͨ��8*y_Dyteѡ��������
	if(x_Bit<8)          //�ж����ڸ�8λ�������ڵ�
   	{
		if(ATunm & 0x01)
		{	TransferData(GDRAM_Hbit |Data ,1); //��λGDRAM����8λ��������Ӧ�ĵ�
		}
		else
		{	TransferData(Data ,1); //��λGDRAM����8λ��������Ӧ�ĵ�
		}
  		TransferData(GDRAM_Lbit,1);       //��ʾGDRAM����8λ����
	}
	else
	{	TransferData(GDRAM_Hbit,1); //��λGDRAM����8λ��������Ӧ�ĵ�
		if(ATunm & 0x01)
		{	TransferData(GDRAM_Lbit | Data,1);     //��ʾGDRAM����8λ����
		}
		else
		{	TransferData(Data ,1); //��λGDRAM����8λ��������Ӧ�ĵ�
		}
	 }
	TransferData(0x30,0);          //�ָ�������ָ�
}
//****************************************************************************//
//****************************************************************************//


void  Show_Picture_Area(unsigned char x,unsigned char y,const unsigned char *Data,unsigned char W,unsigned char H)
{   unsigned char i,j;
	unsigned char x_Dyte,x_Bit;    //�����е�ַ���ֽڣ������ֽ��е���1λ
	unsigned char y_Dyte,y_Bit;    //������Ϊ����������(ȡֵΪ0��1)���е�ַ(ȡֵΪ0~31)
	volatile unsigned char GDRAM_Hbi=0,GDRAM_Lbi=0;
	if(x>127) return;
	if(y>63) return;
	W=(W+7)/8;
	TransferData(0x36,0);     //��չָ������
	for(i=0;i<H;i++)
	{	x_Dyte=x/16;        //������16���ֽ��е���һ��
		x_Bit=x&0x0F;        //�����ڸ��ֽ��е���һλ
		y_Dyte=y/32;        //0Ϊ�ϰ�����1Ϊ�°���
		y_Bit=y&0x1f;        //������0~16���е���һ��
		TransferData(0x80+y_Bit,0);      //�趨�е�ַ(y����)
		TransferData(0x80+x_Dyte+8*y_Dyte,0);    //�趨�е�ַ(x����)����ͨ��8*y_Dyteѡ��������
		Lcd_Read();         //Ԥ��ȡ����
		GDRAM_Hbi=Lcd_Read();      //��ȡ��ǰ��ʾ��8λ����
		GDRAM_Lbi=Lcd_Read();      //��ȡ��ǰ��ʾ��8λ����
		TransferData(0x80+y_Bit,0);      //�趨�е�ַ(y����)
		TransferData(0x80+x_Dyte+8*y_Dyte,0);    //�趨�е�ַ(x����)����ͨ��8*y_Dyteѡ��������
		if(x_Bit<8)          //�ж����ڸ�8λ�������ڵ�
   		{	for(j=0;j<W;j++)
			{	TransferData(*Data,1); //��λGDRAM����8λ��������Ӧ�ĵ�
				Data++;
			}
		}
		else
		{	TransferData(GDRAM_Hbi,1); //��λGDRAM����8λ��������Ӧ�ĵ�
			for(j=0;j<W;j++)
			{	TransferData(*Data ,1); //��λGDRAM����8λ��������Ӧ�ĵ�
				Data++;
			}
		 }
		 y++;
	}
	TransferData(0x30,0);          //�ָ�������ָ�
}
//****************************************************************************//
//****************************************************************************//


//*****************����*****************************************************
//****************************************************************************
//����˵���� �xx yָ����ʾ�������ʼ������
//           // dat	Ҫ�����ʾ��ͼ�λ��ֵ������顣
//            y1 �ǻ����������
//            HҪ����ĸ߶�
//         // ATunm����//unsigned char W,unsigned char H,
//****************************************************************************//
void  Show_Draw_Run(unsigned char x,unsigned char y,unsigned char y1,unsigned char H)
{	unsigned char i,j,Data;

	if(y1==y1old)
	{	for(j=0;j<64;j++)
		{	Data=DrawR[j];
			Show_Byte(x,y,Data,0x01);
			y++;
		}
	}
	else
	{	for(j=0;j<64;j++)
		{	Data=DrawR[j];
			Show_Byte(x,y,Data,0x00);
			y++;
		}
	}
	y1old=y1;
	for(i=0;i<H;i++)//����д������ҪС������߶�
	{   Show_Byte(x,y1,0xff,0x01);
		y1++;
	}
}
//****************************************************************************//
//****************************************************************************//


//****************************************************************************//
//������� ���GDRAM
//          x��yָ������������ʼ������
//          dat	Ҫ�����ʾ������
//          W	����ĳ���
//          H	����ĸ߶�
//****************************************************************************//
void  Show_Clr_Area(unsigned char x,unsigned char y,unsigned char Data,unsigned char W,unsigned char H)
{	unsigned char i,j;
	unsigned char x_Dyte,x_Bit;    //�����е�ַ���ֽڣ������ֽ��е���1λ
	unsigned char y_Dyte,y_Bit;    //������Ϊ����������(ȡֵΪ0��1)���е�ַ(ȡֵΪ0~31)
	volatile unsigned char GDRAM_Hb=0,GDRAM_Lb=0;
	TransferData(0x36,0);     //��չָ������
	if(x>127) return;
	if(y>63) return;
	W=(W+7)/8;
	for(i=0;i<H;i++)
	{
		x_Dyte=x/16;        //������16���ֽ��е���һ��
		x_Bit=x&0x0F;        //�����ڸ��ֽ��е���һλ
		y_Dyte=y/32;        //0Ϊ�ϰ�����1Ϊ�°���
		y_Bit=y&0x1f;        //������0~16���е���һ��
		TransferData(0x80+y_Bit,0);      //�趨�е�ַ(y����)
		TransferData(0x80+x_Dyte+8*y_Dyte,0);    //�趨�е�ַ(x����)����ͨ��8*y_Dyteѡ��������
		Lcd_Read();         //Ԥ��ȡ����
		GDRAM_Hb=Lcd_Read();      //��ȡ��ǰ��ʾ��8λ����
		GDRAM_Lb=Lcd_Read();      //��ȡ��ǰ��ʾ��8λ����

		TransferData(0x80+y_Bit,0);      //�趨�е�ַ(y����)
		TransferData(0x80+x_Dyte+8*y_Dyte,0);    //�趨�е�ַ(x����)����ͨ��8*y_Dyteѡ��������
		if(x_Bit<8)          //�ж����ڸ�8λ�������ڵ�
   		{	for(j=0;j<W;j++)
			{	TransferData(Data ,1); //��λGDRAM��8λ��������Ӧ�ĵ�
			}
		}
		else
		{	TransferData(GDRAM_Hb,1);     //��ʾGDRAM����8λ����
			for(j=0;j<W;j++)
			{	TransferData(Data ,1);
			}
		}
		y++;
	}
	TransferData(0x30,0);          //�ָ�������ָ�   */
}
//****************************************************************************//
//****************************************************************************//




//****************************************************************************//
//****************************************************************************//
void StrCopyBTA( unsigned char *str1, unsigned char *str2, unsigned char a)
{ unsigned char b;
	for(b=0;b<a;b++)
	{	str1[b]=str2[b];
		if(str2[b]==0) return;
	}
}
/*********************************************
 �������ܣ� ��ʽ��һ�������͵��ַ���
 ��ڲ����� uStyle.3-uStyle.0: �������λ��(������С����)
 			uStyle.7-uStyle.4: ��ʾС����λ��,ȫ�㲻��ʾС����
 			uStyle.15=0:����뷽ʽ, =1:�Ҷ��뷽ʽ
 ���ڲ�����
 ��    ע:  ��������λ��:���ʵ������λ�����ڶ��������λ��,��ʵ�ʵķ���
                ���ʵ�ʵ�����λ��С�ڶ��������λ��,�򲻹�����뻹���Ҷ���,�����ո�
**********************************************/

void utoa( char *DStr,int DATA,unsigned char N)
{   int ia=0,ib=0,ic=0,im=0;
    int id=0;
    if(DATA>=10000)     {im=5;ib=10000;}
    else if(DATA>=1000) {im=4;ib=1000;}
    else if(DATA>=100) {im=3;ib=100;}
    else if(DATA>=10)  {im=2;ib=10;}
    else if(DATA>=1)   {im=1;ib=1;}
    else  {im=0;ib=0;}

    if(im!=0)
    {   for(ia=0;ia<im;ia++)
        {   id=DATA/ib;
            DStr[ic++]=id+'0';
            DATA=DATA%ib;
            ib=ib/10;
        }
    }
    else
    {
        DStr[ic++]='0';
    }
    DStr[ic]='\0';
}

/*
unsigned char strlenle( char string[])
{	unsigned char i=0;
	while(string[i]!='\0') i++;
	return i;
}*/
void strcpyy( unsigned char *strDest, const  char *strSrc)
{  /* if ((strDest == NULL) || (strSrc == NULL))
	return NULL ;
	if(strDest==strSrc)
	return strDest ;
	unsigned char *tempptr = strDest ;
	while( (*strDest++ = *strSrc++) !='\0');
	return tempptr ;*/
	unsigned char i=0;
	while(strSrc[i]!='\0')
	{
		strDest[i]=(unsigned char)strSrc[i];
		i++;
	}
}

/*********************************************
 �������ܣ� ��ʽ��һ�������͵��ַ���
 ��ڲ�����   uStyle.3-uStyle.0: �������λ��(������С����)
        uStyle.7-uStyle.4: ��ʾС����λ��,ȫ�㲻��ʾС����
        uStyle.15=0:����뷽ʽ, =1:�Ҷ��뷽ʽ
 ���ڲ�����
 ��    ע:  ��������λ��:���ʵ������λ�����ڶ��������λ��,��ʵ�ʵķ���
                ���ʵ�ʵ�����λ��С�ڶ��������λ��,�򲻹�����뻹���Ҷ���,�����ո�
**********************************************/
void sFormatLong(int lData, unsigned int uStyle,  unsigned char *pStr)
{   char pTemp[5];
	char i, j, k, iStrLen, iDataLen, iPointLen;
	pStr[0]=0;								// ���ַ����ÿ�
	utoa(pTemp,lData,5);// ������ת��Ϊ�ַ���
	iStrLen=strlen(pTemp);
	iDataLen = uStyle&0x000f;
	iPointLen = (uStyle&0x00f0)>>4;
											// ������ݳ��Ȼ���ʾС����λ�������򲻴���
	if((iDataLen>9) || (iPointLen>8))  return;

	if(iPointLen==0)
	{
		if(uStyle & 0x8000)					// ��С�����Ҷ���
		{
			if(iDataLen > iStrLen)
			{								// ������λ������ʵ��λ��ʱ��߲��ո�
				for(i=0; i<(iDataLen-iStrLen); i++)	pStr[i]=0x20;
				strcpyy(pStr+iDataLen-iStrLen, pTemp);

			}
			else
			{  ;  }
			   strcpyy(pStr, pTemp);		// ������λ��С��ʵ��λ��ʱֱ�ӿ����ַ���
		}
		else
		{									// ��С���������
		    strcpyy(pStr, pTemp);			// �ȿ����ַ���
			if(iDataLen > iStrLen)			// ������λ������ʵ��λ��ʱ�ұ߲��ո�
			{
				for(i=iStrLen; i<iDataLen; i++) pStr[i]=0x20;
				pStr[i]=0;
			}
		}
	}
	else
	{
		if((uStyle & 0x8000)==0)				// �����, ��ʾС����
		{
			if(iPointLen >= iStrLen)
			{									// ���С��λ�����ڻ����ʵ������,�ȷ���"0."
				pStr[0]='0'; pStr[1]='.';		// ����С������"0"
				for(i=2; i<(2+iPointLen-iStrLen); i++) pStr[i]='0';
				strcpyy(pStr+i, pTemp);			// ����ʵ������
				i += iStrLen;
				for(; i<iDataLen+1; i++)  pStr[i]=0x20;  // �ұ߲��ո�
				pStr[i]=0;
			}
			else								// С����λ��С��ʵ������,�����
			{									// �ȷ���С����ǰ����
				for(i=0; i<iStrLen-iPointLen; i++)  pStr[i]=pTemp[i];
				pStr[i++]='.';					// ����С����
				for(; i<iStrLen+1; i++)	pStr[i]=pTemp[i-1];	// ����С��������
				for(; i<iDataLen+1; i++) pStr[i]=0x20;		// �ұ߲��ո�
				pStr[i]=0;
			}
		}
		else									// �Ҷ���, ��ʾС����
		{
			if(iPointLen >= iStrLen)			// ���С��λ�����ڵ���ʵ������
			{
				i=0;
				if(iDataLen > iPointLen+1)		// ���iDataLen����С��λ��+1,����߲��ո�
				for(i=0; i< (iDataLen-(iPointLen+1)); i++) pStr[i]=0x20;
				pStr[i++]='0';					// ����"0."
				pStr[i++]='.';
				j=i;							// ����С�����,ʵ����ǰ��"0"
				for(; i<(j+iPointLen-iStrLen); i++) pStr[i]='0';
				strcpyy(pStr+i, pTemp);			// ����ʵ������
			}
			else								// ���С��λ��С��ʵ������
			{
				i=0;
				if(iDataLen > iStrLen)			// ��߲��ո�
					for(i=0; i< (iDataLen-iStrLen); i++) pStr[i]=0x20;
				j=i; k=0;						// ����С����ǰ����
				for(; i<(j+iStrLen-iPointLen); i++, k++) pStr[i]=pTemp[k];
				pStr[i++]='.';					// ����С����
				j=i;							// ����С��������
				for(; i<(j+iPointLen); i++, k++) pStr[i]=pTemp[k];
				pStr[i]=0;
			}
		}
	}
	return;
}

//===========================================================================
// No more.
//===========================================================================
