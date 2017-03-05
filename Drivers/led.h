/*******************************************************************************/
/**
*      @file : led.h
*   @version : 0
*      @date : March 5, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/
#ifndef LED_H_
#define LED_H_


/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "xgpio.h"
/*******************************     MACROS     *******************************/
#define LED_DEVICE_ID  XPAR_AXI_GPIO_0_DEVICE_ID    /* device ID of the LED */
#define LED_CHANNEL    (1)                          /* Channel of the LEDs on GPIO to operate on*/

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
long int led_initialize(void);
void led_write(uint8_t data);
void led_set(uint8_t mask);
void led_clear(uint8_t mask);

#endif
