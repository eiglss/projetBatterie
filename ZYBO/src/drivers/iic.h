/*******************************************************************************/
/**
*      @file : iic.h
*   @version : 0
*      @date : April 15, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "xparameters.h"

#ifndef IIC_H_
#define IIC_H_

/*******************************     MACROS     *******************************/
/**** IIC DEVICE ****/
#define IIC_0   (axi_iic_t *)XPAR_AXI_IIC_0_BASEADDR
#define IIC_1   (axi_iic_t *)XPAR_AXI_IIC_1_BASEADDR

/**** IIC_OPERATIONS ****/
#define IIC_READ    1
#define IIC_WRITE   0

/**** GIE ****/
#define IIC_GIE_GIE 0X8000  /* Global Interrupt Enable */
/* [30:0] Reserved */

/**** ISR ****/
/* [31:8] Reserved */
#define IIC_ISR_INT_7   0x0080  /* Interrupt(7) — Transmit FIFO Half Empty */
#define IIC_ISR_INT_6   0x0040  /* Interrupt(6) — Not Addressed As Slave */
#define IIC_ISR_INT_5   0x0020  /* Interrupt(5) — Addressed As Slave */
#define IIC_ISR_INT_4   0x0010  /* Interrupt(4) — IIC Bus is Not Busy */
#define IIC_ISR_INT_3   0x0008  /* Interrupt(3) — Receive FIFO Full */
#define IIC_ISR_INT_2   0x0004  /* Interrupt(2) — Transmit FIFO Empty */
#define IIC_ISR_INT_1   0x0002  /* Interrupt(1) — Transmit Error/Slave Transmit Complete */
#define IIC_ISR_INT_0   0x0001  /* Interrupt(0) — Arbitration Lost */

/**** IER ****/
/* [31:8] Reserved */
#define IIC_IER_INT_7   0x0080  /* Interrupt(7) — Transmit FIFO Half Empty */
#define IIC_IER_INT_6   0x0040  /* Interrupt(6) — Not Addressed As Slave */
#define IIC_IER_INT_5   0x0020  /* Interrupt(5) — Addressed As Slave */
#define IIC_IER_INT_4   0x0010  /* Interrupt(4) — IIC Bus is Not Busy */
#define IIC_IER_INT_3   0x0008  /* Interrupt(3) — Receive FIFO Full */
#define IIC_IER_INT_2   0x0004  /* Interrupt(2) — Transmit FIFO Empty */
#define IIC_IER_INT_1   0x0002  /* Interrupt(1) — Transmit Error/Slave Transmit Complete */
#define IIC_IER_INT_0   0x0001  /* Interrupt(0) — Arbitration Lost */

/**** SOFTR ****/
/* [31:4] Reserved */
#define IIC_SOFTR_RKEY          0x000F  /* Reset Key */
#define IIC_SOFTR_RKEY_Value    0x000A  /* Reset Key value for soft reset of the Interrupt registers */

/**** CR ****/
/* [31:7] Reserved */
#define IIC_CR_GC_EN    0x0040  /* General Call Enable */
#define IIC_CR_RSTA     0x0020  /* Repeated Start */
#define IIC_CR_TXAK     0x0010  /* Transmit Acknowledge Enable */
#define IIC_CR_TX       0x0008  /* Transmit/Receive Mode Select */
#define IIC_CR_MSMS     0x0004  /* Master/Slave Mode Select */
#define IIC_CR_TX_FIFO  0x0002  /* Transmit FIFO Reset */
#define IIC_CR_EN       0x0001  /* AXI IIC Enable */

/**** SR ****/
/* [31:8] Reserved */
#define IIC_SR_TX_FIFO_Empty    0x0080  /* Transmit FIFO empty */
#define IIC_SR_RX_FIFO_Empty    0x0040  /* Receive FIFO empty */
#define IIC_SR_RX_FIFO_Full     0x0020  /* Receive FIFO full */
#define IIC_SR_TX_FIFO_Full     0x0010  /* Transmit FIFO full */
#define IIC_SR_SRW              0x0008  /* Slave Read/Write */
#define IIC_SR_BB               0x0004  /* Bus Busy */
#define IIC_SR_AAS              0x0002  /* Addressed as Slave */
#define IIC_SR_ABGC             0x0001  /* Addressed By a General Call */

/**** TX_FIFO ****/
/* [31:10] Reserved */
#define IIC_TX_FIFO_Stop        0x0200  /* Stop */
#define IIC_TX_FIFO_Start       0x0100  /* Start */
#define IIC_TX_FIFO_D7_to_D0    0x00FF  /* AXI IIC Transmit Data */

/**** RX_FIFO ****/
/* [31:8] Reserved */
#define IIC_RX_FIFO_D7_to_D0    0x00FF  /* IIC Receive Data */

/**** ADR ****/
/* [31:8] Reserved */
#define IIC_ADR_Slave_Address   0x00FE  /* Address used by the IIC bus interface when in slave mode */
/* 0 Reserved */

/**** TEN_ADR ****/
/* [31:3] Reserved */
#define IIC_TEN_ADR_MSB_Slave_Address   0x0007  /* Three MSBs of the 10-bit address used by the AXI IIC bus interface when in slave mode */

/**** TX_FIFO_OCY ****/
/* [31:4] Reserved */
#define IIC_TX_FIFO_OCY_Occupancy_Value 0x000F  /* Bit[3] is the MSB. A binary value of 1001 indicates that 10 locations are full in the FIFO. */

/**** RX_FIFO_OCY ****/
/* [31:4] Reserved */
#define IIC_RX_FIFO_OCY_Occupancy_Value 0x000F  /* Bit[3] is the MSB. A binary value of 1001 implies that 10 locations are full in the FIFO. */

/**** RX_FIFO_PIRQ ****/
/* [31:4] Reserved */
#define IIC_RX_FIFO_PIRQ_Compare_Value  0x000F  /* Bit[3] is the MSB. A binary value of 1001 implies that when 10 locations in the receive FIFO are filled, the receive FIFO interrupt is set. */

/**** TSUSTA ****/
#define IIC_TSUSTA_TSUSTA   0xFFFF  /* Setup time for a repeated START condition */

/**** TSUST0 ****/
#define IIC_TSUSTO_TSUSTO   0xFFFF  /* Setup time for a repeated STOP condition */

/**** THDSTA ****/
#define IIC_THDSTA_THDSTA   0xFFFF  /* Hold time for a repeated START condition */

/**** TSUDAT ****/
#define IIC_TSUDAT_TSUDAT   0xFFFF  /* Data setup time */

/**** TBUF ****/
#define IIC_TBUF_TBUF   0xFFFF  /* Bus free time between a STOP and START condition */

/**** THIGH ****/
#define IIC_THIGH_THIGH 0xFFFF  /* High period of the scl clock */

/**** TLOW ****/
#define IIC_TLOW_TLOW   0xFFFF  /* Low period of the scl clock */

/**** THDDAT ****/
#define IIC_THDDAT_THDDAT   0xFFFF  /* Data hold time */

/*******************************     TYPES      *******************************/
typedef struct
{
    uint32_t RESERVED0[7];
    uint32_t GIE;           /* Global Interrupt Enable Register */
    uint32_t ISR;           /* Interrupt Status Register */
    uint32_t RESERVED1;
    uint32_t IER;           /* Interrupt Enable Register */
    uint32_t RESERVED2[5];
    uint32_t SOFTR;         /* Soft Reset Register */
    uint32_t RESERVED3[47];
    uint32_t CR;            /* Control Register */
    uint32_t SR;            /* Status Register */
    uint32_t TX_FIFO;       /* Transmit FIFO Register */
    uint32_t RX_FIFO;       /* Receive FIFO Register */
    uint32_t ADR;           /* Slave Address Register */
    uint32_t TX_FIFO_OCY;   /* Transmit FIFO Occupancy Register */
    uint32_t RX_FIFO_OCY;   /* Receive FIFO Occupancy Register */
    uint32_t TEN_ADR;       /* Slave Ten Bit Address Register */
    uint32_t RX_FIFO_PIRQ;  /* Receive FIFO Programmable Depth Interrupt Register */
    uint32_t GPO;           /* General Purpose Output Register */
    uint32_t TSUSTA;        /* Timing Parameter Register */
    uint32_t TSUSTO;        /* Timing Parameter Register */
    uint32_t THDSTA;        /* Timing Parameter Register */
    uint32_t TSUDAT;        /* Timing Parameter Register */
    uint32_t TBUF;          /* Timing Parameter Register */
    uint32_t THIGH;         /* Timing Parameter Register */
    uint32_t TLOW;          /* Timing Parameter Register */
    uint32_t THDDAT;        /* Timing Parameter Register */
}axi_iic_t;

/*******************************   FUNCTIONS    *******************************/
uint8_t iic_write(axi_iic_t * axi, uint8_t address, uint8_t * data, uint8_t length);
uint8_t iic_read(axi_iic_t * axi, uint8_t address, uint8_t * data, uint8_t length);

#endif
