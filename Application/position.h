#ifndef POSITION_H
#define POSITION_H

#include "definitions.h"
#include "vector_tools.h"
#include "math.h"

T_coord_3D integrate (T_coord_3D p_prev_coord, T_coord_3D p_curr_coord, float sample_time_s);
void compute_angle (T_mpu_infos *p_mpu, float sample_time_s);
void init_all_mpu (T_sensors *p_sensors);
void update_next_sample (T_mpu_infos *p_mpu);
T_coord_3D saturator_angle (T_coord_3D p_angle);
void get_mpu_asp_acc (T_mpu_infos *p_mpu, T_coord_3D p_raw_asp, T_coord_3D p_raw_acc);
void compute_position (T_mpu_infos *p_mpu);
void compute_mpu_infos (T_sensors *p_sensors, T_coord_3D data_asp, T_coord_3D data_acc, T_coord_3D data_mag, float sample_time_s);

#endif
