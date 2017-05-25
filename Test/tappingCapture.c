#include <stdio.h>
#include "definitions.h"
//////////////////////////////////////////////////////////////////////////
#define Max_acc_x=0;
#define Max_acc_y=0;
#define Max_acc_z=0;

#define Max_asp_x=0;
#define Max_asp_y=0;
#define Max_asp_z=0;

#define Max_pos_x=0;
#define Max_pos_y=0;
#define Max_pos_z=0;

#define Max_ang_x=0;
#define Max_ang_y=0;
#define Max_ang_z=0;
//////////////////////////////////////////////////////////////////////////
bool Tapping_Capture(T_sensors *p_mpu)
{
  bool bon;
  int i, j;
  for (i=0;i<NB_OF_MPU;i++)
  {
      for (j=0;j<NB_OF_STORED_SAMPLES;j++)
      {
          if(
          (p_mpu->mpu[i].acc[j].x > Max_acc_x) &&
          (p_mpu->mpu[i].acc[j].y > Max_acc_y) &&
          (p_mpu->mpu[i].acc[j].z > Max_acc_z) &&

          (p_mpu->mpu[i].asp[j].x > Max_asp_x) &&
          (p_mpu->mpu[i].asp[j].y > Max_asp_y) &&
          (p_mpu->mpu[i].asp[j].z > Max_asp_z) &&

          (p_mpu->mpu[i].pos[j].x > Max_pos_x) &&
          (p_mpu->mpu[i].pos[j].y > Max_pos_y) &&
          (p_mpu->mpu[i].pos[j].z > Max_pos_z) &&

          (p_mpu->mpu[i].ang[j].x > Max_ang_x) &&
          (p_mpu->mpu[i].ang[j].y > Max_ang_y) &&
          (p_mpu->mpu[i].ang[j].z > Max_ang_z)
          )
          bon = true;
          else
          bon = false;
      }
  }
  return(bon);
}
