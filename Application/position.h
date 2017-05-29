#ifndef POSITION_H
#define POSITION_H

#include "definitions.h"
#include "vector_tools.h"
#include "../Drivers/timer.h"
#include "math.h"

extern unsigned char test_tap;

T_coord_3D integrate (T_coord_3D p_prev_coord, T_coord_3D p_curr_coord, float sample_time_s);
void compute_angle (T_mpu_infos *p_mpu, float sample_time_s);
int init_all_mpu (T_sensors *p_sensors);
void update_next_sample (T_mpu_infos *p_mpu);
T_coord_3D saturator_angle (T_coord_3D p_angle);
void get_mpu_asp_acc_mag (T_mpu_infos *p_mpu, T_coord_3D p_raw_asp, T_coord_3D p_raw_acc, T_coord_3D p_raw_mag);
void compute_mpu_infos (T_sensors *p_sensors, T_coord_3D* data_asp, T_coord_3D* data_acc, T_coord_3D* data_mag, int calibration);
void tapping_capture (T_mpu_infos *p_mpu, float p_sample_time_s);
void read_all(T_coord_3D* p_data_acc, T_coord_3D* p_data_asp, T_coord_3D* p_data_mag);
int fonction_calibration(T_sensors *p_sensors, int p_nb_toms, int init);
void get_tom_tapped(T_mpu_infos *p_mpu, float p_sample_time_s);
float abs_angle_diff(float ang1, float ang2);
void fonction_calcul_MIDI(T_sensors *p_sensors, int p_nb_toms);

#endif
