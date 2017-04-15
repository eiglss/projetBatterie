/*******************************************************************************/
/**
*      @file : iic.c
*   @version : 0
*      @date : April 15, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "iic.h"

/*******************************   FUNCTIONS    *******************************/
/******************************************************************************/
/**
* Test if the IIC bus is busy.
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   IIC_SR_BB if the bus is busy else 0.
*
* @note     None.
*
*******************************************************************************/
inline int iic_bus_is_busy(axi_iic_t * axi)
{
    return axi->SR&IIC_SR_BB;
}

/******************************************************************************/
/**
* Configure the address of the iic slave.
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    address id the address of the slave in 7 bits format.
* @param    operation indicate what kind of operation is:
*               - IIC_WRITE = write operation.
*               - IIC_READ = read operation.
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
static void iic_slave_address(axi_iic_t * axi, uint8_t address, uint8_t operation)
{
    axi->TX_FIFO = (address<<1)|(operation&0x01);
    if(operation)
    {
        axi->CR &= ~IIC_CR_TX;
    }
    else
    {
        axi->CR |= IIC_CR_TX;
    }
}

/******************************************************************************/
/**
* Sending a start condition.
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
static inline void iic_start(axi_iic_t * axi)
{
    axi->CR |= IIC_CR_MSMS|IIC_CR_EN;
}

/******************************************************************************/
/**
* Sending a stop condition.
*
* @param    axi is a pointer to the axi_iic_t instance.
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
static inline void iic_stop(axi_iic_t * axi)
{
    axi->CR &= ~IIC_CR_MSMS;
}


/******************************************************************************/
/**
* Clear a specified Interrupt Status Register (ISR)
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    isr is the specified ISR to clear.
*
* @return   None.
*
* @note     None.
*
*******************************************************************************/
static inline void iic_clear_isr(axi_iic_t * axi, uint32_t isr)
{
    axi->ISR &= isr;
}

/******************************************************************************/
/**
* Manage the transmit process.
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    data is a pointer to the data to be send.
* @param    length is the number of data to be send.
*
* @return   The number of byte that have been send.
*
* @note     If the number of bytes is different from the specified length, an
*           error has occurred.
*
*******************************************************************************/
static uint8_t iic_transmit_handler(axi_iic_t * axi, uint8_t * data, uint8_t length)
{
    /* Local declaration */
    uint8_t byte_cnt;
    /* Program statement */
    for(byte_cnt = 0; byte_cnt < length; byte_cnt++)
    {
        do
        {
            if(axi->ISR&(IIC_ISR_INT_4|IIC_ISR_INT_1|IIC_ISR_INT_0))
            {
                return byte_cnt;
            }
        }
        while(!(axi->ISR&IIC_ISR_INT_2));
        if(byte_cnt == length-1)
        {
                iic_stop(axi);
        }
        axi->TX_FIFO = data[byte_cnt];
        iic_clear_isr(axi, IIC_ISR_INT_2);
    }
    return byte_cnt;
}

/******************************************************************************/
/**
* Manage the receive process.
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    data is a pointer to the data that was read.
* @param    length is the number of data to be read.
*
* @return   The number of byte that have been read.
*
* @note     If the number of bytes is different from the specified length, an
*           error has occurred.
*
*******************************************************************************/
static uint8_t iic_receive_handler(axi_iic_t * axi, uint8_t * data, uint8_t length)
{
    /* Local declaration */
    uint8_t byte_cnt;
    uint32_t isr_mask = IIC_ISR_INT_4|IIC_ISR_INT_1|IIC_ISR_INT_0;
    /* Program statement */
    for(byte_cnt = 0; byte_cnt <= length; byte_cnt ++)
    {
        if(byte_cnt == length-1)
        {
            isr_mask = IIC_ISR_INT_4|IIC_ISR_INT_0;
            axi->CR |= IIC_CR_TXAK;
        }
        while(!(axi->ISR&IIC_ISR_INT_3))
        {
            if(axi->ISR&isr_mask)
            {
                return byte_cnt;
            }
        }
        if(byte_cnt == length-1)
        {
            iic_stop(axi);
        }
        data[byte_cnt] = axi->RX_FIFO;
        iic_clear_isr(axi, IIC_ISR_INT_3);
    }
    return byte_cnt;
}

/******************************************************************************/
/**
* Write data on the specified iic bus
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    address is the address of the slave in 7 bits format.
* @param    data is a pointer to the data to be send.
* @param    length is the number of data to be send.
*
* @return   The number of byte that have been write.
*
* @note     If the number of bytes is different from the specified length, an
*           error has occurred.
*
*******************************************************************************/
uint8_t iic_write(axi_iic_t * axi, uint8_t address, uint8_t * data, uint8_t length)
{
    /* local declaration */
    uint8_t byte_cnt;
    /* program statement */
    iic_slave_address(axi, address, IIC_WRITE);
    iic_clear_isr(axi, IIC_ISR_INT_2|IIC_ISR_INT_1|IIC_ISR_INT_0);
    iic_start(axi);
    while(!iic_bus_is_busy(axi));
    iic_clear_isr(axi, IIC_ISR_INT_4);
    byte_cnt = iic_transmit_handler(axi, data, length);
    while(!(axi->ISR&IIC_ISR_INT_4));
    axi->SOFTR = IIC_SOFTR_RKEY_Value;
    return byte_cnt;
}

/******************************************************************************/
/**
* Read data from the specified iic bus
*
* @param    axi is a pointer to the axi_iic_t instance.
* @param    address is the address of the slave in 7 bits format.
* @param    data is a pointer to the data that was read.
* @param    length is the number of data to be read.
*
* @return   The number of byte that have been read.
*
* @note     If the number of bytes is different from the specified length, an
*           error has occurred.
*
*******************************************************************************/
uint8_t iic_read(axi_iic_t * axi, uint8_t address, uint8_t * data, uint8_t length)
{
    /* local declaration */
    uint8_t byte_cnt;
    /* program statement */
    iic_slave_address(axi, address, IIC_READ);
    axi->RX_FIFO_PIRQ = 0;
    iic_clear_isr(axi, IIC_ISR_INT_3|IIC_ISR_INT_1|IIC_ISR_INT_0);
    iic_start(axi);
    while(!iic_bus_is_busy(axi));
    iic_clear_isr(axi, IIC_ISR_INT_4);
    byte_cnt = iic_receive_handler(axi, data, length);
    while(!(axi->ISR&IIC_ISR_INT_4));
    axi->SOFTR = IIC_SOFTR_RKEY_Value;
    return byte_cnt;
}
