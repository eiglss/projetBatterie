/*******************************************************************************/
/**
*      @file : gpio.h
*   @version : 0
*      @date : April 17, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "xparameters.h"

#ifndef GPIO_H_
#define GPIO_H_

/*******************************     MACROS     *******************************/
/**** GPIO ****/
#define GPIO_0  (axi_gpio_t *)XPAR_GPIO_0_BASEADDR
#define GPIO_1  (axi_gpio_t *)XPAR_GPIO_0_BASEADDR
#define GPIO_2  (axi_gpio_t *)XPAR_GPIO_0_BASEADDR
#define GPIO_3  (axi_gpio_t *)XPAR_GPIO_0_BASEADDR

#define GPIO_LED			GPIO_0
#define GPIO_SW				GPIO_1
#define GPIO_BTN			GPIO_2
#define GPIO_MPU9250_INT	GPIO_3

/**** GIE ****/
#define GPIO_GIE_GIE 0X8000  /* Global Interrupt Enable */
/* [30:0] Reserved */

/**** IP_IER ****/
/* [31:2] Reserved */
#define GPIO_IP_IER_CH2 0x0002  /* Enable Channel 2 Interrupt */
#define GPIO_IP_IER_CH1 0x0001  /* Enable Channel 1 Interrupt */

/**** IP_ISR ****/
/* [31:2] Reserved */
#define GPIO_IP_ISR_CH2 0x0002  /* Channel 2 Interrupt Status */
#define GPIO_IP_ISR_CH1 0x0001  /* Channel 1 Interrupt Status */

/*******************************     TYPES      *******************************/
typedef struct
{
    uint32_t GPIO_DATA;     /* Channel 1 AXI GPIO Data Register */
    uint32_t GPIO_TRI;      /* Channel 1 AXI GPIO 3-state Control Register */
    uint32_t GPIO2_DATA;    /* Channel 2 AXI GPIO Data Register */
    uint32_t GPIO2_TRI;     /* Channel 2 AXI GPIO 3-state Control */
    uint32_t RESERVED0[67];
    uint32_t GIER;          /* Global Interrupt Enable Register */
    uint32_t IP_ISR;        /* IP Interrupt Enable Register (IP IER) */
    uint32_t RESERVED1;
    uint32_t IP_IER;        /* IP Interrupt Status Register */
}axi_gpio_t;

/*******************************   FUNCTIONS    *******************************/
/**** GPIO 1 ****/
    /**** GPIO 3-State ****/
inline void gpio_tri_dir(axi_gpio_t * axi, uint32_t value);
inline void gpio_tri_output(axi_gpio_t * axi, uint32_t value);
inline void gpio_tri_input(axi_gpio_t * axi, uint32_t value);
    /**** GPIO Interrupt ****/
inline void gpio_interrupt_enbale(axi_gpio_t * axi, uint8_t value);
inline void gpio_interrupt_disable(axi_gpio_t * axi, uint8_t value);
inline uint32_t gpio_interrupt_status(axi_gpio_t * axi);
inline void gpio_interrupt_clear(axi_gpio_t * axi, uint32_t value);
    /**** GPIO R/W ****/
inline void gpio_write(axi_gpio_t * axi, uint32_t value);
inline void gpio_set(axi_gpio_t * axi, uint32_t value);
inline void gpio_clear(axi_gpio_t * axi, uint32_t value);
inline void gpio_toggle(axi_gpio_t * axi, uint32_t value);
inline uint32_t gpio_read(axi_gpio_t * axi);
/**** GPIO 2 ****/
    /**** GPIO 3-State ****/
inline void gpio2_tri_dir(axi_gpio_t * axi, uint32_t value);
inline void gpio2_tri_output(axi_gpio_t * axi, uint32_t value);
inline void gpio2_tri_input(axi_gpio_t * axi, uint32_t value);
    /**** GPIO Interrupt ****/
inline void gpio2_interrupt_enbale(axi_gpio_t * axi, uint8_t value);
inline void gpio2_interrupt_disable(axi_gpio_t * axi, uint8_t value);
inline uint32_t gpio2_interrupt_status(axi_gpio_t * axi);
inline void gpio2_interrupt_clear(axi_gpio_t * axi, uint8_t value);
    /**** GPIO R/W ****/
inline void gpio2_write(axi_gpio_t * axi, uint32_t value);
inline void gpio2_set(axi_gpio_t * axi, uint32_t value);
inline void gpio2_clear(axi_gpio_t * axi, uint32_t value);
inline void gpio2_toggle(axi_gpio_t * axi, uint32_t value);
inline uint32_t gpio2_read(axi_gpio_t * axi);

#endif
