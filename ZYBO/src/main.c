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
                printf("%.2f %.2f %.2f | %.2f %.2f %.2f | %.2f %.2f %.2f\n", mpu9250.acc.x, mpu9250.acc.y, mpu9250.acc.z, mpu9250.gy.x, mpu9250.gy.y, mpu9250.gy.z, ak8963.mag.x, ak8963.mag.y, ak8963.mag.z);
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
