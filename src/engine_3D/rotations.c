#include "cub.h"

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
void	rotate_vector(double *v, double angle_rad)
{
	v[X] = v[X] * cos(angle_rad) - v[Y] * sin(angle_rad);
	v[Y] = v[X] * sin(angle_rad) + v[Y] * cos(angle_rad);
}
