/*******************************************************************************/
/**
*      @file : led.c
*   @version : 0
*      @date : March 5, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "xgpio.h"
#include "led.h"
/*******************************     MACROS     *******************************/

/*******************************     TYPES      *******************************/

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/
static XGpio led;

/*******************************   FUNCTIONS    *******************************/
/******************************************************************************/
/**
* Initialize the LED GPIO.
*
* @param    None.
*
* @return
*       - XST_SUCCESS if the initialization was successfull.
*       - XST_DEVICE_NOT_FOUND  if the device configuration data was not found
*       for a device with the supplied device ID.
*
* @note     Nothing is done except to initialize the LED.
*
*******************************************************************************/
long int led_initialize(void)
{
    /* local declaration */
    long int status;
    /* program statement */
    status = XGpio_Initialize(&led, LED_DEVICE_ID);
    if(status == XST_SUCCESS)
    {
        XGpio_SetDataDirection(&led, LED_CHANNEL, 0x00);
    }
    return status;
}

/******************************************************************************/
/**
* Write to data to LED, and overwrite the previous value.
*
* @param    Data is the value to be written to the LED. (bit 0 for LED 0 ... bit
*           4 for LED 4)
*
* @return   None.
*
* @note     Data must be equal 0 to clear and 1 to set (only the last 4 bits are
*           considered)
*
*******************************************************************************/
void led_write(uint8_t data)
{
    XGpio_DiscreteWrite(&led, LED_CHANNEL, (uint32_t)(data&0x0F));
}

/******************************************************************************/
/**
* Set the specified LED and does not overwrite the previous value.
*
* @param    mask is the set of bits that will be set to the LED. All other bits
*           in the data register are unaffected. (bit 0 for LED 0 ... bit 4 for
*           LED 4)
*
* @return   None.
*
* @note     Only the last 4 bits of the parameter mask are considered
*
*******************************************************************************/
void led_set(uint8_t mask)
{
    XGpio_DiscreteSet(&led, LED_CHANNEL, (uint32_t)(mask&0x0F));
}

/******************************************************************************/
/**
* Clear the specified LED and does not overwrite the previous value.
*
* @param    mask is the set of bits that will be clear to the LED. All other
*           bits in the data register are unaffected. (bit 0 for LED 0 ... bit 4
*           for LED 4)
*
* @return   None.
*
* @note     Only the last 4 bits of the parameter mask are considered
*
*******************************************************************************/
void led_clear(uint8_t mask)
{
    XGpio_DiscreteClear(&led, LED_CHANNEL, (uint32_t)(mask&0x0F));
}
