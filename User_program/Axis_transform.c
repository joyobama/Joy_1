//############################################################
// FILE:  Axis_transform.c
// Created on: 2016��8��11��
// Author: XQ
// summary:Axis_transform
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

#include "Axis_transform.h"

extern   CLARKE       ClarkeI;

void  CLARKE_Cale(p_CLARKE  pV)
{
	pV->Alpha = pV->As;
	pV->Beta = _IQmpy((pV->As +_IQmpy2(pV->Bs)),_IQ(0.57735026918963));
}

void  PARK_Cale(p_PARK pV)
{
	pV->Ds = _IQmpy(pV->Alpha,pV->Cosine) + _IQmpy(pV->Beta,pV->Sine);
    pV->Qs = _IQmpy(pV->Beta,pV->Cosine) - _IQmpy(pV->Alpha,pV->Sine);
}

void  IPARK_Cale(p_IPARK pV)   // pV->
{
	pV->Alpha = _IQmpy(pV->Ds,pV->Cosine) - _IQmpy(pV->Qs,pV->Sine);
	pV->Beta  = _IQmpy(pV->Qs,pV->Cosine) + _IQmpy(pV->Ds,pV->Sine);
}

//===========================================================================
// No more.
//===========================================================================

