#include "vector_tools.h"

T_coord_3D add_coord_3D (T_coord_3D p_op1, T_coord_3D p_op2)
{
    T_coord_3D result;
    result.x = p_op1.x + p_op2.x;
    result.y = p_op1.y + p_op2.y;
    result.z = p_op1.z + p_op2.z;
    return (result);
}

T_coord_3D mean_coord_3D (T_coord_3D p_op1, T_coord_3D p_op2)
{
    return (add_coord_3D (p_op1, p_op2));
}

T_coord_3D scalar_time_coord_3D (T_coord_3D p_op, float scalar)
{
    T_coord_3D result;
    result.x = p_op.x * scalar;
    result.y = p_op.y * scalar;
    result.z = p_op.z * scalar;
    return (result);
}

