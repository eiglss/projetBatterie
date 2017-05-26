#include <stdio.h>
#include "position.h"
#include "../Drivers/mpu9250.h"

static mpu9250_t mpu9250;
static ak8963_t ak8963;

void read_all(T_coord_3D* p_data_acc, T_coord_3D* p_data_asp, T_coord_3D* p_data_mag)
{
	// Capteur 1
	mpu9250_read_all(&mpu9250);
	p_data_acc[MAIN_D].x = mpu9250.acc.x;
	p_data_acc[MAIN_D].y = mpu9250.acc.y;
	p_data_acc[MAIN_D].z = mpu9250.acc.z;
	p_data_asp[MAIN_D].x = mpu9250.gy.x;
	p_data_asp[MAIN_D].y = mpu9250.gy.y;
	p_data_asp[MAIN_D].z = mpu9250.gy.z;

	ak8963_read_mag(&ak8963);
	p_data_mag[MAIN_D].x = ak8963.compass.x;
	p_data_mag[MAIN_D].y = ak8963.compass.y;
	p_data_mag[MAIN_D].z = ak8963.compass.y;

	// Capteurs autres
	// ...
}

int init_all_mpu (T_sensors *p_sensors)
{
    // Init des MPU
	if(mpu9250_initialization(&mpu9250, IIC_0, MPU9250_ADDR) == -1) return -1;
	if(ak8963_initialization(&ak8963, IIC_0, AK8963_ADDR) ==-1) return -1;

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
    return 0;
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

float abs_angle_diff(float ang1, float ang2)
{
	if(fabs(ang1 - ang2) > 180)
	{
		return 360 - fabs(ang1 - ang2);
	}
	else
	{
		return fabs(ang1 - ang2);
	}
}

void compute_angle (T_mpu_infos *p_mpu, float p_sample_time_s)
{
    // Calcul de l'angle
    T_coord_3D gyr_angle, acc_angle;

    acc_angle.y = atan(p_mpu->acc[0].x/sqrt(pow(p_mpu->acc[0].y, 2) + pow(p_mpu->acc[0].z, 2))) * 180./M_PI;
    acc_angle.x = atan(p_mpu->acc[0].y/sqrt(pow(p_mpu->acc[0].x, 2) + pow(p_mpu->acc[0].z, 2))) * 180./M_PI;

    gyr_angle = add_coord_3D(scalar_time_coord_3D(p_mpu->asp[0], p_sample_time_s), p_mpu->ang[1]);

    p_mpu->ang[0] = add_coord_3D(scalar_time_coord_3D(gyr_angle, ALPHA_PARAM), scalar_time_coord_3D(acc_angle, 1 - ALPHA_PARAM));
    //p_mpu->ang[0].z = (gyr_angle.z*ALPHA_PARAM) + (p_mpu->mag[0].y*(1-ALPHA_PARAM));
    p_mpu->ang[0].z = p_mpu->mag[0].z;

    // Calcul de l'acceleration angulaire (derivee de la vitesse angulaire)
    // Operation : accel_angulaire = (vitesse_angulaire - vitesse_angulaire_prec) / T_echantillonage
    p_mpu->aca[0] = scalar_time_coord_3D(add_coord_3D(scalar_time_coord_3D(p_mpu->asp[1], -1) , p_mpu->asp[0]) , 1./p_sample_time_s);

 }

void tapping_capture (T_mpu_infos *p_mpu, float p_sample_time_s)
{
    static float time_ms_last_tap = 0;

    time_ms_last_tap += p_sample_time_s;
    if (fabs(p_mpu->aca[0].y) > MIN_ACA_TAPPING_CAPTURE && time_ms_last_tap > MIN_TIME_LAST_TAP)
    {
        time_ms_last_tap = 0;
        p_mpu->tap.tap_detected = -1;
    }
    else
    	p_mpu->tap.tap_detected = 0;
}

int fonction_calibration(T_sensors *p_sensors, int p_nb_toms, int init)
{
	int calibration_necessaire = 0;
	int ok;
	int i, j;
	float norm_speed;
	static int nb_passages[NB_OF_MPU];
	static int left_toms[NB_OF_MPU];
	static int left_tap[NB_OF_MPU]; // Nombre de fois a taper avant calibration

	if(init)
	{
	    for (i=0;i<NB_OF_MPU;i++)
	    {
	    	nb_passages[i] = 0;
	    	left_toms[i] = p_nb_toms;
	    	left_tap[i] = 5;
	    }
	    return 1;
	}
	else
    {
		for (i=0;i<NB_OF_MPU;i++)
		{
			if(i | MAIN)
			{
				if(left_tap[i] > 0)
				{
					if(p_sensors->mpu[i].tap.tap_detected == 1)
					{
						left_tap[i]--;
						printf("Tap initiale\n");
					}
				}
				else
				{
					norm_speed = sqrt(pow(p_sensors->mpu[i].asp[0].x,2) + pow(p_sensors->mpu[i].asp[0].y,2) + pow(p_sensors->mpu[i].asp[0].z,2));
					if(norm_speed < 100)
					{
						nb_passages[i] ++;
					}
					else
					{
						nb_passages[i] = 0;
					}

					if(nb_passages[i] >= 1000 && left_toms[i] > 0)
					{
						ok = 1;
						for(j = p_nb_toms ; j > left_toms[i] ; j--)
						{
							if (abs_angle_diff(p_sensors->mpu[i].tab_toms[j-1].z, p_sensors->mpu[i].ang[0].z) < 10.)
							{
								ok = 0;
								nb_passages[i] = 0; // Trop proches (< 10 deg)
							}
						}
						if (ok)
						{
							nb_passages[i] = 0;
							left_toms[i]--;
							p_sensors->mpu[i].tab_toms[left_toms[i]].z = p_sensors->mpu[i].ang[0].z;
							p_sensors->mpu[i].tab_toms[left_toms[i]].rayon = 10;						// test : a enlever
							printf("TOM initialise %f\n", p_sensors->mpu[i].tab_toms[left_toms[i]].z);
						}
					}
				}
				if(left_toms[i]>0)
					calibration_necessaire = 1;
			}
		}
		return calibration_necessaire;
    }
}

void get_tom_tapped(T_mpu_infos *p_mpu, float p_sample_time_s)
{
	int i = 0;
	for (i=0 ; i<NB_TOMS ; i++)
	{
		if(abs_angle_diff(p_mpu->tab_toms[i].z, p_mpu->ang[0].z) < p_mpu->tab_toms[i].rayon)
		{
			p_mpu->tap.num_tom = i;
			// Velocite = vitesse angulaire au temps n-1
			p_mpu->tap.velocite = (p_mpu->ang[2].y - p_mpu->ang[1].y)/p_sample_time_s;
		}
	}
}

void compute_mpu_infos (T_sensors *p_sensors, T_coord_3D* data_asp, T_coord_3D* data_acc, T_coord_3D* data_mag, int calibration)
{
	float sample_time_s = timer_restart(TIMER_0);
    int i = 0;
    for (i=0;i<NB_OF_MPU;i++)
    {
        update_next_sample (&p_sensors->mpu[i]);

        get_mpu_asp_acc_mag (&p_sensors->mpu[i], data_asp[i], data_acc[i], data_mag[i]);

        compute_angle(&p_sensors->mpu[i], sample_time_s);

        tapping_capture (&p_sensors->mpu[i], sample_time_s);

        // Si la calibration a ete effectuee et une frappe a ete detectee
        if(calibration == 0 && p_sensors->mpu[i].tap.tap_detected == 1 && (i | MAIN))
        	get_tom_tapped(&p_sensors->mpu[i], sample_time_s);
    }
}
