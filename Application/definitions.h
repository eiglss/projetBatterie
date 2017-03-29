#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define NB_OF_STORED_SAMPLES 2
#define NB_OF_MPU 1

#define ALPHA_PARAM 0.98

typedef struct
{
    float x;
    float y;
    float z;
} T_coord_3D;


/*
* asp : angular speed (vitesse angulaire) [�/s]
* ang : angle [�]
* spe : vitesse [m/s]
* acc : acceleration lineaire [m/s�]
* aca : acceleration angulaire [�/s�]
* mag : magnetometre [�]
*/
typedef struct
{
    T_coord_3D asp[NB_OF_STORED_SAMPLES];
    T_coord_3D ang[NB_OF_STORED_SAMPLES];
    T_coord_3D spe[NB_OF_STORED_SAMPLES];
    T_coord_3D acc[NB_OF_STORED_SAMPLES];
    T_coord_3D aca[NB_OF_STORED_SAMPLES];
    T_coord_3D mag[NB_OF_STORED_SAMPLES];
} T_mpu_infos;


typedef struct
{
    T_mpu_infos mpu[NB_OF_MPU];
} T_sensors;

#endif
