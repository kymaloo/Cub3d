#include "cub.h"

void digital_differential_analyser_ini(t_dda *d, double point[], double angle)
{
	d->cos_a = cos(angle);
	d->sin_a = sin(angle);
	d->recipCos_a = 1 / d->cos_a;
	d->recipCos_a = 1 / d->sin_a;
	d->step_x = MAP_SQUARE_SIDE_X * d->recipCos_a;
	d->step_y =	MAP_SQUARE_SIDE_Y * d->recipSin_a;
	d->dist_walked_x = 0;
	d->dist_walked_y = 0;
}



/**
 * @brief returns the int indicating if collided on X, Y walk or if stopped because render distance exceeded.
 * 
 * @param d 
 * @param point 
 * @param angle 
 * @return int 
 */
int digital_differential_analyser_steps(t_dda *d, double point[], double angle, t_ray *r)
{
	double	walked_x;
	double	walked_y;

	while(true)
	{
		if (walked_x < walked_y)
		{
			if (ray_collision(walked_x))
				return (r->dist = walked_x, r->collision_type = X);
			walked_x += d->step_x;
			if (walked_x > RENDER_DISTANCE)
				return (r->dist = RENDER_DISTANCE, r->collision_type = RENDER_DISTANCE);
		}
		else
		{
			if (ray_collision(walked_y))
				return (r->dist = walked_y, r->collision_type = Y);
			walked_y += d->step_y;
			if (walked_x > RENDER_DISTANCE)
				return (r->dist = RENDER_DISTANCE, r->collision_type = RENDER_DISTANCE);
		}
	}
}

void	ray_ini(double point[], double angle, t_ray *r)
{
	r->angle = angle;
	init_coords(r->point, point[X], point[Y]);
}

void	raycast(double point[], double angle, t_ray *r)
{
	t_dda	d;

	ray_ini(point, angle, r);
	digital_differential_analyser_ini(&d, point, angle);
	digital_differential_analyser_steps(&d, point, angle, r);
}

void	rotate_camera(t_camera *c, double angle)
{
	rotate_vector(c->start, angle);
	rotate_vector(c->camera_step, angle);
}




