//############################################################
// FILE:  Task_function.h
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

#ifndef Task_function_H
#define Task_function_H
#include "DSP2833x_Project.h"

typedef struct {
	    Uint16    Control_Mode;  // ����ģʽ  VF=1    �˱��뿪��=2      �˱���FOC=3      ������=4
	    Uint16    TripFlagDMC;   //  ���� ������־
	    Uint16    drive_car;
	    Uint16    olddrive_car;
	    Uint16    clear_PWMtripz;
	    Uint16    Run_mode;
	    Uint16    Qiehuan_count;
	    Uint16    Start_order;
	   	 }logic;

#define  logic_DEFAULTS  {0,0,0,0,0,0,0,0}


void Timer_Dpie(void);
void knob_control(void);   // ��ť��λ������ �ٶ��ź�

#endif  // end of Task_function_H definition

//===========================================================================
// End of file.
//===========================================================================
