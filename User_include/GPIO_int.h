//############################################################
// FILE:  GPIO_int.h
// Created on: 2016��6��5��
// Author: XQ
// summary:  GPIO_int
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

#include "DSP2833x_Project.h"

#ifndef GPIO_int_H
#define GPIO_int_H
#define LED1_CLR  GpioDataRegs.GPACLEAR.bit.GPIO29=1
#define LED1_SET  GpioDataRegs.GPASET.bit.GPIO29=1
#define LED1_REV  GpioDataRegs.GPATOGGLE.bit.GPIO29=1
#define LED2_CLR  GpioDataRegs.GPACLEAR.bit.GPIO30=1
#define LED2_SET  GpioDataRegs.GPASET.bit.GPIO30=1
#define LED2_REV  GpioDataRegs.GPATOGGLE.bit.GPIO30=1


void Init_Gpio_LED(void);
void Init_3MotorGpio(void);
void Init_DACEPWMGpio(void);
void Init_FMQ_voice(void);
void InitScirs232bGpio(void);
void Init_KEY_switch(void);
void Init_LCD12864_Gpio(void);
void  Init_QEP_Gpio (void );
#endif  // end of GPIO_int_H definition

//===========================================================================
// End of file.
//===========================================================================
