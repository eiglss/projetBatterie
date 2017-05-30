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
#include "Application/communication.h"
#include "font.h"

int main(void)
{
    /* local declaration */
	int i = 0;
	int j = 0;
	int calibration = 1;
    T_sensors sensors;
    // Test
    T_coord_3D data_asp[NB_OF_MPU];
    T_coord_3D data_acc[NB_OF_MPU];
    T_coord_3D data_mag[NB_OF_MPU];

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
    	// Lecture
    	read_all(data_acc, data_asp, data_mag);
        compute_mpu_infos (&sensors, data_asp, data_acc, data_mag, calibration);




        if(calibration == 1)
        {
        	calibration = fonction_calibration(&sensors, NB_TOMS, 0);
            if(calibration == 0)
            	fonction_calcul_MIDI(&sensors, NB_TOMS);
        }


        if(calibration == 0)
        	envoyer_message(&sensors);




        //envoyer_message(&sensors);

        //############################# TEST ##############################//

        //printf("%f \n", sensors.mpu[0].ang[0].z);
        //printf("%f\n", sensors.mpu[0].mag[0].z);
        //printf("%f, %f \n", sensors.mpu[0].mag[0].x, sensors.mpu[0].mag[0].y);
        //printf("%f, %f, %f \n", sensors.mpu[0].ang[0].x, sensors.mpu[0].ang[1].x, sensors.mpu[0].ang[2].x);

		#ifdef DEBUG
        if(sensors.mpu[0].tap.tap_detected == 1 && calibration != 1)
        {
        	j ++;
        	i = 100;
        	printf("Frappe detectee : %d\n", sensors.mpu[0].tap.num_tom);
        	printf("Velocite : %f\n", sensors.mpu[0].tap.velocite);
        	printf("\n");
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
		#endif
        //############################# FIN TEST ##############################//
    }

    cleanup_platform();
    return EXIT_SUCCESS;
}
