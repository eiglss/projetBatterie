/*******************************************************************************/
/**
*      @file : mpu9250.h
*   @version : 0.2
*      @date : February 28, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "iic.h"

#ifndef MPU9250_H_
#define MPU9250_H_

/*******************************    EXEMPLE     *******************************/
/* Exemple of how to use */
/**
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "drivers/mpu9250.h"

int main(void)
{
    // local declaration
    mpu9250_t mpu9250;
    ak8963_t ak8963;
    // initialization
    init_platform();
    // Program statement
    if(mpu9250_initialization(&mpu9250, IIC_0, MPU9250_IIC) == -1)
    {
        printf("Failed to initialize MPU9250.\r\n");
        return EXIT_FAILURE;
    }
    if(ak8963_initialization(&ak8963, IIC_0, AK8963_ADDR) == -1)
    {
        printf("Failed to initialize MPU9250.\r\n");
        return EXIT_FAILURE;
    }
    while(!0)
    {
        if(mpu9250_read_all(&mpu9250) == -1)
        {
            printf("Failed read data from MPU9250.\r\n");
        }
        else
        {
            // data have been read correctly
        }
        switch(ak8963_read_mag(&ak8963))
        {
            case TRUE:
            {
                // data have been read correctly
            }
            break;
            case FALSE:
            {
                // overflow occurred or data are not ready
            }
            break;
            case -1:
            default:
            {
                printf("Failed read data from AK8963.\r\n");
            }
        }
    }
    cleanup_platform();
    return EXIT_SUCCESS;
}
**/

/*******************************     MACROS     *******************************/
/**** TRUE & FALSE ****/

#ifndef FALSE
    #define FALSE   (0)
#endif
#ifndef TRUE
    #define TRUE (!FALSE)
#endif

/**** BITS ****/
#ifndef BIT0
	#define BIT0	0x01
#endif
#ifndef BIT1
	#define BIT1	0x02
#endif
#ifndef BIT2
	#define BIT2	0x04
#endif
#ifndef BIT3
	#define BIT3	0x08
#endif
#ifndef BIT4
	#define BIT4	0x10
#endif
#ifndef BIT5
	#define BIT5	0x20
#endif
#ifndef BIT6
	#define BIT6	0x40
#endif
#ifndef BIT7
	#define BIT7	0x80
#endif

/**** IIC ADDRESS ****/
/* MPU9250 */
#define MPU9250_AD0 (0)
#define MPU9250_IIC (0x68|MPU9250_AD0)
/* AK8963 */
#define AK8963_ADDR (0x0C)

/**** Register Map for Gyroscope and Accelerometer (MPU9250) ****/
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

/**** Register Map for Magnetometer (AK8963) ****/
#define AK8963_WIA              (0x00) /* R   */
#define AK8963_INFO             (0x01) /* R   */
#define AK8963_ST1              (0x02) /* R   */
    #define AK8963_MAG_DRDY         (BIT0)  /* Data Ready */
    #define AK8963_MAG_DOR          (BIT1)  /* Data Overrun */
#define AK8963_HXL              (0x03) /* R   */
#define AK8963_HXH              (0x04) /* R   */
#define AK8963_HYL              (0x05) /* R   */
#define AK8963_HYH              (0x06) /* R   */
#define AK8963_HZL              (0x07) /* R   */
#define AK8963_HZH              (0x08) /* R   */
#define AK8963_ST2              (0x09) /* R   */
    #define AK8963_MAG_HOFL         (BIT3)  /* Magnetic sensor overflow */
    #define AK8963_MAG_BITM         (BIT4)  /* Output bit setting (mirror) */
#define AK8963_CNTL1            (0x0A) /* R/W */
    #define AK8963_MAG_MODE         (BIT3|BIT2|BIT1|BIT0)
        #define AK8963_MAG_MODE0        (0x00)  /* Power-down mode */
        #define AK8963_MAG_MODE1        (BIT0)  /* Single measurement mode */
        #define AK8963_MAG_MODE2        (BIT1)  /* Continuous measurement mode 1 */
        #define AK8963_MAG_MODE3        (BIT2|BIT1) /* Continuous measurement mode 2 */
        #define AK8963_MAG_MODE4        (BIT2)  /* External trigger measurement mode */
        #define AK8963_MAG_MODE5        (BIT3)  /* Self-test mode */
        #define AK8963_MAG_MODE6        (BIT3|BIT2|BIT1|BIT0)   /* Fuse ROM access mode */
    #define AK8963_MAG_BIT              (BIT4)  /* Output bit setting  */
#define AK8963_CNTL2            (0x0B) /* R/W */
    #define AK8963_MAG_SRST         (BIT0)  /* Soft reset */
#define AK8963_MAG_ASTC         (0x0C) /* R/W */
    #define AK8963_MAG_SELF         (BIT6)  /* Self-test control */
#define AK8963_MAG_I2CDIS       (0x0F) /* R/W */
    #define AK8963_MAG_I2CDIS_VAL   (BIT4|BIT3|BIT1|BIT0)   /* This register disables I2C bus interface */
#define AK8963_MAG_ASAX         (0x10) /* R   */
#define AK8963_MAG_ASAY         (0x11) /* R   */
#define AK8963_MAG_ASAZ         (0x12) /* R   */

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
	axi_iic_t * iic;
	uint8_t     address : 7;
    /* Gyroscope Features */
    uint8_t  gy_full_scale      : 2;
    axi_3d_t gy; /* °/s */
    /* Accelerometer Features */
    uint8_t  acc_full_scale      : 2;
    axi_3d_t acc; /* g */
    /* Additional Features */
    float    temp_data; /* °C */
}mpu9250_t;

typedef struct
{
    /* iic */
	axi_iic_t * iic;
	uint8_t     address : 7;
    /* Magnetometer Features */
    uint8_t  mag_full_scale : 1; /* 0: 14 bits precision; 1: 16 bits precision */
    axi_3d_t mag; /* µT */
}ak8963_t;

/*******************************   FUNCTIONS    *******************************/
/***** WRITE & READ to or from register *****/
int mpu9250_write(mpu9250_t * mpu9250, uint8_t * data, uint8_t length);
int mpu9250_read(mpu9250_t * mpu9250, uint8_t * data, uint8_t length);
int mpu9250_write_register(mpu9250_t * mpu9250, uint8_t reg_addr, uint8_t data);
int mpu9250_read_register(mpu9250_t * mpu9250, uint8_t reg_addr, uint8_t * data, uint8_t length);
int ak8963_write(ak8963_t * ak8963, uint8_t * data, uint8_t length);
int ak8963_read(ak8963_t * ak8963, uint8_t * data, uint8_t length);
int ak8963_write_register(ak8963_t * ak8963, uint8_t reg_addr, uint8_t data);
int ak8963_read_register(ak8963_t * ak8963, uint8_t reg_addr, uint8_t * data, uint8_t length);
/***** AJUSING SCALE *****/
int mpu9250_gy_scale(mpu9250_t * mpu9250, uint8_t scale);
int mpu9250_acc_scale(mpu9250_t * mpu9250, uint8_t scale);
int ak8963_mag_scale(ak8963_t * ak8963, uint8_t scale);
/***** FILTER *****/
int mpu9250_filter(mpu9250_t * mpu9250, uint8_t filter);
/**** INTERRUPTION ****/
int mpu9250_enable_int(mpu9250_t * mpu9250);
/**** INITIALIZATION ****/
int mpu9250_initialization(mpu9250_t * mpu9250, axi_iic_t * iic, uint8_t address);
int ak8963_initialization(ak8963_t * ak8963, axi_iic_t * iic, uint8_t address);
/**** CONVERSIONS ****/
void mpu9250_gy_deg_per_s(mpu9250_t * mpu9250, const int16_t x, const int16_t y, const int16_t z);
void mpu9250_acc_g(mpu9250_t * mpu9250, const int16_t x, const int16_t y, const int16_t z);
int mpu9250_temp_degC(mpu9250_t * mpu9250, const int16_t temp_out);
int ak8963_mag_uT(ak8963_t * ak8963, const int16_t x, const int16_t y, const int16_t z);
/**** READ DATA from sensor ****/
int mpu9250_read_acc(mpu9250_t * mpu9250);
int mpu9250_read_gy(mpu9250_t * mpu9250);
int mpu9250_read_temp(mpu9250_t * mpu9250);
int ak8963_read_mag(ak8963_t * ak8963);
int mpu9250_read_all(mpu9250_t * mpu9250);

#endif /* MPU9250_H_ */
