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
    	//if(p_sensors->mpu[i].tap.tap_detected)

    }
}
