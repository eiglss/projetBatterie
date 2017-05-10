#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "Drivers/mpu9250.h"
#include "Drivers/led.h"
#include "Drivers/switch.h"
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
    init_all_mpu(&sensors);
    timer_start(TIMER_0);

    printf("MPU Connected!\n");

    /* Program statement */
    int i = 0;

    while (!0)
    {
    	read_all(&data_asp, &data_acc, &data_mag);
        compute_mpu_infos (&sensors, data_asp, data_acc, data_mag);
        //printf("ACC : %f \n", data_acc.x);
        //printf("ACA : %f \n", sensors.mpu[0].aca[0].x);

        if(test_tap)
        	i = 1000000;
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
