#include "position.h"

void init_all_mpu (T_sensors *p_sensors)
{
    int i, j;
    for (i=0;i<NB_OF_MPU;i++)
    {
        for (j=0;j<NB_OF_STORED_SAMPLES;j++)
        {
            p_sensors->mpu[i].acc[j].x = 0;
            p_sensors->mpu[i].acc[j].y = 0;
            p_sensors->mpu[i].acc[j].z = 0;
            p_sensors->mpu[i].asp[j].x = 0;
            p_sensors->mpu[i].asp[j].y = 0;
            p_sensors->mpu[i].asp[j].z = 0;
            p_sensors->mpu[i].pos[j].x = 0;
            p_sensors->mpu[i].pos[j].y = 0;
            p_sensors->mpu[i].pos[j].z = 0;
            p_sensors->mpu[i].ang[j].x = 0;
            p_sensors->mpu[i].ang[j].y = 0;
            p_sensors->mpu[i].ang[j].z = 0;
            p_sensors->mpu[i].spe[j].x = 0;
            p_sensors->mpu[i].spe[j].y = 0;
            p_sensors->mpu[i].spe[j].z = 0;
        }
    }
}

void get_mpu_asp_acc (T_mpu_infos *p_mpu, T_coord_3D p_raw_asp, T_coord_3D p_raw_acc)
{
    p_mpu->asp[0].x = p_raw_asp.x;
    p_mpu->asp[0].y = p_raw_asp.y;
    p_mpu->asp[0].z = p_raw_asp.z;
    p_mpu->acc[0].x = p_raw_acc.x;
    p_mpu->acc[0].y = p_raw_acc.y;
    p_mpu->acc[0].z = p_raw_acc.z;
}

void update_next_sample (T_mpu_infos *p_mpu)
{
    int i;
    for (i=1;i<NB_OF_STORED_SAMPLES;i++)
    {
        p_mpu->acc[i] = p_mpu->acc[i-1];
        p_mpu->asp[i] = p_mpu->asp[i-1];
        p_mpu->ang[i] = p_mpu->ang[i-1];
        p_mpu->pos[i] = p_mpu->pos[i-1];
        p_mpu->spe[i] = p_mpu->spe[i-1];
    }
}

T_coord_3D integrate (T_coord_3D p_prev_coord, T_coord_3D p_curr_coord, float p_sample_time_s)
{
    T_coord_3D result;

    result.x = ((p_curr_coord.x + p_prev_coord.x) / 2.) * p_sample_time_s;
    result.y = ((p_curr_coord.y + p_prev_coord.y) / 2.) * p_sample_time_s;
    result.z = ((p_curr_coord.z + p_prev_coord.z) / 2.) * p_sample_time_s;

    return result;
}

T_coord_3D saturator_angle (T_coord_3D p_angle)
{
    T_coord_3D ang_cor;

    if (p_angle.x > 180)
        ang_cor.x = p_angle.x - 360;
    else if(p_angle.x < -180)
        ang_cor.x = p_angle.x + 360;
    else
        ang_cor.x = p_angle.x;

    if (p_angle.y > 180)
        ang_cor.y = p_angle.y - 360;
    else if(p_angle.y < -180)
        ang_cor.y = p_angle.y + 360;
    else
        ang_cor.y = p_angle.y;

    if (p_angle.z > 180)
        ang_cor.z = p_angle.z - 360;
    else if(p_angle.z < -180)
        ang_cor.z = p_angle.z + 360;
    else
        ang_cor.z = p_angle.z;

    return ang_cor;
}

void compute_angle (T_mpu_infos *p_mpu, float p_sample_time_s)
{
    T_coord_3D gyr_angle, acc_angle;

    acc_angle.x = atan(-p_mpu->acc[0].x/sqrt(pow(p_mpu->acc[0].y, 2) + pow(p_mpu->acc[0].z, 2))) * 180./M_PI;
    acc_angle.y = atan2(p_mpu->acc[0].y , p_mpu->acc[0].z) * 180./M_PI;

    //acc_angle.x = atan(p_mpu->acc[0].x/sqrt(pow(p_mpu->acc[0].y, 2) + pow(p_mpu->acc[0].z, 2))) * 180./M_PI;
    //acc_angle.y = atan(p_mpu->acc[0].y/sqrt(pow(p_mpu->acc[0].x, 2) + pow(p_mpu->acc[0].z, 2))) * 180./M_PI;
    //acc_angle.z = atan(sqrt(pow(p_mpu->acc[0].y, 2) + pow(p_mpu->acc[0].x, 2)) / p_mpu->acc[0].z) * 180./M_PI;;

    T_coord_3D null_coord = {0,0,0};
    gyr_angle = add_coord_3D(null_coord, scalar_time_coord_3D(p_mpu->asp[0], p_sample_time_s));
    gyr_angle = add_coord_3D(gyr_angle, p_mpu->ang[1]);

    p_mpu->ang[0] = add_coord_3D(scalar_time_coord_3D(gyr_angle, ALPHA_PARAM), scalar_time_coord_3D(acc_angle, 1 - ALPHA_PARAM));
}

void compute_position (T_mpu_infos *p_mpu)
{
}

void compute_mpu_infos (T_sensors *p_sensors, T_coord_3D data_asp, T_coord_3D data_acc, T_coord_3D data_mag, float p_sample_time_s)
{
    int i = 0;
    for (i=0;i<NB_OF_MPU;i++)
    {
        update_next_sample (&p_sensors->mpu[i]);

        get_mpu_asp_acc (&p_sensors->mpu[i], data_asp, data_acc);

        compute_angle(&p_sensors->mpu[i], p_sample_time_s);

        //compute_position (&p_sensors->mpu[i]);
    }
}
