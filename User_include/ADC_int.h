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

#ifndef ADC_int_H
#define ADC_int_H
#include "DSP2833x_Project.h"
#include "IQmathLib.h"
typedef struct {
	     _iq   BUS_Curr ;     // DC Bus  Current
	     _iq   PhaseA_Curr;   // Phase A Current
	     _iq   PhaseB_Curr;   // Phase A Current
	     _iq   BUS_Voltage ;  //DC Bus  Voltage
	     _iq   PhaseA_Voltage ;  //Phase A Voltage
	     _iq   PhaseB_Voltage ;  //Phase B Voltage
	     _iq   PhaseC_Voltage ;  //Phase C Voltage
	     _iq   RP3_Voltage ;     //  RP1_Voltage
	     _iq   RP2_Voltage ;     //  RP1_Voltage
	     _iq   OffsetBUS_Curr ;     // DC Bus  Current
	     _iq   OffsetPhaseA_Curr;   // Phase A Current
	     _iq   OffsetPhaseB_Curr;   // Phase A Current
	     _iq   Coeff_filterK1;   // Phase A Current
		 _iq   Coeff_filterK2;   // Phase A Current
		 _iq    Test_Vq_ref;
		 _iq    Test_Vd_ref;
       }ADCSamp;

#define  ADCSamp_DEFAULTS  {0,0,0,0,0,0,0,0,0,0,0,0,_IQ(0.238),_IQ(0.762),0,0}


extern void ADC_cal();
void   ADC_MACRO_INIT( Uint16  *ChSel_X,  Uint16 *Trigsel_X,  Uint16  *ACQPS_X);
void   ADC_SOC_int(void );
void   ADC_Sample(void );
#endif  // end of ADC_int_H definition

//===========================================================================
// End of file.
//===========================================================================
