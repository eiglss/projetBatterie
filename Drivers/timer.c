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
/*******************************   FUNCTIONS    *******************************/

/**** Generate Mode ****/
/******************************************************************************/
/**
* Start the specified timer from 0.
*
* @param    timer is a pointer to the axi_timer_t instance.
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
void timer_start(axi_timer_t * timer)
{
	timer->TCSR0 = 0; /* Reset Control/Status Register 0 */
	timer->TLR0 = 0; /* Reset Load Register */
	timer->TCSR0 |= TIMER_TCSR0_LOAD0; /* Load Timer 0 */
	timer->TCSR0 &= ~TIMER_TCSR0_LOAD0;
	timer->TCSR0 |= TIMER_TCSR0_ENT0; /* Enable Timer 0 */
}

/******************************************************************************/
/**
* Read the counter register of the specified timer.
*
* @param    timer is a pointer to the axi_timer_t instance.
*
* @return   the time in second.
*
* @note     None.
*
*******************************************************************************/
inline double timer_read(axi_timer_t * timer)
{
	return timer_second(timer->TCR0);
}

/******************************************************************************/
/**
* Pause the specified timer.
*
* @param    timer is a pointer to the axi_timer_t instance.
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
inline void timer_pause(axi_timer_t * timer)
{
	timer->TCSR0 &= ~TIMER_TCSR0_ENT0;
}

/******************************************************************************/
/**
* Resume the specified timer.
*
* @param    timer is a pointer to the axi_timer_t instance.
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
inline void timer_resume(axi_timer_t * timer)
{
	timer->TCSR0 |= TIMER_TCSR0_ENT0;
}

/******************************************************************************/
/**
* Pause the specified timer and reload 0.
*
* @param    timer is a pointer to the axi_timer_t instance.
*
* @return   the timer in second befor stoping the timer.
*
* @note     None.
*
*******************************************************************************/
double timer_stop(axi_timer_t * timer)
{
	double value;
	value = timer_second(timer->TCR0);
	timer->TCSR0 = 0;
	timer->TLR0 = 0; /* Reset Load Register */
	timer->TCSR0 |= TIMER_TCSR0_LOAD0; /* Load Timer 0 */
	timer->TCSR0 &= ~TIMER_TCSR0_LOAD0;
	return value;
}

/******************************************************************************/
/**
* Reset to 0 and start the specified timer.
*
* @param    timer is a pointer to the axi_timer_t instance.
*
* @return   the timer in second befor restarting the timer.
*
* @note     None.
*
*******************************************************************************/
double timer_restart(axi_timer_t * timer)
{
	double value;
	value = timer_second(timer->TCR0);
	timer_start(timer);
	return value;
}
