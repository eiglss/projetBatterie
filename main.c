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

    /* initialization */
    init_platform();
    init_all_mpu(&sensors);
    printf("Hello world!\n");

    /* Program statement */
    int i = 1000;

    while (!0)
    {
    	read_all(&data_asp, &data_acc, &data_mag);
        compute_mpu_infos (&sensors, data_asp, data_acc, data_mag, 0.0005);
        //printf("ACC : %f \n", data_acc.x);
        if(test_tap)
        {
        	i --;
        	led_write(LED1);
        }
        else
        {
        	i = 1000;
        	led_write(0);
        }
    }

    cleanup_platform();
    return EXIT_SUCCESS;
}
