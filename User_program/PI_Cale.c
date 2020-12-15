 //############################################################
// FILE:  PI_Cale.c
// Created on: 2016��8��4��
// Author: XQ
// summary: PI_Cale
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

#include "PI_Cale.h"

extern  PI_Control   pi_spd ;
extern  PI_Control   pi_id  ;
extern  PI_Control   pi_iq  ;


void  PI_Controller(p_PI_Control  pV)
{
    /* proportional term */
	pV->up = pV->Ref - pV->Fbk;

	/* integral term */
	pV->ui = (pV->Out == pV->v1)?(_IQmpy(pV->Ki, pV->up)+ pV->i1) : pV->i1;
	pV->i1 = pV->ui;

	/* control output */
	pV->v1 = _IQmpy(pV->Kp, (pV->up )) + pV->ui;
	pV->Out= _IQsat(pV->v1, pV->Umax, pV->Umin);
}

void  PI_Pare_init(void )
{
  pi_spd.Kp=_IQ(0.22);
  pi_spd.Ki=_IQ(0.00097);  // 0.0001*10 / 0.2   T*SpeedLoopPrescaler/0.2
  pi_spd.Umax =_IQ(0.85);
  pi_spd.Umin =_IQ(0.0);

  pi_id.Kp=_IQ(0.025);  //
  pi_id.Ki=_IQ(0.00048);  //
  pi_id.Umax =_IQ(0.1);
  pi_id.Umin =_IQ(-0.1);

  pi_iq.Kp=_IQ(0.028);
  pi_iq.Ki=_IQ(0.00056);
  pi_iq.Umax =_IQ(0.85);
  pi_iq.Umin =_IQ(0.0);
 }

//===========================================================================
// No more.
//===========================================================================

