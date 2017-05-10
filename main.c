#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "Drivers/mpu9250.h"
#include "Drivers/led.h"
#include "Drivers/switch.h"
#include "Drivers/timer.h"
#include "Application/definitions.h"
#include "Application/position.h"
#include "Application/vector_tools.h"

int main(void)
{
    /* local declaration */

    T_sensors sensors;

    // Test
    T_coord_3D data_asp;
    T_coord_3D data_acc;
    T_coord_3D data_mag;

    printf("Hello world!\n");

    /* initialization */
    init_platform();

    timer_start(TIMER_0);
    printf("Timer OK!\n");

    init_all_mpu(&sensors);
    printf("MPU Connected!\n");

    printf("Lancement!\n");

    /* Program statement */
    int i = 0;
    int j = 0;
    while (!0)
    {
    	read_all(&data_acc, &data_asp, &data_mag);
        compute_mpu_infos (&sensors, data_asp, data_acc, data_mag);
        //printf("ACC : %f \n", data_acc.x);
        //printf("%f \n", sensors.mpu[0].aca[0].x);
        printf("%f, %f, %f \n", sensors.mpu[0].ang[0].x, sensors.mpu[0].ang[0].y, sensors.mpu[0].ang[0].z);
        if(test_tap)
        {
        	i = 100;
        	//printf("%f\n", sensors.mpu[0].ang[0].x);
        	/*if(sensors.mpu[0].ang[0].z > -100 && sensors.mpu[0].ang[0].z < -25)
        	{
        		print("1\n");
        	}
        	else if(sensors.mpu[0].ang[0].z > -25 && sensors.mpu[0].ang[0].z < 50)
        	{
        		print("2\n");
        	}
        	else if(sensors.mpu[0].ang[0].z > 50 && sensors.mpu[0].ang[0].z < 125)
        	{
        		print("3\n");
        	}
        	else
        	{
        		print("aucun\n");
        	}*/

        	j++;
        }

        if(i > 0)
        {
        	led_write(1);
        	i --;
        }
        else
        {
        	led_write(0);
        }
    }

    cleanup_platform();
    return EXIT_SUCCESS;
}
