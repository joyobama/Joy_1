//############################################################
// FILE:  KEY.h
// Created on: 2016��7��5��
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

#ifndef KEY_H
#define KEY_H
#include "DSP2833x_Project.h"


typedef struct {
	    Uint16   Key_num[5];
	    Uint16   KeyDataK;
	    Uint16   Key_count[5];
	    Uint16   Key_switch[5];
	   }KEY;

#define  KEY_DEFAULTS  {0,0,0,0}

void Key_Can(void);
void Key_Dispose(void);
void Show_disp(void);
#endif


