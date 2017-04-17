/*******************************************************************************/
/**
*      @file : led.h
*   @version : 0
*      @date : April 17, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/
#include "gpio.h"

#ifndef LED_H_
#define LED_H_

/*******************************     MACROS     *******************************/
/**** GPIO ****/
#define GPIO_LED GPIO_0

/**** LEDS ****/
#define LED0	0x0001
#define LED1	0x0002
#define LED2	0x0004
#define LED4	0x0008

/***************** Macros (Inline Functions) Definitions **********************/
/******************************************************************************/
/**
* Write on the specified led of the ZYBO
*
* @param    led is the value to be write on the led.
*
* @return   None.
*
* @note     1 = ON ; 0 = OFF.
*
*******************************************************************************/
#define led_write(led)	gpio_write(GPIO_LED, (uint32_t)(led)&0x000F)

/***************** Macros (Inline Functions) Definitions **********************/
/******************************************************************************/
/**
* Set the specified led of the ZYBO
*
* @param    led is the led that must be set.
*
* @return   None.
*
* @note     1 = ON ; 0 = Unchanged.
*
*******************************************************************************/
#define led_set(led)	gpio_set(GPIO_LED, (uint32_t)(led)&0x000F)

/***************** Macros (Inline Functions) Definitions **********************/
/******************************************************************************/
/**
* Clear the specified led of the ZYBO
*
* @param    led is the led that must be clear.
*
* @return   None.
*
* @note     1 = OFF ; 0 = Unchanged.
*
*******************************************************************************/
#define led_clear(led)	gpio_clear(GPIO_LED, (uint32_t)(led)&0x000F)

/***************** Macros (Inline Functions) Definitions **********************/
/******************************************************************************/
/**
* Toggle the specified led of the ZYBO
*
* @param    led is the led that must be toggle.
*
* @return   None.
*
* @note     1 = Toggle ; 0 = Unchanged.
*
*******************************************************************************/
#define led_toggle(led)	gpio_toggle(GPIO_LED, (uint32_t)(led)&0x000F)

#endif /* LED_H_ */
