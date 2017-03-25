/*******************************************************************************/
/**
*      @file : mpu9250.c
*   @version : 0.1
*      @date : February 28, 2017
*    @author : Enzo IGLESIS, Yonggi CHOI, Vincent MAIRE, Solene DOTHEE
* @copyright : Copyright (c) 2017 E. IGLESIS, Y. CHOI, V. MAIRE, S. DOTHEE
*              MIT License (MIT)
*******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include "msp432p401r.h"
#include "mpu9250.h"

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
    mpu9250->iic.tx.data = data;
    mpu9250->iic.tx.length = length;
    while(i2c_bus_busy(&mpu9250->iic));
    return i2c_write_data(&mpu9250->iic);
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
    mpu9250->iic.rx.data = data;
    mpu9250->iic.rx.length = length;
    while(i2c_bus_busy(&mpu9250->iic));
    return i2c_read_data(&mpu9250->iic);
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
    mpu9250->iic.tx.data = tx_data;
    mpu9250->iic.tx.length = 1;
    mpu9250->iic.rx.data = data;
    mpu9250->iic.rx.length = length;
    while(i2c_bus_busy(&mpu9250->iic));
    return i2c_write_read(&mpu9250->iic);
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
    ak8963->iic.tx.data = data;
    ak8963->iic.tx.length = length;
    while(i2c_bus_busy(&ak8963->iic));
    return i2c_write_data(&ak8963->iic);
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
    ak8963->iic.rx.data = data;
    ak8963->iic.rx.length = length;
    while(i2c_bus_busy(&ak8963->iic));
    return i2c_read_data(&ak8963->iic);
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
    ak8963->iic.tx.data = tx_data;
    ak8963->iic.tx.length = 1;
    ak8963->iic.rx.data = data;
    ak8963->iic.rx.length = length;
    while(i2c_bus_busy(&ak8963->iic));
    return i2c_write_read(&ak8963->iic);
}

/******************************************************************************/
/**
* Configure the precision of the gyroscope
*
* @param    mpu9250 is a pointer to the mpu9250_t instance
* @param    scale the precision to be setting (0: +/-250°/s; 1: +/-4g; 2: +/-8g
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
    mpu9250->gy_full_scale = scale;
    return mpu9250_write_register(mpu9250, MPU9250_GYRO_CONFIG, MPU9250_GYRO_FS_SEL&(scale<<3));
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
    mpu9250->acc_full_scale = scale;
    return mpu9250_write_register(mpu9250, MPU9250_ACCEL_CONFIG, MPU9250_ACCEL_FS_SEL&(scale<<3));
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
*           function. 14 bits correspond to 0.6 µT/LSB and 16 bits to 0.15µT/LSB
*
*******************************************************************************/
int ak8963_mag_scale(ak8963_t * ak8963, uint8_t scale)
{
    ak8963->mag_full_scale = scale;
    return ak8963_write_register(ak8963, AK8963_CNTL1, AK8963_MAG_BIT&(scale<<4)|AK8963_MAG_MODE3);
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
    mpu9250->acc_low_pass_filter = filter;
    mpu9250->gy_low_pass_filter = filter;
    return mpu9250_write_register(mpu9250, MPU9250_CONFIG, MPU9250_DLPF_CFG&filter);
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
    if(mpu9250_write_register(mpu9250, MPU9250_INT_PIN_CFG, MPU9250_INT_ANYRD_2CLEAR) == -1) return -1;
    return mpu9250_write_register(mpu9250, MPU9250_INT_ENABLE, MPU9250_RAW_RDY_EN);
}

/******************************************************************************/
/**
* Check if data are ready to be read on the ak8963.
*
* @param    ak8963 is a pointer to the ak8963_t instance
*
* @return   -1 if an error occurred else 0 if data are not ready or 1 if data is
*           ready o be read
*
* @note     IIC in the mpu9250 instance must be initialize before using this
*           function.
*
*******************************************************************************/
int ak8963_data_is_rdy(ak8963_t * ak8963)
{
    /**/
    uint8_t data[1];
    /**/
    if(ak8963_read_register(ak8963, AK8963_ST1, data, 1) == -1) return -1;
    return data[0]&AK8963_MAG_DRDY;
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
int mpu9250_initialization(mpu9250_t * mpu9250, EUSCI_B_Type * eusci, uint32_t scl_Hz, uint8_t address)
{
    mpu9250->iic.address = address;
    if(i2c_initialization_master(&mpu9250->iic, eusci, scl_Hz) == -1) return -1;
    if(mpu9250_write_register(mpu9250, MPU9250_PWR_MGMT_1, 0) == -1) return -1;
    if(mpu9250_write_register(mpu9250, MPU9250_CONFIG, 0) == -1) return -1;
    if(mpu9250_gy_scale(mpu9250, 0) == -1) return -1;
    if(mpu9250_acc_scale(mpu9250, 0) == -1) return -1;
    return (mpu9250_filter(mpu9250, 0) == -1);
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
int ak8963_initialization(ak8963_t * ak8963, EUSCI_B_Type * eusci, uint32_t scl_Hz, uint8_t address)
{
    ak8963->iic.address = address;
    if(i2c_initialization_master(&ak8963->iic, eusci, scl_Hz) == -1) return -1;
    if(ak8963_write_register(ak8963, AK8963_CNTL2, AK8963_MAG_SRST)) return -1; /* Soft reset */
    return ak8963_mag_scale(ak8963, 1); /* 16 bits precision and continuous mode 2 */
}

/******************************************************************************/
/**
* Transform gyroscope sensor raw data to �/s
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
    mpu9250->gy_data.x = x/scale;
    mpu9250->gy_data.y = y/scale;
    mpu9250->gy_data.z = z/scale;
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
    mpu9250->acc_data.x = x/scale;
    mpu9250->acc_data.y = y/scale;
    mpu9250->acc_data.z = z/scale;
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
    if(in_range(temp_out, -20366, 21367)) /* -40�C <= temp_out <= 85�C ? */
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
    int16_t range = 32760>>(2*ak8963->mag_full_scale);
    float scale = range/4192.;
    /* prorgam statement */
    if(in_range((int16_t)x, -range, range) && in_range((int16_t)y, -range, range) && in_range((int16_t)z, -range, range))
    {
        ak8963->mag_data.x = x/scale;
        ak8963->mag_data.y = y/scale;
        ak8963->mag_data.z = z/scale;
        return 0;
    }
    return -1;
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
* @return   -1 if an error occurred else 0
*
* @note     The data is automatically update in the mpu9250_t instance.
*
*******************************************************************************/
int ak8963_read_mag(ak8963_t * ak8963)
{
    /* Local declaration */
    uint8_t mag[6];
    uint16_t x, y, z;
    /* Program statement */
    if(ak8963_read_register(ak8963, AK8963_HXL, mag, 6) == -1) return -1;
    x = (uint16_t)mag[1]<<8|(uint16_t)mag[0];
    y = (uint16_t)mag[3]<<8|(uint16_t)mag[2];
    z = (uint16_t)mag[5]<<8|(uint16_t)mag[4];
    return ak8963_mag_uT(ak8963, x, y, z);
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
