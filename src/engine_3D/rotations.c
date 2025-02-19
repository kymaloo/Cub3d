

#include "engine_3d.h"


/**
 * @brief mutiplies vect the the rotation matrix R : 
 * 
 * R = 
 * 
 * [cos(a), -sin(a)]
 * 
 * [sin(a),  cos(a)]
 * 
 * 
 * @param vect 		2D vector
 * @param angle_rad angle in radians
 */
rotate_vector(t_vect2D *vect, double angle_rad)
{
	double *v;

	v = vect->coords;
	v[X] = v[X] * cos(angle_rad) - v[Y] * sin(angle_rad);
	v[Y] = v[X] * sin(angle_rad) - v[Y] * cos(angle_rad);
}

