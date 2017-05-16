#include <stdio.h>
#include "position.h"
#include "../Drivers/mpu9250.h"

unsigned char test_tap;

static mpu9250_t mpu9250;
static ak8963_t ak8963;

void read_all(T_coord_3D *p_data_acc, T_coord_3D *p_data_asp, T_coord_3D *p_data_mag)
{
	mpu9250_read_all(&mpu9250);
	p_data_acc->x = mpu9250.acc.x;
	p_data_acc->y = mpu9250.acc.y;
	p_data_acc->z = mpu9250.acc.z;
	p_data_asp->x = mpu9250.gy.x;
	p_data_asp->y = mpu9250.gy.y;
	p_data_asp->z = mpu9250.gy.z;
	ak8963_read_mag(&ak8963);
	p_data_mag->x = ak8963.mag.x;
	p_data_mag->y = ak8963.mag.y;
	p_data_mag->z = ak8963.mag.z;
}

void init_all_mpu (T_sensors *p_sensors)
{
    // Init des MPU
	mpu9250_initialization(&mpu9250, IIC_0, MPU9250_IIC);
	ak8963_initialization(&ak8963, IIC_0, AK8963_ADDR);

    uint8_t data;
    mpu9250_read_register(&mpu9250, MPU9250_GYRO_CONFIG, &data, 1);
    printf("%X\n", data);

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
            p_sensors->mpu[i].ang[j].x = 0;
            p_sensors->mpu[i].ang[j].y = 0;
            p_sensors->mpu[i].ang[j].z = 0;
            p_sensors->mpu[i].spe[j].x = 0;
            p_sensors->mpu[i].spe[j].y = 0;
            p_sensors->mpu[i].spe[j].z = 0;
            p_sensors->mpu[i].aca[j].x = 0;
            p_sensors->mpu[i].aca[j].y = 0;
            p_sensors->mpu[i].aca[j].z = 0;
            p_sensors->mpu[i].mag[j].x = 0;
            p_sensors->mpu[i].mag[j].y = 0;
            p_sensors->mpu[i].mag[j].z = 0;
        }
    }
}

void get_mpu_asp_acc_mag (T_mpu_infos *p_mpu, T_coord_3D p_raw_asp, T_coord_3D p_raw_acc, T_coord_3D p_raw_mag)
{
    p_mpu->asp[0].x = p_raw_asp.x;
    p_mpu->asp[0].y = p_raw_asp.y;
    p_mpu->asp[0].z = p_raw_asp.z;
    p_mpu->acc[0].x = p_raw_acc.x;
    p_mpu->acc[0].y = p_raw_acc.y;
    p_mpu->acc[0].z = p_raw_acc.z;
    p_mpu->mag[0].x = p_raw_mag.x;
    p_mpu->mag[0].y = p_raw_mag.y;
    p_mpu->mag[0].z = p_raw_mag.z;
}

void update_next_sample (T_mpu_infos *p_mpu)
{
    int i;
    for (i=1;i<NB_OF_STORED_SAMPLES;i++)
    {
        p_mpu->acc[i] = p_mpu->acc[i-1];
        p_mpu->asp[i] = p_mpu->asp[i-1];
        p_mpu->ang[i] = p_mpu->ang[i-1];
        p_mpu->spe[i] = p_mpu->spe[i-1];
        p_mpu->aca[i] = p_mpu->aca[i-1];
        p_mpu->mag[i] = p_mpu->mag[i-1];
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
    // Calcul de l'angle
    T_coord_3D gyr_angle, acc_angle;

    //acc_angle.x = atan(-p_mpu->acc[0].x/sqrt(pow(p_mpu->acc[0].y, 2) + pow(p_mpu->acc[0].z, 2))) * 180./M_PI;
    //acc_angle.y = atan2(p_mpu->acc[0].x , p_mpu->acc[0].z) * 180./M_PI;

    //acc_angle.x = atan2(p_mpu->acc[0].y , p_mpu->acc[0].z) * 180./M_PI;
    //acc_angle.y = atan2(p_mpu->acc[0].x , p_mpu->acc[0].z) * 180./M_PI;

    acc_angle.y = atan(-p_mpu->acc[0].x/sqrt(pow(p_mpu->acc[0].y, 2) + pow(p_mpu->acc[0].z, 2))) * 180./M_PI;
    acc_angle.x = atan(-p_mpu->acc[0].y/sqrt(pow(p_mpu->acc[0].x, 2) + pow(p_mpu->acc[0].z, 2))) * 180./M_PI;

    gyr_angle = add_coord_3D(scalar_time_coord_3D(p_mpu->asp[0], p_sample_time_s), p_mpu->ang[1]);

    p_mpu->ang[0] = add_coord_3D(scalar_time_coord_3D(gyr_angle, ALPHA_PARAM), scalar_time_coord_3D(acc_angle, 1 - ALPHA_PARAM));
    p_mpu->ang[0].z = p_mpu->mag[0].y;


    // Calcul de l'acceleration angulaire (derivee de la vitesse angulaire)
    // Operation : accel_angulaire = (vitesse_angulaire - vitesse_angulaire_prec) / T_echantillonage
    p_mpu->aca[0] = scalar_time_coord_3D(add_coord_3D(scalar_time_coord_3D(p_mpu->asp[1], -1) , p_mpu->asp[0]) , 1./p_sample_time_s);
}

// Retourne 1 si une frappe est detectee, 0 sinon
unsigned char tapping_capture (T_mpu_infos *p_mpu, float p_sample_time_s)
{
    static float time_ms_last_tap = 0;
    unsigned char result = 0;

    time_ms_last_tap += p_sample_time_s;
    if (p_mpu->aca[0].x > MIN_ACA_TAPPING_CAPTURE && time_ms_last_tap > MIN_TIME_LAST_TAP)
    {
        result = 1;
        time_ms_last_tap = 0;
    }
    return result;
}

void compute_mpu_infos (T_sensors *p_sensors, T_coord_3D data_asp, T_coord_3D data_acc, T_coord_3D data_mag)
{
	float sample_time_s = timer_restart(TIMER_0);
    int i = 0;
    for (i=0;i<NB_OF_MPU;i++)
    {
        update_next_sample (&p_sensors->mpu[i]);

        get_mpu_asp_acc_mag (&p_sensors->mpu[i], data_asp, data_acc, data_mag);

        compute_angle(&p_sensors->mpu[i], sample_time_s);

        test_tap = tapping_capture (&p_sensors->mpu[i], sample_time_s);
    }
}

