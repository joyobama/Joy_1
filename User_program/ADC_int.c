//############################################################
// FILE:  ADC_int.c
// Created on: 2016年8月5日
// Author: XQ
// summary: ADCSampPare
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//版权所有，盗版必究
//DSP/STM32电机控制开发板
//硕历电子
//网址: https://shuolidianzi.taobao.com
//修改日期:2016/5/23
//版本：V16.3-1
//Author-QQ: 616264123
//电机控制QQ群：314306105
//############################################################

#include "ADC_int.h"

#define CPU_CLOCK_SPEED      15.000L   // 10.000L for a 100MHz CPU clock speed
#define ADC_usDELAY 50000L

extern   ADCSamp     ADCSampPare;
extern _iq   FilK1 ;
extern _iq   FilK2 ;

 Uint16 ChSel[16]   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 Uint16	TrigSel[16] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
 Uint16 ACQPS[16]   = {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};


void   ADC_MACRO_INIT( Uint16  *ChSel_X,  Uint16 *Trigsel_X,  Uint16  *ACQPS_X)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
	ADC_cal();
	EDIS;

	AdcRegs.ADCTRL3.all = 0x00E0;  /* Power up bandgap/reference/ADC circuits*/
    DELAY_US(ADC_usDELAY);         /* Delay before converting ADC channels*/

 	AdcRegs.ADCTRL1.bit.ACQ_PS = ACQPS_X[0];
	AdcRegs.ADCTRL1.bit.CPS = 1;
	AdcRegs.ADCTRL3.bit.ADCCLKPS =  0;
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;        /* 0x0 Dual Sequencer Mode, 0x1 Cascaded Mode*/
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x0;
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;
	AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0x1;
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1=0x1; /* enable SOC from EPWMA trigger*/


	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = ChSel_X[0];
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = ChSel_X[1];
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = ChSel_X[2];
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = ChSel_X[3];
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = ChSel_X[4];
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = ChSel_X[5];
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = ChSel_X[6];
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = ChSel_X[7];
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = ChSel_X[8];
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = ChSel_X[9];

	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 9;
	EDIS;

    /* Set up Event Trigger with CNT_zero enable for Time-base of EPWM1 */
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;     /* Enable SOCA */
    EPwm1Regs.ETSEL.bit.SOCASEL = 2;    /* Enable period event for SOCA */
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;     /* Generate SOCA on the 1st event */
	EPwm1Regs.ETCLR.bit.SOCA = 1;       /* Clear SOCA flag */
}

void  ADC_SOC_int(void )
{
	    ChSel[0]=1;		// Dummy meas. avoid 1st sample issue Rev0 Picollo*/
	    ChSel[1]=1;		// ChSelect: ADC A1-> DC Bus  Current
		ChSel[2]=9;		// ChSelect: ADC B1-> Phase A Current
		ChSel[3]=8;		// ChSelect: ADC B0-> Phase B Current
		ChSel[4]=0;     // ChSelect: ADC A0-> DC Bus  Voltage
		ChSel[5]=2;		// ChSelect: ADC A2->  RP3
		ChSel[6]=3;		// ChSelect: ADC A3->  RP2
		ChSel[7]=10;	// ChSelect: ADC B2-> Phase A Voltage
		ChSel[8]=11;	// ChSelect: ADC B3-> Phase B Voltage
		ChSel[9]=12;	// ChSelect: ADC B4-> Phase C Voltage

		ADC_MACRO_INIT(ChSel,TrigSel,ACQPS) ;
}

void   ADC_Sample(void )
{

	ADCSampPare.BUS_Curr = _IQmpy(FilK2,ADCSampPare.BUS_Curr )+_IQmpy(FilK1,AdcMirror.ADCRESULT1+29-ADCSampPare.OffsetBUS_Curr);

	ADCSampPare.PhaseA_Curr = _IQmpy2 (_IQ12toIQ(AdcMirror.ADCRESULT2)-ADCSampPare.OffsetPhaseA_Curr) ;
	ADCSampPare.PhaseB_Curr = _IQmpy2 (_IQ12toIQ(AdcMirror.ADCRESULT3)-ADCSampPare.OffsetPhaseB_Curr) ;

	ADCSampPare.BUS_Voltage = _IQmpy(FilK2,ADCSampPare.BUS_Voltage )+_IQmpy(FilK1,AdcMirror.ADCRESULT4);

	ADCSampPare.PhaseA_Voltage = AdcMirror.ADCRESULT7 ;
    ADCSampPare.PhaseB_Voltage = AdcMirror.ADCRESULT8 ;
    ADCSampPare.PhaseC_Voltage = AdcMirror.ADCRESULT9 ;

    ADCSampPare.RP3_Voltage =_IQ12toIQ (AdcMirror.ADCRESULT5) ;
    ADCSampPare.RP2_Voltage =_IQ12toIQ (AdcMirror.ADCRESULT6) ;

}


//===========================================================================
// No more.
//===========================================================================
