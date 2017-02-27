/*******************************************************************************/
/**
*      @file : mpu9250.h
*   @version : 0
*      @date : February 28, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/
#ifndef MPU9250_H_
#define MPU9250_H_


/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "xiicps.h"
/*******************************     MACROS     *******************************/
/**** BITS ****/
#define BIT0    (0x01)
#define BIT1    (0x02)
#define BIT2    (0x04)
#define BIT3    (0x08)
#define BIT4    (0x10)
#define BIT5    (0x20)
#define BIT6    (0x40)
#define BIT7    (0x80)

/**** I²C ADDRESS ****/
#define MPU9250_IIC_AGT     (0xD1)
#define MPU9250_IIC_MAG     (0x0C)

/**** Register Map for Gyroscope and Accelerometer ****/
#define MPU9250_SELF_TEST_X_GYRO    (0x00)  /* R/W */
#define MPU9250_SELF_TEST_Y_GYRO    (0x01)  /* R/W */
#define MPU9250_SELF_TEST_Z_GYRO    (0x02)  /* R/W */
#define MPU9250_SELF_TEST_X_ACCEL   (0x0D)  /* R/W */
#define MPU9250_SELF_TEST_Y_ACCEL   (0x0E)  /* R/W */
#define MPU9250_SELF_TEST_Z_ACCEL   (0x0F)  /* R/W */
#define MPU9250_XG_OFFSET_H         (0x13)  /* R/W */
#define MPU9250_XG_OFFSET_L         (0x14)  /* R/W */
#define MPU9250_YG_OFFSET_H         (0x15)  /* R/W */
#define MPU9250_YG_OFFSET_L         (0x16)  /* R/W */
#define MPU9250_ZG_OFFSET_H         (0x17)  /* R/W */
#define MPU9250_ZG_OFFSET_L         (0x18)  /* R/W */
#define MPU9250_SMPLRT_DIV          (0x19)  /* R/W */
#define MPU9250_CONFIG              (0x1A)  /* R/W */
    #define MPU9250_DLPF_CFG            (BIT2|BIT1|BIT0)
    #define MPU9250_EXT_SYNC_SET        (BIT5|BIT4|BIT3)
    #define MPU9250_FIFO_MODE           (BIT6)
#define MPU9250_GYRO_CONFIG         (0x1B)  /* R/W */
    #define MPU9250_FCHOICE_B           (BIT1|BIT0)
    #define MPU9250_GYRO_FS_SEL         (BIT4|BIT3)
    #define MPU9250_ZGYRO_CTEN          (BIT5)
    #define MPU9250_YGYRO_CTEN          (BIT6)
    #define MPU9250_XGYRO_CTEN          (BIT7)
#define MPU9250_ACCEL_CONFIG        (0x1C)  /* R/W */
    #define MPU9250_ACCEL_FS_SEL        (BIT4|BIT3)
    #define MPU9250_AZ_ST_EN            (BIT5)
    #define MPU9250_AY_ST_EN            (BIT6)
    #define MPU9250_AX_ST_EN            (BIT7)
#define MPU9250_ACCEL_CONFIG_2      (0x1D)  /* R/W */
    #define MPU9250_A_DLPF_CFG          (BIT1|BIT0)
    #define MPU9250_ACCEL_FCHOICE_B     (BIT3|BIT2)
#define MPU9250_LP_ACCEL_ODR        (0x1E)  /* R/W */
    #define MPU9250_LPOSC_CLKSEL        (BIT3|BIT2|BIT1|BIT0)
#define MPU9250_WOM_THR             (0x1F)  /* R/W */
#define MPU9250_FIFO_EN             (0x23)  /* R/W */
    #define MPU9250_SLV0                (BIT0)
    #define MPU9250_SLV1                (BIT1)
    #define MPU9250_SLV2                (BIT2)
    #define MPU9250_ACCEL               (BIT3)
    #define MPU9250_GYRO_ZOUT           (BIT4)
    #define MPU9250_GYRO_YOUT           (BIT5)
    #define MPU9250_GYRO_XOUT           (BIT6)
    #define MPU9250_TEMP_FIFO_EN        (BIT7)
#define MPU9250_I2C_MST_CTRL        (0x24)  /* R/W */
    #define MPU9250_I2C_MST_CLK         (BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_MST_P_NSR       (BIT4)
    #define MPU9250_SLV_3_FIFO_EN       (BIT5)
    #define MPU9250_WAIT_FOR_ES         (BIT6)
    #define MPU9250_MULT_MST_EN         (BIT7)
#define MPU9250_I2C_SLV0_ADDR       (0x25)  /* R/W */
    #define MPU9250_I2C_ID_0            (BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_SLV0_RNW        (BIT7)
#define MPU9250_I2C_SLV0_REG        (0x26)  /* R/W */
#define MPU9250_I2C_SLV0_CTRL       (0x27)  /* R/W */
    #define MPU9250_I2C_SLV0_LENG       (BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_SLV0_GRP        (BIT4)
    #define MPU9250_I2C_SLV0_REG_DIS    (BIT5)
    #define MPU9250_I2C_SLV0_BYTE_SW    (BIT6)
    #define MPU9250_I2C_SLV0_EN         (BIT7)
#define MPU9250_I2C_SLV1_ADDR       (0x28)  /* R/W */
    #define MPU9250_I2C_ID_1            (BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_SLV1_RNW        (BIT7)
#define MPU9250_I2C_SLV1_REG        (0x29)  /* R/W */
#define MPU9250_I2C_SLV1_CTRL       (0x2A)  /* R/W */
    #define MPU9250_I2C_SLV1_LENG       (BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_SLV1_GRP        (BIT4)
    #define MPU9250_I2C_SLV1_REG_DIS    (BIT5)
    #define MPU9250_I2C_SLV1_BYTE_SW    (BIT6)
    #define MPU9250_I2C_SLV1_EN         (BIT7)
#define MPU9250_I2C_SLV2_ADDR       (0x2B)  /* R/W */
    #define MPU9250_I2C_ID_2            (BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_SLV2_RNW        (BIT7)
#define MPU9250_I2C_SLV2_REG        (0x2C)  /* R/W */
#define MPU9250_I2C_SLV2_CTRL       (0x2D)  /* R/W */
    #define MPU9250_I2C_SLV2_LENG       (BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_SLV2_GRP        (BIT4)
    #define MPU9250_I2C_SLV2_REG_DIS    (BIT5)
    #define MPU9250_I2C_SLV2_BYTE_SW    (BIT6)
    #define MPU9250_I2C_SLV2_EN         (BIT7)
#define MPU9250_I2C_SLV3_ADDR       (0x2E)  /* R/W */
    #define MPU9250_I2C_ID_3            (BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_SLV3_RNW        (BIT7)
#define MPU9250_I2C_SLV3_REG        (0x2F)  /* R/W */
#define MPU9250_I2C_SLV3_CTRL       (0x30)  /* R/W */
    #define MPU9250_I2C_SLV3_LENG       (BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_SLV3_GRP        (BIT4)
    #define MPU9250_I2C_SLV3_REG_DIS    (BIT5)
    #define MPU9250_I2C_SLV3_BYTE_SW    (BIT6)
    #define MPU9250_I2C_SLV3_EN         (BIT7)
#define MPU9250_I2C_SLV4_ADDR       (0x31)  /* R/W */
    #define MPU9250_I2C_ID_4            (BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_SLV4_RNW        (BIT7)
#define MPU9250_I2C_SLV4_REG        (0x32)  /* R/W */
#define MPU9250_I2C_SLV4_DO         (0x33)  /* R/W */
#define MPU9250_I2C_SLV4_CTRL       (0x34)  /* R/W */
    #define MPU9250_I2C_SLV4_DLY        (BIT4|BIT3|BIT2|BIT1|BIT0)
    #define MPU9250_I2C_SLV4_REG_DIS    (BIT5)
    #define MPU9250_SLV4_DONE_INT_EN    (BIT6)
    #define MPU9250_I2C_SLV4_EN         (BIT7)
#define MPU9250_I2C_SLV4_DI         (0x35)  /* R   */
#define MPU9250_I2C_MST_STATUS      (0x36)  /* R   */
    #define MPU9250_I2C_SLV0_NACK       (BIT0)
    #define MPU9250_I2C_SLV1_NACK       (BIT1)
    #define MPU9250_I2C_SLV2_NACK       (BIT2)
    #define MPU9250_I2C_SLV3_NACK       (BIT3)
    #define MPU9250_I2C_SLV4_NACK       (BIT4)
    #define MPU9250_I2C_LOST_ARB        (BIT5)
    #define MPU9250_I2C_SLV4_DONE       (BIT6)
    #define MPU9250_PASS_THROUGH        (BIT7)
#define MPU9250_INT_PIN_CFG         (0x37)  /* R/W */
    #define MPU9250_BYPASS_EN           (BIT1)
    #define MPU9250_FSYNC_INT_MODE_EN   (BIT2)
    #define MPU9250_ACTL_FSYNC          (BIT3)
    #define MPU9250_INT_ANYRD_2CLEAR    (BIT4)
    #define MPU9250_LATCH_INT_EN        (BIT5)
    #define MPU9250_OPEN                (BIT6)
    #define MPU9250_ACTL                (BIT7)
#define MPU9250_INT_ENABLE          (0x38)  /* R/W */
    #define MPU9250_RAW_RDY_EN          (BIT0)
    #define MPU9250_FSYNC_INT_EN        (BIT3)
    #define MPU9250_FIFO_OFLOW_EN       (BIT4)
    #define MPU9250_WOM_EN              (BIT6)
#define MPU9250_INT_STATUS          (0x3A)  /* R   */
    #define MPU9250_RAW_DATA_RDY_INT    (BIT0)
    #define MPU9250_FSYNC_INT           (BIT3)
    #define MPU9250_FIFO_OFLOW_INT      (BIT4)
    #define MPU9250_WOM_INT             (BIT6)
#define MPU9250_ACCEL_XOUT_H        (0x3B)  /* R   */
#define MPU9250_ACCEL_XOUT_L        (0x3C)  /* R   */
#define MPU9250_ACCEL_YOUT_H        (0x3D)  /* R   */
#define MPU9250_ACCEL_YOUT_L        (0x3E)  /* R   */
#define MPU9250_ACCEL_ZOUT_H        (0x3F)  /* R   */
#define MPU9250_ACCEL_ZOUT_L        (0x40)  /* R   */
#define MPU9250_TEMP_OUT_H          (0x41)  /* R   */
#define MPU9250_TEMP_OUT_L          (0x42)  /* R   */
#define MPU9250_GYRO_XOUT_H         (0x43)  /* R   */
#define MPU9250_GYRO_XOUT_L         (0x44)  /* R   */
#define MPU9250_GYRO_YOUT_H         (0x45)  /* R   */
#define MPU9250_GYRO_YOUT_L         (0x46)  /* R   */
#define MPU9250_GYRO_ZOUT_H         (0x47)  /* R   */
#define MPU9250_GYRO_ZOUT_L         (0x48)  /* R   */
#define MPU9250_EXT_SENS_DATA_00    (0x49)  /* R   */
#define MPU9250_EXT_SENS_DATA_01    (0x4A)  /* R   */
#define MPU9250_EXT_SENS_DATA_02    (0x4B)  /* R   */
#define MPU9250_EXT_SENS_DATA_03    (0x4C)  /* R   */
#define MPU9250_EXT_SENS_DATA_04    (0x4D)  /* R   */
#define MPU9250_EXT_SENS_DATA_05    (0x4E)  /* R   */
#define MPU9250_EXT_SENS_DATA_06    (0x4F)  /* R   */
#define MPU9250_EXT_SENS_DATA_07    (0x50)  /* R   */
#define MPU9250_EXT_SENS_DATA_08    (0x51)  /* R   */
#define MPU9250_EXT_SENS_DATA_09    (0x52)  /* R   */
#define MPU9250_EXT_SENS_DATA_10    (0x53)  /* R   */
#define MPU9250_EXT_SENS_DATA_11    (0x54)  /* R   */
#define MPU9250_EXT_SENS_DATA_12    (0x55)  /* R   */
#define MPU9250_EXT_SENS_DATA_13    (0x56)  /* R   */
#define MPU9250_EXT_SENS_DATA_14    (0x57)  /* R   */
#define MPU9250_EXT_SENS_DATA_15    (0x58)  /* R   */
#define MPU9250_EXT_SENS_DATA_16    (0x59)  /* R   */
#define MPU9250_EXT_SENS_DATA_17    (0x5A)  /* R   */
#define MPU9250_EXT_SENS_DATA_18    (0x5B)  /* R   */
#define MPU9250_EXT_SENS_DATA_19    (0x5C)  /* R   */
#define MPU9250_EXT_SENS_DATA_20    (0x5D)  /* R   */
#define MPU9250_EXT_SENS_DATA_21    (0x5E)  /* R   */
#define MPU9250_EXT_SENS_DATA_22    (0x5F)  /* R   */
#define MPU9250_EXT_SENS_DATA_23    (0x60)  /* R   */
#define MPU9250_I2C_SLV0_DO         (0x63)  /* R/W */
#define MPU9250_I2C_SLV1_DO         (0x64)  /* R/W */
#define MPU9250_I2C_SLV2_DO         (0x65)  /* R/W */
#define MPU9250_I2C_SLV3_DO         (0x66)  /* R/W */
#define MPU9250_I2C_MST_DELAY_CTRL  (0x67)  /* R/W */
    #define MPU9250_I2C_SLV0_DLY_EN     (BIT0)
    #define MPU9250_I2C_SLV1_DLY_EN     (BIT1)
    #define MPU9250_I2C_SLV2_DLY_EN     (BIT2)
    #define MPU9250_I2C_SLV3_DLY_EN     (BIT3)
    #define MPU9250_I2C_SLV4_DLY_EN     (BIT4)
    #define MPU9250_DELAY_ES_SHADOW     (BIT7)
#define MPU9250_SIGNAL_PATH_RESET   (0x68)  /* R/W */
    #define MPU9250_TEMP_RST            (BIT0)
    #define MPU9250_ACCEL_RST           (BIT1)
    #define MPU9250_GYRO_RST            (BIT2)
#define MPU9250_MOT_DETECT_CTRL     (0x69)  /* R/W */
    #define MPU9250_ACCEL_INTEL_MODE    (BIT6)
    #define MPU9250_ACCEL_INTEL_EN      (BIT7)
#define MPU9250_USER_CTRL           (0x6A)  /* R/W */
    #define MPU9250_SIG_COND_RST        (BIT0)
    #define MPU9250_I2C_MST_RST         (BIT1)
    #define MPU9250_FIFO_RST            (BIT2)
    #define MPU9250_I2C_IF_DIS          (BIT4)
    #define MPU9250_I2C_MST_EN          (BIT5)
    #define MPU9250_CTRL_FIFO_EN        (BIT6)
#define MPU9250_PWR_MGMT_1          (0x6B)  /* R/W */
    #define MPU9250_CLKSEL              (BIT2|BIT1|BIT0)
    #define MPU9250_PD_PTAT             (BIT3)
    #define MPU9250_GYRO_STANDBY        (BIT4)
    #define MPU9250_CYCLE               (BIT5)
    #define MPU9250_SLEEP               (BIT6)
    #define MPU9250_H_RESET             (BIT7)
#define MPU9250_PWR_MGMT_2          (0x6C)  /* R/W */
    #define MPU9250_DIS_ZG              (BIT0)
    #define MPU9250_DIS_YG              (BIT1)
    #define MPU9250_DIS_XG              (BIT2)
    #define MPU9250_DIS_ZA              (BIT3)
    #define MPU9250_DIS_YA              (BIT4)
    #define MPU9250_DIS_XA              (BIT5)
#define MPU9250_FIFO_COUNTH         (0x72)  /* R/W */
    #define MPU9250_FIFO_CNT            (BIT4|BIT3|BIT2|BIT1|BIT0)
#define MPU9250_FIFO_COUNTL         (0x73)  /* R/W */
#define MPU9250_FIFO_R_W            (0x74)  /* R/W */
#define MPU9250_WHO_AM_I            (0x75)  /* R   */
#define MPU9250_XA_OFFSET_H         (0x77)  /* R/W */
#define MPU9250_XA_OFFSET_L         (0x78)  /* R/W */
    #define MPU9250_XA_OFFS             (BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1)
#define MPU9250_YA_OFFSET_H         (0x7A)  /* R/W */
#define MPU9250_YA_OFFSET_L         (0x7B)  /* R/W */
    #define MPU9250_YA_OFFS             (BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1)
#define MPU9250_ZA_OFFSET_H         (0x7D)  /* R/W */
#define MPU9250_ZA_OFFSET_L         (0x7E)  /* R/W */
    #define MPU9250_ZA_OFFS             (BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1)

/**** Register Map for Magnetometer ****/
#define MPU9250_MAG_WIA             (0x00) /* R   */
#define MPU9250_MAG_INFO            (0x01) /* R   */
#define MPU9250_MAG_ST1             (0x02) /* R   */
    #define MPU9250_MAG_DRDY            (BIT0)  /* Data Ready */
    #define MPU9250_MAG_DOR             (BIT1)  /* Data Overrun */
#define MPU9250_MAG_HXL             (0x03) /* R   */
#define MPU9250_MAG_HXH             (0x04) /* R   */
#define MPU9250_MAG_HYL             (0x05) /* R   */
#define MPU9250_MAG_HYH             (0x06) /* R   */
#define MPU9250_MAG_HZL             (0x07) /* R   */
#define MPU9250_MAG_HZH             (0x08) /* R   */
#define MPU9250_MAG_ST2             (0x09) /* R   */
    #define MPU9250_MAG_HOFL            (BIT3)  /* Magnetic sensor overflow */
    #define MPU9250_MAG_BITM            (BIT4)  /* Output bit setting (mirror) */
#define MPU9250_MAG_CNTL1           (0x0A) /* R/W */
    #define MPU9250_MAG_MODE            (BIT3|BIT2|BIT1|BIT0)
        #define MPU9250_MAG_MODE0           (0x00)  /* Power-down mode */
        #define MPU9250_MAG_MODE1           (BIT0)  /* Single measurement mode */
        #define MPU9250_MAG_MODE2           (BIT1)  /* Continuous measurement mode 1 */
        #define MPU9250_MAG_MODE3           (BIT2|BIT1) /* Continuous measurement mode 2 */
        #define MPU9250_MAG_MODE4           (BIT2)  /* External trigger measurement mode */
        #define MPU9250_MAG_MODE5           (BIT3)  /* Self-test mode */
        #define MPU9250_MAG_MODE6           (BIT3|BIT2|BIT1|BIT0)   /* Fuse ROM access mode */
    #define MPU9250_MAG_BIT             (BIT4)  /* Output bit setting  */
#define MPU9250_MAG_CNTL2           (0x0B) /* R/W */
    #define MPU9250_MAG_SRST            (BIT0)  /* Soft reset */
#define MPU9250_MAG_ASTC            (0x0C) /* R/W */
    #define MPU9250_MAG_SELF            (BIT6)  /* Self-test control */
#define MPU9250_MAG_I2CDIS          (0x0F) /* R/W */
    #define MPU9250_MAG_I2CDIS_VAL      (BIT4|BIT3|BIT1|BIT0)   /* This register disables I2
C bus interface */
#define MPU9250_MAG_ASAX            (0x10) /* R   */
#define MPU9250_MAG_ASAY            (0x11) /* R   */
#define MPU9250_MAG_ASAZ            (0x12) /* R   */

/***************** Macros (Inline Functions) Definitions **********************/
/******************************************************************************/
/**
* Check if the data is in the specified range
*
* @param    x is the value to check
* @param    min is the minimum value that x must be equal or bigger
* @param    max is the maximum value that x must be equal or smaller
*
* @return
*           - TRUE if the value is included in teh specified range
*           - FALSE otherwise
*
* @note     C-Style signature:
*           int in_range(<type> x, <type> min, <type> max)
*
*******************************************************************************/
#define in_range(x, min, max)   (((x) >= (min) && (x) <= (max))? TRUE : FALSE)

/******************************************************************************/
/**
* Write a byte to the mpu9250 from a specified address
*
* @param    iic_mpu9250 is a pointer to the XIicPs instance inside the mpu9250_t
*           instance (iic_mpu9250 or iic_mpu9250_aux).
* @param    register_addr is the register address where data must be write
* @param    byte is the byte that will be write in the mpu9250
*
* @return   -1 if an error occured else 0
*
* @note     C-Style signature:
*           int8_t mpu9250_write_byte(XIicPs * iic_mpu9250, const uint8_t
*           register_addr, const uint8_t * byte)
*
*******************************************************************************/
#define mpu9250_write_byte(iic_mpu9250, register_addr, byte)  mpu9250_write_data(iic_mpu9250, register_addr, (uint8_t *)byte, 1)

/******************************************************************************/
/**
* Read a byte from the mpu9250 at a specified address
*
* @param    iic_mpu9250 is a pointer to the XIicPs instance inside the mpu9250_t
*           instance (iic_mpu9250 or iic_mpu9250_aux).
* @param    register_addr is the register address where data must be read
* @param    byte is the byte that will be read in the mpu9250
*
* @return   -1 if an error occured else 0
*
* @note     C-Style signature:
*           int8_t mpu9250_read_byte(XIicPs * iic_mpu9250, const uint8_t
*           register_addr, uint8_t * byte)
*
*******************************************************************************/
#define mpu9250_read_byte(iic_mpu9250, register_addr, byte)  mpu9250_read_data(iic_mpu9250, register_addr, (uint8_t [])byte, 1)

/*******************************     TYPES      *******************************/
typedef struct
{
    float x;
    float y;
    float z;
}axi_3d_t;

typedef struct
{
    /* iic */
    XIicPs iic_mpu9250;
    XIicPs iic_aux_mpu9250;
    /* Gyroscope Features */
    uint8_t  gy_full_scale      : 2;
    uint8_t  gy_low_pass_filter : 3;
    axi_3d_t gy_data; /* °/s */
    /* Accelerometer Features */
    uint8_t  acc_full_scale      : 2;
    uint8_t  acc_low_pass_filter : 3;
    axi_3d_t acc_data; /* g */
    /* Magnetometer Features */
    axi_3d_t mag_data; /* µT */
    /* Additional Features */
    float    temp_data; /* °C */
}mpu9250_t;
/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/

#endif
