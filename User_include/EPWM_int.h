//############################################################
// FILE:  ADC_int.h
// Created on: 2016��8��5��
// Author: XQ
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


#ifndef EPWM_int_H
#define EPWM_int_H
#include "DSP2833x_Project.h"

void EPWM3_int(void);
void HVDMC_Protection(void);
void  PWMDAC_int(void);
void  Svpwm_Outpwm(void);
void START_CAR(void);
void STOP_CAR(void);
#endif  // end of EPWM_int_H definition

//===========================================================================
// End of file.
//===========================================================================
