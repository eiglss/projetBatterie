/*******************************************************************************/
/**
*      @file : swicth.h
*   @version : 0
*      @date : April 17, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/
#include "gpio.h"

#ifndef SWITCH_H_
#define SWITCH_H_

/*******************************     MACROS     *******************************/
/**** GPIO ****/
#define GPIO_SW GPIO_1

/**** LEDS ****/
#define SW0	0x0001
#define SW1	0x0002
#define SW2	0x0004
#define SW4	0x0008

/***************** Macros (Inline Functions) Definitions **********************/
/******************************************************************************/
/**
* Read values of the switches
*
* @param    None.
*
* @return   Values of the switches.
*
* @note     1 = ON ; 0 = OFF.
*
*******************************************************************************/
#define sw_read()	gpio_read(GPIO_SW)&0x000F

/***************** Macros (Inline Functions) Definitions **********************/
/******************************************************************************/
/**
* Read the values of specified switches
*
* @param    switches that must be read.
*
* @return   Values of the switches.
*
* @note     1 = ON ; 0 = OFF.
*
*******************************************************************************/
#define sw_is_on(sw)	gpio_read(GPIO_SW)&((sw)&0x000F)

#endif /* SWITCH_H_ */
