/*******************************************************************************/
/**
*      @file : timer.h
*   @version : 0
*      @date : May 2, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "xparameters.h"

#ifndef TIMER_H_
#define TIMER_H_

/*******************************     MACROS     *******************************/
/**** TIMER ****/
#define TIMER_0 (axi_timer_t *)XPAR_AXI_TIMER_0_BASEADDR

/**** TCSR0 ****/
/* [31:12] Reserved */
#define TIMER_TCSR0_CASC    0x0800  /* Enable cascade mode of timers */
#define TIMER_TCSR0_ENALL   0x0400  /* Enable All Timers */
#define TIMER_TCSR0_PWMA0   0x0200  /* Enable Pulse Width Modulation for Timer 0 */
#define TIMER_TCSR0_T0INT   0x0100  /* Timer 0 Interrupt */
#define TIMER_TCSR0_ENT0    0x0080  /* Enable Timer 0 */
#define TIMER_TCSR0_ENIT0   0x0040  /* Enable Interrupt for Timer 0 */
#define TIMER_TCSR0_LOAD0   0x0020  /* Load Timer 0 */
#define TIMER_TCSR0_ARHT0   0x0010  /* Auto Reload/Hold Timer 0 */
#define TIMER_TCSR0_CAPT0   0x0008  /* Enable External Capture Trigger Timer 0 */
#define TIMER_TCSR0_GENT0   0x0004  /* Enable External Generate Signal Timer 0 */
#define TIMER_TCSR0_UDT0    0x0002  /* Up/Down Count Timer 0 */
#define TIMER_TCSR0_MDT0    0x0001  /* Timer 0 Mode */

/**** TLR0 ****/
#define TIMER_TLR0  0xFFFF  /* Timer/Counter Load Register */

/**** TCR0 ****/
#define TIMER_TCR0  0xFFFF  /* Timer/Counter Register */

/**** TCSR1 ****/
/* [31:12] Reserved */
#define TIMER_TCSR1_ENALL   0x0400  /* Enable All Timers */
#define TIMER_TCSR1_PWMA0   0x0200  /* Enable Pulse Width Modulation for Timer 1 */
#define TIMER_TCSR1_T1INT   0x0100  /* Timer 1 Interrupt */
#define TIMER_TCSR1_ENT1    0x0080  /* Enable Timer 1 */
#define TIMER_TCSR1_ENIT1   0x0040  /* Enable Interrupt for Timer 1 */
#define TIMER_TCSR1_LOAD1   0x0020  /* Load Timer 1 */
#define TIMER_TCSR1_ARHT1   0x0010  /* Auto Reload/Hold Timer 1 */
#define TIMER_TCSR1_CAPT1   0x0008  /* Enable External Capture Trigger Timer 1 */
#define TIMER_TCSR1_GENT1   0x0004  /* Enable External Generate Signal Timer 1 */
#define TIMER_TCSR1_UDT1    0x0002  /* Up/Down Count Timer 1 */
#define TIMER_TCSR1_MDT1    0x0001  /* Timer 1 Mode */

/**** TLR1 ****/
#define TIMER_TLR0  0xFFFF /* Timer/Counter Load Register */

/**** TCR1 ****/
#define TIMER_TCR0  0xFFFF  /* Timer/Counter Register */

/*******************************     TYPES      *******************************/
typedef struct
{
    uint32_t TCSR0          /* Timer 0 Control and Status Register */
    uint32_t TLR0           /* Timer 0 Load Register */
    uint32_t TCR0           /* Timer 0 Counter Register */
    uint32_t RESERVED0[2];
    uint32_t TCSR1;         /* Timer 1 Control and Status Register */
    uint32_t TLR1;          /* Timer 1 Load Register */
    uint32_t TCR1;          /* Timer 1 Counter Register */
    uint32_t RESERVED1[2];
}axi_timer_t;

/*******************************   FUNCTIONS    *******************************/

#endif /* TIMER_H_ */
