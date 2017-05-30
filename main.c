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
	int cpt_vel;

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
        	//envoyer_message(&sensors);

        // Initialisation sur appui bouton
		if(btn_is_on(BTN3))
		{
			calibration = fonction_calibration(&sensors, NB_TOMS, 1);
			while(btn_is_on(BTN3));
		}

        //############################# TEST ##############################//

		#ifdef DEBUG
        if(sensors.mpu[0].tap.tap_detected == 1 && calibration != 1)
        {
        	// Affichage TOM
        	if(sensors.mpu[0].tap.num_tom != -1)
        	{
        		switch(sensors.mpu[0].tab_toms[sensors.mpu[0].tap.num_tom].num_MIDI)
        		{
        			case SNARE :
        				printf(F_LIGHTGREEN"SNARE"DEFAULTCOLOR"\n");
        				break;
        			case HIGH_TOM :
        				printf(F_LIGHTBLUE"HIGH TOM"DEFAULTCOLOR"\n");
        				break;
        			case MIDDLE_TOM :
        				printf(F_LIGHTMAGENTA"MIDDLE TOM"DEFAULTCOLOR"\n");
        				break;
        			case FLOOR_TOM :
        				printf(F_LIGHTYELLOW"FLOOR TOM"DEFAULTCOLOR"\n");
        				break;
        			default :
        				printf(F_LIGHTRED"ERROR"DEFAULTCOLOR"\n");
        				break;
        		}
				// Affichage velocite
				printf("Velocite : ["F_LIGHTGREEN);
				for(cpt_vel = -1 ; cpt_vel < 100 ; cpt_vel += 2)
				{
					if(sensors.mpu[0].tap.velocite < cpt_vel)
						printf(F_LIGHTRED);
					printf("|");
				}
				printf(DEFAULTCOLOR"]\n");
        	}
        	else
        		printf(F_LIGHTRED"Pas de tom detecte !"DEFAULTCOLOR"\n");

        	printf("\n");
        }
		#endif
        //############################# FIN TEST ##############################//
    }

    cleanup_platform();
    return EXIT_SUCCESS;
}
