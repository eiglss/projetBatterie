/*******************************************************************************/
/**
*      @file : gpio.c
*   @version : 0
*      @date : April 17, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "gpio.h"

/*******************************   FUNCTIONS    *******************************/
/**** GPIO 1 ****/

    /**** GPIO 3-State ****/

/******************************************************************************/
/**
* Set the direction of the GPIO on the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the direction of the gpio (0 for output, 1 input).
*
* @return   None.
*
* @note     bit 0 corresponding to the pin 0, bit 1 to the pin 1...
*
*******************************************************************************/
inline void gpio_tri_dir(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_TRI = value;
}

/******************************************************************************/
/**
* Set the specified pin of the GPIO as output on the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the pin to be set as output.
*
* @return   None.
*
* @note     bit 0 corresponding to the pin 0, bit 1 to the pin 1...
*
*******************************************************************************/
inline void gpio_tri_output(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_TRI &= ~value;
}

/******************************************************************************/
/**
* Set the specified pin of the GPIO as input on the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the pin to be set as input.
*
* @return   None.
*
* @note     bit 0 corresponding to the pin 0, bit 1 to the pin 1...
*
*******************************************************************************/
inline void gpio_tri_input(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_TRI |= value;
}

    /**** GPIO Interrupt ****/

/******************************************************************************/
/**
* Enable the interruption for the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   None.
*
* @note     interruption are enable on all the pin (no choice)
*
*******************************************************************************/
inline void gpio_interrupt_enbale(axi_gpio_t * axi)
{
    axi->IP_IER |= GPIO_IP_IER_CH1;
}

/******************************************************************************/
/**
* Disable the interruption for the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   None.
*
* @note     interruption are disable on all the pin (no choice)
*
*******************************************************************************/
inline void gpio_interrupt_disable(axi_gpio_t * axi)
{
    axi->IP_IER &= ~GPIO_IP_IER_CH1;
}

/******************************************************************************/
/**
* Get the interruption status for the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   None.
*
* @note     0 = No Channel 1 input interrupt; 1 = Channel 1 input interrupt
*
*******************************************************************************/
inline uint32_t gpio_interrupt_status(axi_gpio_t * axi)
{
    return axi->IP_ISR&GPIO_IP_ISR_CH1;
}

/******************************************************************************/
/**
* Clear interruption status for the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
inline void gpio_interrupt_clear(axi_gpio_t * axi)
{
    axi->IP_ISR &= GPIO_IP_ISR_CH1;
}

    /**** GPIO R/W ****/

/******************************************************************************/
/**
* Write on the channel 1 of the GPIO
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the value to be write on the gpio.
*
* @return   None.
*
* @note     1 = VCC ; 0 = GND.
*
*******************************************************************************/
inline void gpio_write(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_DATA = value;
}

/******************************************************************************/
/**
* Set the specified pin of the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the pin that must be set.
*
* @return   None.
*
* @note     1 = VCC ; 0 = GND.
*
*******************************************************************************/
inline void gpio_set(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_DATA |= value;
}

/******************************************************************************/
/**
* Clear the specified pin of the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the pin that must be clear.
*
* @return   None.
*
* @note     1 = VCC ; 0 = GND.
*
*******************************************************************************/
inline void gpio_clear(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_DATA &= ~value;
}

/******************************************************************************/
/**
* Toggle the specified pin of the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the pin that must be toggle.
*
* @return   None.
*
* @note     1 = VCC ; 0 = GND.
*
*******************************************************************************/
inline void gpio_toggle(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_DATA ^= value;
}

/******************************************************************************/
/**
* Read the value of the GPIO on the channel 1
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   The value of the GPIO.
*
* @note     1 = VCC ; 0 = GND.
*
*******************************************************************************/
inline uint32_t gpio_read(axi_gpio_t * axi)
{
    return axi->GPIO_DATA;
}

/**** GPIO 2 ****/

    /**** GPIO 3-State ****/

/******************************************************************************/
/**
* Set the direction of the GPIO on the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the direction of the gpio (0 for output, 1 input).
*
* @return   None.
*
* @note     bit 0 corresponding to the pin 0, bit 1 to the pin 1...
*
*******************************************************************************/
inline void gpio2_tri_dir(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_TRI = value;
}

/******************************************************************************/
/**
* Set the specified pin of the GPIO as output on the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the pin to be set as output.
*
* @return   None.
*
* @note     bit 0 corresponding to the pin 0, bit 1 to the pin 1...
*
*******************************************************************************/
inline void gpio2_tri_output(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_TRI &= ~value;
}

/******************************************************************************/
/**
* Set the specified pin of the GPIO as input on the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the pin to be set as input.
*
* @return   None.
*
* @note     bit 0 corresponding to the pin 0, bit 1 to the pin 1...
*
*******************************************************************************/
inline void gpio2_tri_input(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_TRI |= value;
}

    /**** GPIO Interrupt ****/

/******************************************************************************/
/**
* Enable the interruption for the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   None.
*
* @note     interruption are enable on all the pin (no choice)
*
*******************************************************************************/
inline void gpio2_interrupt_enbale(axi_gpio_t * axi)
{
    axi->IP_IER |= GPIO_IP_IER_CH2;
}

/******************************************************************************/
/**
* Disable the interruption for the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   None.
*
* @note     interruption are disable on all the pin (no choice)
*
*******************************************************************************/
inline void gpio2_interrupt_disable(axi_gpio_t * axi)
{
    axi->IP_IER &= ~GPIO_IP_IER_CH2;
}

/******************************************************************************/
/**
* Get the interruption status for the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   None.
*
* @note     0 = No Channel 1 input interrupt; 1 = Channel 1 input interrupt
*
*******************************************************************************/
inline uint32_t gpio2_interrupt_status(axi_gpio_t * axi)
{
    return axi->IP_ISR&GPIO_IP_ISR_CH2;
}

/******************************************************************************/
/**
* Clear interruption status for the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
inline void gpio2_interrupt_clear(axi_gpio_t * axi)
{
    axi->IP_ISR &= GPIO_IP_ISR_CH2;
}

    /**** GPIO R/W ****/

/******************************************************************************/
/**
* Write on the channel 2 of the GPIO
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the value to be write on the gpio.
*
* @return   None.
*
* @note     1 = VCC ; 0 = GND.
*
*******************************************************************************/
inline void gpio2_write(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_DATA = value;
}

/******************************************************************************/
/**
* Set the specified pin of the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the pin that must be set.
*
* @return   None.
*
* @note     1 = VCC ; 0 = GND.
*
*******************************************************************************/
inline void gpio2_set(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_DATA |= value;
}

/******************************************************************************/
/**
* Clear the specified pin of the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the pin that must be clear.
*
* @return   None.
*
* @note     1 = VCC ; 0 = GND.
*
*******************************************************************************/
inline void gpio2_clear(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_DATA &= ~value;
}

/******************************************************************************/
/**
* Toggle the specified pin of the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    value is the pin that must be toggle.
*
* @return   None.
*
* @note     1 = VCC ; 0 = GND.
*
*******************************************************************************/
inline void gpio2_toggle(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_DATA ^= value;
}

/******************************************************************************/
/**
* Read the value of the GPIO on the channel 2
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   The value of the GPIO.
*
* @note     1 = VCC ; 0 = GND.
*
*******************************************************************************/
inline uint32_t gpio2_read(axi_gpio_t * axi)
{
    return axi->GPIO2_DATA;
}
