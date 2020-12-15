//############################################################
// FILE:    Svpwm_dq.h
// Created on: 2016��2��2��
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

#ifndef  Svpwm_dq_H
#define  Svpwm_dq_H
#include "DSP2833x_Project.h"
#include "IQmathLib.h"

typedef struct 	{ _iq  Ualpha; 			// Input:   alpha-axis
				  _iq  Ubeta;			// Input:   beta-axis
				  _iq  Ta;				// Output:  phase-a
				  _iq  Tb;				// Output:  phase-b
				  _iq  Tc;				// Output:  phase-c
				  _iq  tmp1;			// Variable: temp
				  _iq  tmp2;			// Variable: temp
				  _iq  tmp3;			// Variable: temp
				  Uint16 VecSector;		// Space vector sector
				} SVPWM , *p_SVPWM ;


#define SVPWM_DEFAULTS  { 0,0,0,0,0,0,0,0,0}

void  SVPWM_Cale(p_SVPWM pV);

#endif /* Svpwm_dq*/
