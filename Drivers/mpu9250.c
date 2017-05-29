/*******************************************************************************/
/**
*      @file : mpu9250.c
*   @version : 0.2
*      @date : February 28, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include "mpu9250.h"
#include <math.h>

/*******************************   FUNCTIONS    *******************************/
/******************************************************************************/
/**
* Write data to the mpu9250
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    data is an array that contain data that must be write to the mpu9250
* @param    length is the length of the data that will be write, it do not
*           Exceed data array length.
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the mpu9250 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int mpu9250_write(mpu9250_t * mpu9250, uint8_t * data, uint8_t length)
{
    while(iic_bus_is_busy(mpu9250->iic));
    return (iic_write(mpu9250->iic, mpu9250->address, data, length) == length)? 0 : -1;
}

/******************************************************************************/
/**
* Read data from the mpu9250
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    data is an array where data that have been read from the mpu9250
*           will be write.
* @param    length is the length of the data that will be read, it do not exceed
*           data array length.
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the mpu9250 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int mpu9250_read(mpu9250_t * mpu9250, uint8_t * data, uint8_t length)
{
    while(iic_bus_is_busy(mpu9250->iic));
    return (iic_read(mpu9250->iic, mpu9250->address, data, length) == length)? 0 : -1;
}

/******************************************************************************/
/**
* write data to the mpu9250, on a specified register
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    reg_addr is the register where you want to write
* @param    data is a byte that you want to write on the mpu9250
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the mpu9250 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int mpu9250_write_register(mpu9250_t * mpu9250, uint8_t reg_addr, uint8_t data)
{
    /* Local declaration */
    uint8_t tx_data[2] = {reg_addr, data};
    /* Program statement */
    return mpu9250_write(mpu9250, tx_data, 2);
}

/******************************************************************************/
/**
* Read data from the mpu9250, from a specified register
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    reg_addr is the register from where you want to read
* @param    data is an array where data that have been read from the mpu9250
*           will be write.
* @param    length is the length of the data that will be read, it do not exceed
*           data array length.
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the mpu9250 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int mpu9250_read_register(mpu9250_t * mpu9250, uint8_t reg_addr, uint8_t * data, uint8_t length)
{
    /* Local declaration */
    uint8_t tx_data[1] = {reg_addr};
    /* Program statement */
    while(iic_bus_is_busy(mpu9250->iic));
    if(iic_write(mpu9250->iic, mpu9250->address, tx_data, 1) != 1) return -1;
    return (iic_read(mpu9250->iic, mpu9250->address, data, length) == length)? 0 : -1;
}

/******************************************************************************/
/**
* Write data to the ak8963
*
* @param    ak8963 is a pointer to the ak8963_t instance
* @param    data is an array that contain data that must be write to the ak8963
* @param    length is the length of the data that will be write, it do not
*           exceed data array length.
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the ak8963 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int ak8963_write(ak8963_t * ak8963, uint8_t * data, uint8_t length)
{
    while(iic_bus_is_busy(ak8963->iic));
    return (iic_write(ak8963->iic, ak8963->address, data, length) == length)? 0 : -1;
}

/******************************************************************************/
/**
* Read data from the ak8963
*
* @param    ak8963 is a pointer to the ak8963_t instance
* @param    data is an array where data that have been read from the ak8963
*           will be write.
* @param    length is the length of the data that will be read, it do not exceed
*           data array length.
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the ak8963 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int ak8963_read(ak8963_t * ak8963, uint8_t * data, uint8_t length)
{
    while(iic_bus_is_busy(ak8963->iic));
    return (iic_read(ak8963->iic, ak8963->address, data, length) == length)? 0 : -1;
}

/******************************************************************************/
/**
* write data to the ak8963, on a specified register
*
* @param    ak8963 is a pointer to the ak8963_t instance
* @param    reg_addr is the register where you want to write
* @param    data is a byte that you want to write on the ak8963
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the ak8963 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int ak8963_write_register(ak8963_t * ak8963, uint8_t reg_addr, uint8_t data)
{
    /* Local declaration */
    uint8_t tx_data[2] = {reg_addr, data};
    /* Program statement */
    return ak8963_write(ak8963, tx_data, 2);
}

/******************************************************************************/
/**
* Read data from the ak8963, from a specified register
*
* @param    ak8963 is a pointer to the ak8963_t instance
* @param    reg_addr is the register from where you want to read
* @param    data is an array where data that have been read from the ak8963
*           will be write.
* @param    length is the length of the data that will be read, it do not exceed
*           data array length.
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the ak8963 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int ak8963_read_register(ak8963_t * ak8963, uint8_t reg_addr, uint8_t * data, uint8_t length)
{
    /* Local declaration */
    uint8_t tx_data[1] = {reg_addr};
    /* Program statement */
    while(iic_bus_is_busy(ak8963->iic));
    if(iic_write(ak8963->iic, ak8963->address, tx_data, 1) != 1) return -1;
    return (iic_read(ak8963->iic, ak8963->address, data, length) == length)? 0 : -1;
}

/******************************************************************************/
/**
* Configure the precision of the gyroscope
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    scale the precision to be setting (0: +/-250ï¿½/s; 1: +/-4g; 2: +/-8g
*           3: +/-16g)
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the mpu9250 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int mpu9250_gy_scale(mpu9250_t * mpu9250, uint8_t scale)
{
    /* local declaration */
    uint8_t gyro_config;
    /* program statement */
    if(mpu9250_read_register(mpu9250, MPU9250_GYRO_CONFIG, &gyro_config, 1) == -1) return -1;
    gyro_config &= ~MPU9250_GYRO_FS_SEL;
    gyro_config |= MPU9250_GYRO_FS_SEL&(scale<<3);
    if(mpu9250_write_register(mpu9250, MPU9250_GYRO_CONFIG, gyro_config) == -1) return -1;
    mpu9250->gy_full_scale = scale;
    return 0;
}

/******************************************************************************/
/**
* Configure the precision of the accelerometer
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    scale the precision to be setting (0: +/-2g; 1: +/-4g; 2: +/-8g
*           3: +/-16g)
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the mpu9250 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int mpu9250_acc_scale(mpu9250_t * mpu9250, uint8_t scale)
{
    /* local declaration */
    uint8_t acc_config;
    /* program statement */
    if(mpu9250_read_register(mpu9250, MPU9250_ACCEL_CONFIG, &acc_config, 1) == -1) return -1;
    acc_config &= ~MPU9250_ACCEL_FS_SEL;
    acc_config |= MPU9250_ACCEL_FS_SEL&(scale<<3);
    if(mpu9250_write_register(mpu9250, MPU9250_ACCEL_CONFIG, acc_config) == -1) return -1;
    mpu9250->acc_full_scale = scale;
    return 0;
}

/******************************************************************************/
/**
* Configure the precision of the ak8963
*
* @param    ak8963 is a pointer to the ak8963_t instance
* @param    scale the precision to be setting (0: 14bits, 1: 16bits)
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the ak8963 instance must be initialize before using this
*           function. The continuous mode 2 is configured after using this
*           function. 14 bits correspond to 0.6 ï¿½T/LSB and 16 bits to 0.15ï¿½T/LSB
*
*******************************************************************************/
int ak8963_mag_scale(ak8963_t * ak8963, uint8_t scale)
{
    /* local declaration */
    uint8_t mag_cntl1;
    /* program statement */
    if(ak8963_read_register(ak8963, AK8963_CNTL1, &mag_cntl1, 1) == -1) return -1;
    mag_cntl1 &= ~AK8963_MAG_BIT;
    mag_cntl1 |= AK8963_MAG_BIT&(scale<<4);
    if(ak8963_write_register(ak8963, AK8963_CNTL1, mag_cntl1) == -1) return -1;
    ak8963->mag_full_scale = scale;
    return 0;
}

/******************************************************************************/
/**
* Configure the mode of the ak8963
*
* @param    ak8963 is a pointer to the ak8963_t instance
* @param    mode is the mode of the ak8963
*               - AK8963_MAG_MODE0 (0000): Power-down mode
*               - AK8963_MAG_MODE1 (0001): Single measurement mode
*               - AK8963_MAG_MODE2 (0010): Continuous measurement mode 1
*               - AK8963_MAG_MODE3 (0110): Continuous measurement mode 2
*               - AK8963_MAG_MODE4 (0100): External trigger measurement mode
*               - AK8963_MAG_MODE5 (1000): Self-test mode
*               - AK8963_MAG_MODE6 (1111): Fuse ROM access mode
*               Other code settings are prohibited
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the ak8963 instance must be initialize before using this
*           function. The continuous mode 2 is configured after using this
*           function. 14 bits correspond to 0.6 ï¿½T/LSB and 16 bits to 0.15ï¿½T/LSB
*
*******************************************************************************/
int ak8963_mag_mode(ak8963_t * ak8963, uint8_t mode)
{
    /* local declaration */
    uint8_t mag_cntl1;
    /* program statement */
    if(ak8963_read_register(ak8963, AK8963_CNTL1, &mag_cntl1, 1) == -1) return -1;
    mag_cntl1 &= ~AK8963_MAG_MODE;
    mag_cntl1 |= AK8963_MAG_MODE&mode;
    return ak8963_write_register(ak8963, AK8963_CNTL1, mag_cntl1);
}

/******************************************************************************/
/**
* Configure the filter of the mpu9250
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    filter the filter to be setting
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the ak8963 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int mpu9250_filter(mpu9250_t * mpu9250, uint8_t filter)
{
    /* local declaration */
    uint8_t config;
    /* program statement */
    if(mpu9250_read_register(mpu9250, MPU9250_CONFIG, &config, 1) == -1) return -1;
    config &= ~MPU9250_DLPF_CFG;
    config |= MPU9250_DLPF_CFG&filter;
    if(mpu9250_write_register(mpu9250, MPU9250_CONFIG, config) == -1) return -1;
    if(mpu9250_read_register(mpu9250, MPU9250_GYRO_CONFIG, &config, 1) == -1) return -1;
    return mpu9250_write_register(mpu9250, MPU9250_GYRO_CONFIG, config|MPU9250_FCHOICE_B);
}

/******************************************************************************/
/**
* Enable interruption pin to indicate when data are ready on the mpu9250
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the mpu9250 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int mpu9250_enable_int(mpu9250_t * mpu9250)
{
    /* local declaration */
    uint8_t int_cfg;
    /* program statement */
    if(mpu9250_read_register(mpu9250, MPU9250_INT_PIN_CFG, &int_cfg, 1) == -1) return -1;
    if(mpu9250_write_register(mpu9250, MPU9250_INT_PIN_CFG, int_cfg|(MPU9250_INT_ANYRD_2CLEAR|MPU9250_BYPASS_EN)) == -1) return -1;
    if(mpu9250_read_register(mpu9250, MPU9250_INT_ENABLE, &int_cfg, 1) == -1) return -1;
    return mpu9250_write_register(mpu9250, MPU9250_INT_ENABLE, int_cfg|MPU9250_RAW_RDY_EN);
}

/******************************************************************************/
/**
* Enable all the sensor of the mpu9250, with no filtering and no interruption
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the mpu9250 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int mpu9250_initialization(mpu9250_t * mpu9250, axi_iic_t * iic, uint8_t address)
{
    mpu9250->iic = iic;
    mpu9250->address = address;
    if(mpu9250_write_register(mpu9250, MPU9250_PWR_MGMT_1, 0) == -1) return -1;
    if(mpu9250_write_register(mpu9250, MPU9250_CONFIG, 0) == -1) return -1;
    if(mpu9250_gy_scale(mpu9250, 3) == -1) return -1;
    if(mpu9250_acc_scale(mpu9250, 0) == -1) return -1;
    if(mpu9250_filter(mpu9250, 5) == -1) return -1;
    return mpu9250_write_register(mpu9250, MPU9250_INT_PIN_CFG, MPU9250_BYPASS_EN); /* allow access to ak8963 */
}

/******************************************************************************/
/**
* initialize ak8963, with 16 bits precision and continuous mode 2
*
* @param    ak8963 is a pointer to the ak8963_t instance
*
* @return   -1 if an error occurred else 0
*
* @note     IIC in the ak8963 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int ak8963_initialization(ak8963_t * ak8963, axi_iic_t * iic, uint8_t address)
{
    ak8963->iic = iic;
    ak8963->address = address;
    if(ak8963_write_register(ak8963, AK8963_CNTL2, AK8963_MAG_SRST)) return -1; /* Soft reset */
    if(ak8963_mag_scale(ak8963, 1)) return -1; /* 16-bit output */
    if(ak8963_mag_mode(ak8963, AK8963_MAG_MODE3) == -1) return -1; /* continuous mode 2 */
    return ak8963_mag_scale(ak8963, 1); /* 16 bits precision */
}

/******************************************************************************/
/**
* Transform gyroscope sensor raw data to ï¿½/s
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    x,y,z are the raw data of the gyroscope sensor for x, y & z axis
*
* @return   None.
*
* @note     The data is automatically update in the mpu9250_t instance
*
*******************************************************************************/
void mpu9250_gy_deg_per_s(mpu9250_t * mpu9250, const int16_t x, const int16_t y, const int16_t z)
{
    /* Local declaration */
    float scale = (32768>>mpu9250->gy_full_scale)/250.;
    /* Program statement */
    mpu9250->gy.x = x/scale;
    mpu9250->gy.y = y/scale;
    mpu9250->gy.z = z/scale;
}

/******************************************************************************/
/**
* Transform accelerometer sensor raw data to g (9.80665 [m/(s^2)]).
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    x,y,z are the raw data of the accelerometer sensor for x, y & z axis
*
* @return   None.
*
* @note     The data is automatically update in the mpu9250_t instance
*
*******************************************************************************/
void mpu9250_acc_g(mpu9250_t * mpu9250, const int16_t x, const int16_t y, const int16_t z)
{
    /* Local declaration */
    float scale = 16384>>mpu9250->acc_full_scale;
    /* Program statement */
    mpu9250->acc.x = x/scale;
    mpu9250->acc.y = y/scale;
    mpu9250->acc.z = z/scale;
}

/******************************************************************************/
/**
*
* Transform temperature sensor raw data to celsius degree
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    temp_out is the raw data of the temperature sensor
*
* @return   -1 if an error occurred else 0
*
* @note     The data is automatically update in the mpu9250_t instance
*
*******************************************************************************/
int mpu9250_temp_degC(mpu9250_t * mpu9250, const int16_t temp_out)
{
    if(in_range(temp_out, -20366, 21367)) /* -40ï¿½C <= temp_out <= 85ï¿½C ? */
    {
        mpu9250->temp_data = ((temp_out)/(float)333.87+(float)21.);
        return 0;
    }
    return -1;
}

/******************************************************************************/
/**
* Transform magnetometer sensor raw data to ï¿½T
*
* @param    ak8963 is a pointer to the ak8963_t instance
* @param    x,y,z are the raw data of the magnetometer sensor for x, y & z axis
*
* @return   -1 if an error occurred else 0
*
* @note     The data is automatically update in the mpu9250_t instance
*
*******************************************************************************/
int ak8963_mag_uT(ak8963_t * ak8963, const int16_t x, const int16_t y, const int16_t z)
{
    /* Local declaration */
    int16_t range = (ak8963->mag_full_scale)? 32760 : 8190;
    float scale = (ak8963->mag_full_scale)? 0.15 : 0.6;
    /* prorgam statement */
    if(in_range((int16_t)x, -range, range) && in_range((int16_t)y, -range, range) && in_range((int16_t)z, -range, range))
    {
        ak8963->mag.x = x*scale;
        ak8963->mag.y = y*scale;
        ak8963->mag.z = z*scale;
        return 0;
    }
    return -1;
}


/******************************************************************************/
/**
* compute the angle between the vector u+v+w and the main axis of u
*
* @param    ang_u is a pointer to the solution of the problem
* @param    u,v,w are vector needed to compute angle
*
* @return   -1 if an error occurred else 0
*
* @note     to get a coherent result be sure that the three vectors are on
*           different axis
*
*******************************************************************************/
static int vector_to_angle(float * ang_u, float u, float v, float w)
{
    if(u == 0)
    {
        *ang_u = 90.;
    }
    else if(u > 0)
    {
        *ang_u = atan(sqrt(v*v+w*w)/u)*180./M_PI;
    }
    else if(u < 0)
    {
        *ang_u = atan(sqrt(v*v+w*w)/u)*180./M_PI+180;
    }
    else
    {
        return -1;
    }
    *ang_u = (v >= 0)? *ang_u: -(*ang_u);
    return 0;
}

/******************************************************************************/
/**
* Transform magnetometer sensor raw data to degree (compass) and update ÂµT data
*
* @param    ak8963 is a pointer to the ak8963_t instance
* @param    x,y,z are the raw data of the magnetometer sensor for x, y & z axis
*
* @return   -1 if an error occurred else 0
*
* @note     The data is automatically update in the mpu9250_t instance
*
*******************************************************************************/
int ak8963_mag_compass(ak8963_t * ak8963, const int16_t x, const int16_t y, const int16_t z)
{
    if(ak8963_mag_uT(ak8963, x, y, z) == -1) return -1;
    vector_to_angle(&ak8963->compass.x, x, y, z);
    vector_to_angle(&ak8963->compass.y, y, x, z);
    vector_to_angle(&ak8963->compass.z, z, x, z);
    return 0;
}


/******************************************************************************/
/**
* Read the raw data of the accelerometer of the MPU9250 on the 3 axis
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
*
* @return   -1 if an error occurred else 0
*
* @note     The data is automatically update in the mpu9250_t instance.
*
*******************************************************************************/
int mpu9250_read_acc(mpu9250_t * mpu9250)
{
    /* Local declaration */
    uint8_t acc[6];
    uint16_t x, y, z;
    /* Program statement */
    if(mpu9250_read_register(mpu9250, MPU9250_ACCEL_XOUT_H, acc, 6) == -1) return -1;
    x = (uint16_t)acc[0]<<8|(uint16_t)acc[1];
    y = (uint16_t)acc[2]<<8|(uint16_t)acc[3];
    z = (uint16_t)acc[4]<<8|(uint16_t)acc[5];
    mpu9250_acc_g(mpu9250, x, y, z);
    return 0;
}

/******************************************************************************/
/**
* Read the raw data of the gyroscope of the MPU9250 on the 3 axis
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
*
* @return   -1 if an error occurred else 0
*
* @note     The data is automatically update in the mpu9250_t instance.
*
*******************************************************************************/
int mpu9250_read_gy(mpu9250_t * mpu9250)
{
    /* Local declaration */
    uint8_t gy[6];
    uint16_t x, y, z;
    /* Program statement */
    if(mpu9250_read_register(mpu9250, MPU9250_GYRO_XOUT_H, gy, 6) == -1) return -1;
    x = (uint16_t)gy[0]<<8|(uint16_t)gy[1];
    y = (uint16_t)gy[2]<<8|(uint16_t)gy[3];
    z = (uint16_t)gy[4]<<8|(uint16_t)gy[5];
    mpu9250_gy_deg_per_s(mpu9250, x, y, z);
    return 0;
}

/******************************************************************************/
/**
* Read the raw data of the temperature of the MPU9250
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
*
* @return   -1 if an error occurred else 0
*
* @note     The data is automatically update in the mpu9250_t instance.
*
*******************************************************************************/
int mpu9250_read_temp(mpu9250_t * mpu9250)
{
    /* Local declaration */
    uint8_t temp[2];
    /* Program statement */
    if(mpu9250_read_register(mpu9250, MPU9250_TEMP_OUT_H, temp, 2) == -1) return -1;
    return mpu9250_temp_degC(mpu9250, (uint16_t)temp[0]<<8|(uint16_t)temp[1]);
}

/******************************************************************************/
/**
* Read the raw data of the temperature of the MPU9250
*
* @param    ak8963 is a pointer to the ak8963_t instance
*
* @return   -1 if an error occurred or if data where not ready or an
*           overflow occurred else 0 if data are available.
*
* @note     The data is automatically update in the mpu9250_t instance.
*
*******************************************************************************/
int ak8963_read_mag(ak8963_t * ak8963)
{
    /* Local declaration */
    uint8_t mag[8];
    int16_t x, y, z;
    /* Program statement */
    if(ak8963_read_register(ak8963, AK8963_ST1, mag, 8) == -1) return -1;
    if(((mag[0]&(AK8963_MAG_DRDY|AK8963_MAG_DOR)) != AK8963_MAG_DRDY) || mag[7]&AK8963_MAG_HOFL) return -1;
    x = ((int16_t)mag[2]<<8)|mag[1];
    y = ((int16_t)mag[4]<<8)|mag[3];
    z = ((int16_t)mag[6]<<8)|mag[5];
    ak8963->mag_full_scale = (mag[7]&AK8963_MAG_BITM)>>4;
    if(ak8963_mag_compass(ak8963, x, y, z) == -1) return -1;
    return 0;
}

/******************************************************************************/
/**
* Read the all raw data of all the sensor of the MPU9250
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
*
* @return   -1 if an error occurred else 0
*
* @note     The data is automatically update in the mpu9250_t instance.
*
*******************************************************************************/
int mpu9250_read_all(mpu9250_t * mpu9250)
{
    /* Local declaration */
    uint8_t data[14];
    uint16_t acc_x, acc_y, acc_z;
    uint16_t gy_x, gy_y, gy_z;
    uint16_t temp;
    /* Program statement */
    if(mpu9250_read_register(mpu9250, MPU9250_ACCEL_XOUT_H, data, 14) == -1) return -1;
    acc_x = (uint16_t)data[0]<<8|(uint16_t)data[1];
    acc_y = (uint16_t)data[2]<<8|(uint16_t)data[3];
    acc_z = (uint16_t)data[4]<<8|(uint16_t)data[5];
    temp = (uint16_t)data[6]<<8|(uint16_t)data[7];
    gy_x = (uint16_t)data[8]<<8|(uint16_t)data[9];
    gy_y = (uint16_t)data[10]<<8|(uint16_t)data[11];
    gy_z = (uint16_t)data[12]<<8|(uint16_t)data[13];
    mpu9250_acc_g(mpu9250, acc_x, acc_y, acc_z);
    mpu9250_gy_deg_per_s(mpu9250, gy_x, gy_y, gy_z);
    return mpu9250_temp_degC(mpu9250, temp);
}
