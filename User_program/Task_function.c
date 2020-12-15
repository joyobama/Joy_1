//############################################################
// FILE: Task_function.c
// Created on: 2016��5��18��
// Author: XQ
// summary: Task_function
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

#include "Task_function.h"
#include "Timer_function.h"
#include "LCD12864.h"
#include "KEY.h"
#include "PI_Cale.h"
#include "ADC_int.h"
#include "Axis_transform.h"
#include "EPWM_int.h"

extern  IPARK          IparkU;
extern  ADCSamp        ADCSampPare;
extern  TaskTime       TaskTimePare;
extern  PI_Control     pi_spd  ;
extern  PI_Control     pi_id   ;
extern  PI_Control     pi_iq   ;
extern  logic          logicContr;


void Timer_Dpie(void)
{
    if(TaskTimePare.Tim50ms_flag==1)
     {
       Key_Can();
     }
     if(TaskTimePare.Tim100ms_flag==1)
     {
       Key_Dispose();
       Show_disp();
     }

}

void knob_control(void)
{

	if( ADCSampPare.RP3_Voltage<=_IQ( 0.15))
	{
		 logicContr.drive_car=0;
		 logicContr.Start_order=0;
		 logicContr.Qiehuan_count=0;

		 pi_spd.Fbk=_IQ(0.0);
		 pi_spd.Ref=_IQ(0.0);
		 pi_id.Ref=_IQ(0.0);
		 pi_iq.Ref=_IQ(0.0);
		 IparkU.Qs=_IQ(0.0);
		 IparkU.Qs=_IQ(0.0);

	    pi_spd.up=_IQ(0.0);
	    pi_spd.ui=_IQ(0.0);
	    pi_spd.v1=_IQ(0.0);
	    pi_spd.i1=_IQ(0.0);
	    pi_spd.Out=_IQ(0.0);
	    pi_spd.OutF=_IQ(0.0);

	    pi_id.up=_IQ(0.0);
	    pi_id.ui=_IQ(0.0);
	    pi_id.v1=_IQ(0.0);
	    pi_id.i1=_IQ(0.0);
	    pi_id.Out=_IQ(0.0);

	    pi_iq.up=_IQ(0.0);
	   	pi_iq.ui=_IQ(0.0);
        pi_iq.v1=_IQ(0.0);
        pi_iq.i1=_IQ(0.0);
        pi_iq.Out=_IQ(0.0);
	}
	else
	{

	    logicContr.drive_car=1;
 	    pi_spd.Ref = ADCSampPare.RP3_Voltage-_IQ(0.06);   // ��λ��ת���ź�
 	    if( pi_spd.Ref>=_IQ(0.65))
 	    pi_spd.Ref=_IQ(0.65);
	}

     if ((logicContr.olddrive_car==0) &&( logicContr.drive_car==1 ))
     {
   	 logicContr.Start_order=1;
     }
    else if ((logicContr.olddrive_car==1) &&( logicContr.drive_car==1 ))
	{
		 START_CAR( );
	}
    else
	{
		  STOP_CAR();
		 logicContr.Start_order=0;
	}
	logicContr.olddrive_car=logicContr.drive_car;
}


//===========================================================================
// No more.
//===========================================================================
