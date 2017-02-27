/*******************************************************************************/
/**
*      @file : mpu9250.c
*   @version : 0
*      @date : February 28, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdint.h>
#include "xiicps.h"
#include "mpu9250.h"
/*******************************     MACROS     *******************************/

/*******************************     TYPES      *******************************/

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
/******************************************************************************/
/**
* Write data to the mpu9250 from a specified address
*
* @param    iic_mpu9250 is a pointer to the XIicPs instance inside the mpu9250_t
*           instance (iic_mpu9250 or iic_mpu9250_aux).
* @param    register_addr is the first register address where data must be write
* @param    data is an array which contain the data that will be write in the
*           mpu9250
* @param    length is lenth of the data array
*
* @return   -1 if an error occured else 0
*
* @note     None.
*
*******************************************************************************/
int8_t mpu9250_write_data(XIicPs * iic_mpu9250, const uint8_t register_addr, const uint8_t data[], const uint8_t length)
{

    return 0;
}

/******************************************************************************/
/**
* Read data to the mpu9250 from a specified address
*
* @param    iic_mpu9250 is a pointer to the XIicPs instance inside the mpu9250_t
*           instance (iic_mpu9250 or iic_mpu9250_aux).
* @param    register_addr is the first register address where data must be read
* @param    data is an array which will contain the data that will be read in
*           the mpu9250
* @param    length is lenth of the data array
*
* @return   -1 if an error occured else 0
*
* @note     None.
*
*******************************************************************************/
int8_t mpu9250_read_data(XIicPs * iic_mpu9250, const uint8_t register_addr, uint8_t data[], const uint8_t length)
{

    return 0;
}

/******************************************************************************/
/**
* Write a 2 bytes to the mpu9250 from a specified address
*
* @param    iic_mpu9250 is a pointer to the XIicPs instance inside the mpu9250_t
*           instance (iic_mpu9250 or iic_mpu9250_aux).
* @param    register_addr is the first register address where data must be write
* @param    bytes are the 2 bytes that will be write in the mpu9250
*
* @return   -1 if an error occured else 0
*
* @note     None.
*
*******************************************************************************/
int8_t mpu9250_write_u16(XIicPs * iic_mpu9250, const uint8_t register_addr, const uint16_t bytes)
{
    uint8_t data[2] = {(int8_t)(bytes&0x00FF), (int8_t)(bytes>>8)};
    return mpu9250_write_data(iic_mpu9250, register_addr, data, 2);
}

/******************************************************************************/
/**
* Read a 2 byte from the mpu9250 at a specified address
*
* @param    iic_mpu9250 is a pointer to the XIicPs instance inside the mpu9250_t
*           instance (iic_mpu9250 or iic_mpu9250_aux).
* @param    register_addr is the register address where data must be read
* @param    bytes are the 2 byte that will be read in the mpu9250
*
* @return   -1 if an error occured else 0
*
* @note     C-Style signature:
*           int8_t mpu9250_read_u16(XIicPs * iic_mpu9250, const uint8_t
*           register_addr, uint16_t * bytes)
*
*******************************************************************************/
int8_t mpu9250_read_u16(XIicPs * iic_mpu9250, const uint8_t register_addr, uint16_t * bytes)
{
	/* local declaration */
	int8_t status;
	/* program statement */
    uint8_t data[2];
    status = mpu9250_write_data(iic_mpu9250, register_addr, data, 2);
    *bytes = (((uint16_t)data[0])<<8)|((uint16_t)data[1]);
    return status;
}

/******************************************************************************/
/**
* Enable all the sensor of the mpu9250, with no filtering and no interruption
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
*
* @return   -1 if an error occured else 0
*
* @note     iic in the mpu9250 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int8_t mpu9250_initialize(mpu9250_t * mpu9250)
{
    if(mpu9250_write_u16(&mpu9250->iic_mpu9250, MPU9250_PWR_MGMT_1, 0) == -1) return -1;
    if(mpu9250_write_byte(&mpu9250->iic_mpu9250, MPU9250_CONFIG, 0) == -1) return -1;
    if(mpu9250_write_byte(&mpu9250->iic_aux_mpu9250, MPU9250_MAG_CNTL2, MPU9250_MAG_SRST) == -1) return -1;
    if(mpu9250_write_byte(&mpu9250->iic_aux_mpu9250, MPU9250_MAG_CNTL2, MPU9250_MAG_SRST) == -1) return -1;
    return mpu9250_write_byte(&mpu9250->iic_aux_mpu9250, MPU9250_MAG_CNTL1, MPU9250_MAG_MODE2);
}

/******************************************************************************/
/**
* Transform gyroscope sensor raw data to °/s
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    x,y,z are the raw data of the gyroscope sensor for x, y & z axis
*
* @return   -1 if an error occured else 0
*
* @note     The data is automatically update in the mpu9250_t instance
*
*******************************************************************************/
int8_t mpu9250_gy_deg_per_s(mpu9250_t * mpu9250, const uint16_t x, const uint16_t y, const uint16_t z)
{
    /* local declaration */
    float scale = (32768>>mpu9250->gy_full_scale)/250.;
    /* program statment */
    if(mpu9250 != NULL)
    {
        mpu9250->gy_data.x = x/scale;
        mpu9250->gy_data.y = y/scale;
        mpu9250->gy_data.z = z/scale;
        return 0;
    }
    return -1;
}

/******************************************************************************/
/**
* Transform accelerometer sensor raw data to g (9.80665 [m/(s^2)]).
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    x,y,z are the raw data of the accelerometer sensor for x, y & z axis
*
* @return   -1 if an error occured else 0
*
* @note     The data is automatically update in the mpu9250_t instance
*
*******************************************************************************/
int8_t mpu9250_acc_g(mpu9250_t * mpu9250, const uint16_t x, const uint16_t y, const uint16_t z)
{
    /* local declaration */
    float scale = 16384>>mpu9250->acc_full_scale;
    /* program statment */
    if(mpu9250 != NULL)
    {
        mpu9250->acc_data.x = x/scale;
        mpu9250->acc_data.y = y/scale;
        mpu9250->acc_data.z = z/scale;
        return 0;
    }
    return -1;
}

/******************************************************************************/
/**
*
* Transform temprature sensor raw data to celcius degree
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    temp_out is the raw data of the temperature sensor
*
* @return   -1 if an error occured else 0
*
* @note     The data is automatically update in the mpu9250_t instance
*
*******************************************************************************/
int8_t mpu9250_temp_degC(mpu9250_t * mpu9250, const int16_t temp_out)
{
    if(mpu9250 != NULL && in_range(temp_out, -20366, 21367)) /* -40°C <= temp_out <= 85°C ? */
    {
        mpu9250->temp_data = ((temp_out)/(float)333.87+(float)21.);
        return 0;
    }
    return -1;
}

/******************************************************************************/
/**
* Transform magnetometer sensor raw data to µT
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    x,y,z are the raw data of the magnetometer sensor for x, y & z axis
*
* @return   -1 if an error occured else 0
*
* @note     The data is automatically update in the mpu9250_t instance
*
*******************************************************************************/
int8_t mpu9250_mag_uT(mpu9250_t * mpu9250, const uint16_t x, const uint16_t y, const uint16_t z)
{
    if(mpu9250 != NULL && in_range(x, -8000, 8000) && in_range(y, -8000, 8000) && in_range(z, -8000, 8000))
    {
        mpu9250->mag_data.x = x*0.6;
        mpu9250->mag_data.y = y*0.6;
        mpu9250->mag_data.z = z*0.6;
        return 0;
    }
    return -1;
}
