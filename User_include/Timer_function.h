//############################################################
// FILE:  Timer_function.h
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

#include "DSP2833x_Device.h"

#ifndef Timer_function_H
#define Timer_function_H

typedef struct {
	    Uint16   pwmisr_conut;
	    Uint16   Tim2ms_flag ;
	    Uint16   Tim50ms_count;
        Uint16   IntClock_50ms;
        Uint16   Tim50ms_flag;
        Uint16   Tim100ms_count;
        Uint16   Tim100ms_flag;
        Uint16   Tim200ms_count;
        Uint16   Tim200ms_flag;
        Uint16   Tim1s_count;
        Uint16   Tim1s_flag ;
        Uint16   Tim1min_count;
        Uint16   Tim1min_flag ;
	   }TaskTime;

#define  TaskTime_DEFAULTS  {0,0,0,0,0,0,0,0,0,0,0}
 
void RunSystimer(void);
void CLEAR_flag(void);

#endif  // end of Timer_function_H definition

//===========================================================================
// End of file.
//===========================================================================
