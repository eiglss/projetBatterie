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
/**** Generate Mode ****/
void timer_start(axi_timer_t *timer, uint32_t value)
{
	timer->TCSR0 &= ~TIMER_TCSR0_ENT0;
	timer->TCSR0 &= ~TIMER_TCSR0_UDT0;	/* up mode */
	timer->TCSR0 &= ~TIMER_TCSR0_ARHT0;
	timer->TLR0 = value;
	timer->TCSR0 |= TIMER_TCSR0_LOAD0;
}
