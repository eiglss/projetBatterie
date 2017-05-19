#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define NB_OF_STORED_SAMPLES 3
#define NB_OF_MPU 1
#define NB_TOMS 4

#define MIN_ACA_TAPPING_CAPTURE 70000
#define MIN_ACC_TAPPING_CAPTURE 1
#define MIN_TIME_LAST_TAP 0.09 // 9ms

#define ALPHA_PARAM 0.99


typedef struct
{
    float x;
    float y;
    float z;
} T_coord_3D;


typedef struct
{
	float z;
	float rayon;
	int num_MIDI;
}T_tom;


typedef struct
{
	int tap_detected;
	int num_tom;
	float velocite;
} T_tap;


/*
* asp : angular speed (vitesse angulaire) [deg/s]
* ang : angle [deg]
* spe : vitesse [m/s]
* acc : acceleration lineaire [m/s^2]
* aca : acceleration angulaire [deg/s^2]
* mag : magnetometre [deg]
*/
typedef struct
{
    T_coord_3D asp[NB_OF_STORED_SAMPLES];
    T_coord_3D ang[NB_OF_STORED_SAMPLES];
    T_coord_3D spe[NB_OF_STORED_SAMPLES];
    T_coord_3D acc[NB_OF_STORED_SAMPLES];
    T_coord_3D aca[NB_OF_STORED_SAMPLES];
    T_coord_3D mag[NB_OF_STORED_SAMPLES];
    T_tom tab_toms[NB_TOMS];
    T_tap tap;
} T_mpu_infos;


typedef struct
{
    T_mpu_infos mpu[NB_OF_MPU];
} T_sensors;

#endif
