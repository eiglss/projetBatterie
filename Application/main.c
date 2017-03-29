#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"
#include "position.h"
#include "vector_tools.h"

int main()
{
    T_sensors sensors;
    init_all_mpu(&sensors);

    // Test
    T_coord_3D data_asp = {0,0,0};
    T_coord_3D data_acc = {0,0,1};
    T_coord_3D data_mag = {0,0,0};
    T_coord_3D angCor;

    int i = 0;

    while (i++ < 1000)
    {
        compute_mpu_infos (&sensors, data_asp, data_acc, data_mag, 1);

        angCor = saturator_angle(sensors.mpu[0].ang[0]);
        printf("%3.1f ; %3.1f ; %3.1f ; %u\n", angCor.x, angCor.y, angCor.z, i);
        //printf("%3.1f %3.1f %3.1f\n\n", sensors.mpu[0].pos[0].x, sensors.mpu[0].pos[0].y, sensors.mpu[0].pos[0].z);
    }

    return 1;
}
