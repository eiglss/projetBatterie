/*******************************************************************************/
/**
*      @file : button.h
*   @version : 0
*      @date : April 17, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/
#include "gpio.h"

#ifndef BUTTON_H_
#define BUTTON_H_

/*******************************     MACROS     *******************************/
/**** GPIO ****/
#define GPIO_BTN GPIO_2

/**** LEDS ****/
#define BTN0    0x0001
#define BTN1    0x0002
#define BTN2    0x0004
#define BTN3    0x0008

/***************** Macros (Inline Functions) Definitions **********************/
/******************************************************************************/
/**
* Read values of the buttons
*
* @param    None.
*
* @return   Values of the buttons.
*
* @note     1 = ON ; 0 = OFF.
*
*******************************************************************************/
#define btn_read()  gpio_read(GPIO_BTN)&0x000F

/***************** Macros (Inline Functions) Definitions **********************/
/******************************************************************************/
/**
* Read the values of specified buttons
*
* @param    switches that must be read.
*
* @return   Values of the buttons.
*
* @note     1 = ON ; 0 = OFF.
*
*******************************************************************************/
#define btn_is_on(btn)  gpio_read(GPIO_BTN)&((btn)&0x000F)

#endif /* BUTTON_H_ */
