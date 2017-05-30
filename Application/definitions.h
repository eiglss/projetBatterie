#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define NB_OF_STORED_SAMPLES 3
#define NB_OF_MPU 1
#define NB_TOMS 4

#define DEBUG

#define MAIN_D 0
#define MAIN_G 1
#define PIED_D 2
#define PIED_G 3
#define MAIN (0 | 1)
#define PIED (2 | 3)

#define MIN_ACA_TAPPING_CAPTURE 70000
#define MIN_TIME_LAST_TAP 0.09 // 90ms

#define ALPHA_PARAM 0.99

//num_MIDI
#define KICK 35 //pied
#define SNARE 38 //gauche
#define HIGH_TOM 50 //millieu gauche
#define MIDDLE_TOM 43 //millieu droite
#define FLOOR_TOM 41 //droite

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
