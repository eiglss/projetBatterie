#include <stdio.h>
#include "communication.h"

void traiter_message(T_sensors *p_sensors)
{

}

void envoyer_message(T_sensors *p_sensors)
{
	int i;
    for (i=0;i<NB_OF_MPU;i++)
    {
    	// Envoi d'une trame de detection de frappe
    	if(p_sensors->mpu[i].tap.tap_detected  == 1)
    	{
    		if(p_sensors->mpu[0].tap.num_tom != -1)
    			printf("%1d %1d\n", p_sensors->mpu[0].tab_toms[p_sensors->mpu[0].tap.num_tom].num_MIDI, (int)p_sensors->mpu[i].tap.velocite);
    	}
    }
}

