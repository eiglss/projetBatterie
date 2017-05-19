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
#include "font.h"

int main(void)
{
    /* local declaration */
	int i = 0;
	int j = 0;
	int calibration = 1;
    T_sensors sensors;
    // Test
    T_coord_3D data_asp;
    T_coord_3D data_acc;
    T_coord_3D data_mag;

    /* initialization */
    printf(DEFAULTCOLOR CURSORHOME CLEARSCREEN); /* Cleans the terminal */
    printf("Initializing platform...\t");
    init_platform();
    printf("[ "F_LIGHTGREEN"OK"DEFAULTCOLOR" ]\n");
    printf("Starting timer...\t\t");
    timer_start(TIMER_0);
    printf("[ "F_LIGHTGREEN"OK"DEFAULTCOLOR" ]\n");
    printf("Initializing IMU...\t\t");
    if(init_all_mpu(&sensors) == -1)
    {
    	printf("["F_LIGHTRED"FAIL"DEFAULTCOLOR"]\n");
    	return EXIT_FAILURE;
    }
    else
    {
    	printf("[ "F_LIGHTGREEN"OK"DEFAULTCOLOR" ]\n");
    }
    printf("Calibration...\t\t\t");
    fonction_calibration(&sensors, NB_TOMS, 1);
    printf("[ "F_LIGHTGREEN"OK"DEFAULTCOLOR" ]\n");
    /* Program statement */
    while (!0)
    {
    	read_all(&data_acc, &data_asp, &data_mag);
        compute_mpu_infos (&sensors, data_asp, data_acc, data_mag, calibration);

        if(calibration == 1)
        	calibration = fonction_calibration(&sensors, NB_TOMS, 0);

        printf("%f \n", sensors.mpu[0].ang[0].z);
        //printf("%f\n", sensors.mpu[0].mag[0].z);
        //printf("%f, %f \n", sensors.mpu[0].mag[0].x, sensors.mpu[0].mag[0].y);
        //printf("%f, %f, %f \n", sensors.mpu[0].ang[0].x, sensors.mpu[0].ang[1].x, sensors.mpu[0].ang[2].x);

        if(sensors.mpu[0].tap >= 0 && calibration != 1)
        {
        	j ++;
        	i = 100;
        	printf("Frappe detectee : %d\n", sensors.mpu[0].tap);
        	printf("Angle : %f \n", sensors.mpu[0].ang[0].z);
        	//printf("%d\n", j);
        	/*if(sensors.mpu[0].ang[0].z < sensors.mpu[0].tab_toms[0].x + 5000 && sensors.mpu[0].ang[0].z > sensors.mpu[0].tab_toms[0].x - 5000)
        	{
        		printf("1\n");
        	}
        	else if(sensors.mpu[0].ang[0].z < sensors.mpu[0].tab_toms[1].x + 5000 && sensors.mpu[0].ang[0].z > sensors.mpu[0].tab_toms[1].x - 5000)
        	{
        		printf("2\n");
        	}
        	else if(sensors.mpu[0].ang[0].z < sensors.mpu[0].tab_toms[2].x + 5000 && sensors.mpu[0].ang[0].z > sensors.mpu[0].tab_toms[2].x - 5000)
        	{
        		printf("3\n");
        	}
        	else
        	{
        		printf("aucun\n");
        	}*/
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
