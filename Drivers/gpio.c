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
inline void gpio_tri_dir(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_TRI = value;
}

inline void gpio_tri_output(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_TRI &= ~value;
}

inline void gpio_tri_input(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_TRI |= value;
}

inline void gpio_interrupt_enbale(axi_gpio_t * axi, uint8_t value)
{
    axi->IP_IER |= value&GPIO_IP_IER_CH1;
}

inline void gpio_interrupt_disable(axi_gpio_t * axi, uint8_t value)
{
    axi->IP_IER &= ~(value&GPIO_IP_IER_CH1);
}

inline uint32_t gpio_interrupt_status(axi_gpio_t * axi)
{
    return axi->IP_ISR&GPIO_IP_ISR_CH1;
}

inline void gpio_interrupt_clear(axi_gpio_t * axi, uint32_t value)
{
    axi->IP_ISR &= value&GPIO_IP_ISR_CH1;
}

inline void gpio_write(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_DATA = value;
}

inline void gpio_set(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_DATA |= value;
}

inline void gpio_clear(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_DATA &= ~value;
}

inline void gpio_toggle(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO_DATA ^= value;
}

inline uint32_t gpio_read(axi_gpio_t * axi)
{
    return axi->GPIO_DATA;
}

/**** GPIO 2 ****/
inline void gpio2_tri_dir(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_TRI = value;
}

inline void gpio2_tri_output(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_TRI &= ~value;
}

inline void gpio2_tri_input(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_TRI |= value;
}

inline void gpio2_interrupt_enbale(axi_gpio_t * axi, uint8_t value)
{
    axi->IP_IER |= value&GPIO_IP_IER_CH2;
}

inline void gpio2_interrupt_disable(axi_gpio_t * axi, uint8_t value)
{
    axi->IP_IER &= ~(value&GPIO_IP_IER_CH2);
}

inline uint32_t gpio2_interrupt_status(axi_gpio_t * axi)
{
    return axi->IP_ISR&GPIO_IP_ISR_CH2;
}

inline void gpio2_interrupt_clear(axi_gpio_t * axi, uint8_t value)
{
    axi->IP_ISR &= value&GPIO_IP_ISR_CH2;
}

inline void gpio2_write(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_DATA = value;
}

inline void gpio2_set(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_DATA |= value;
}

inline void gpio2_clear(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_DATA &= ~value;
}

inline void gpio2_toggle(axi_gpio_t * axi, uint32_t value)
{
    axi->GPIO2_DATA ^= value;
}

inline uint32_t gpio2_read(axi_gpio_t * axi)
{
    return axi->GPIO2_DATA;
}
