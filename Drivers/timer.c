/*******************************************************************************/
/**
*      @file : timer.c
*   @version : 0
*      @date : May 2, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "timer.h"
#include "xtmrctr.h"
/*******************************   FUNCTIONS    *******************************/
XTmrCtr TimerCounter;

/**** Generate Mode ****/
void timer_start(axi_timer_t * timer)
{
	XTmrCtr *TmrCtrInstancePtr = &TimerCounter;
	XTmrCtr_Initialize(TmrCtrInstancePtr, XPAR_TMRCTR_0_DEVICE_ID);
	XTmrCtr_SetOptions(TmrCtrInstancePtr, XPAR_TMRCTR_0_DEVICE_ID, 0);
	XTmrCtr_Start(TmrCtrInstancePtr, XPAR_TMRCTR_0_DEVICE_ID);
}

inline double timer_read(axi_timer_t * timer)
{
	return timer_second(XTmrCtr_GetValue(&TimerCounter, XPAR_TMRCTR_0_DEVICE_ID));
}

inline void timer_pause(axi_timer_t * timer)
{
	XTmrCtr_Stop(&TimerCounter, XPAR_TMRCTR_0_DEVICE_ID);
}

double timer_stop(axi_timer_t * timer)
{
	double value;
	value = timer_second(XTmrCtr_GetValue(&TimerCounter, XPAR_TMRCTR_0_DEVICE_ID));
	XTmrCtr_Reset(&TimerCounter, XPAR_TMRCTR_0_DEVICE_ID);
	return value;
}

double timer_restart(axi_timer_t * timer)
{
	double value;
	value = timer_second(XTmrCtr_GetValue(&TimerCounter, XPAR_TMRCTR_0_DEVICE_ID));
	timer_stop(timer);
	XTmrCtr_Reset(&TimerCounter, XPAR_TMRCTR_0_DEVICE_ID);
	XTmrCtr_Initialize(&TimerCounter, XPAR_TMRCTR_0_DEVICE_ID);
	XTmrCtr_SetOptions(&TimerCounter, XPAR_TMRCTR_0_DEVICE_ID, 0);
	XTmrCtr_Start(&TimerCounter, XPAR_TMRCTR_0_DEVICE_ID);
	return value;
}

