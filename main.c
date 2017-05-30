#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "Drivers/mpu9250.h"
#include "Drivers/led.h"
#include "Drivers/switch.h"
#include "Drivers/timer.h"
#include "Drivers/button.h"
#include "Application/definitions.h"
#include "Application/position.h"
#include "Application/vector_tools.h"
#include "Application/communication.h"
#include "font.h"

int main(void)
{
    /* local declaration */
	int calibration;

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
    calibration = fonction_calibration(&sensors, NB_TOMS, 1);
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
            {
              Calcul_rayon_tamb(&sensors);
              fonction_calcul_MIDI(&sensors, NB_TOMS);

            }
        }

        //if(calibration == 0)
        //	envoyer_message(&sensors);

		if(btn_is_on(BTN3))
			calibration = fonction_calibration(&sensors, NB_TOMS, 1);

        //############################# TEST ##############################//

		#ifdef DEBUG
        if(sensors.mpu[0].tap.tap_detected == 1 && calibration != 1)
        {
        	printf("Frappe detectee : %d\n", sensors.mpu[0].tap.num_tom);
        	printf("Velocite : %.1f\n", sensors.mpu[0].tap.velocite);
        	printf("Angle : %.1f \n", sensors.mpu[0].ang[0].z);
        	printf("\n");
        }


		#endif
        //############################# FIN TEST ##############################//
    }

    cleanup_platform();
    return EXIT_SUCCESS;
}
