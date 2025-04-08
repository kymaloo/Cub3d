#include "cub.h"

void digital_differential_analyser_ini(t_dda *d, t_map *m, t_ray *r)
{
	d->cos_a = cos(r->angle);
	d->sin_a = sin(r->angle);
	d->recipCos_a = 1 / d->cos_a;
	d->recipCos_a = 1 / d->sin_a;
	d->map = m;
	d->step_x = MAP_SQUARE_SIDE_X * d->recipCos_a;
	d->step_y =	MAP_SQUARE_SIDE_Y * d->recipSin_a;
	d->dist_walked_x = 0;
	d->dist_walked_y = 0;
}

// int	ray_collision()
// {

// }

/**
 * @brief returns the type of the tile X Y, 
 * 
 * tarsnlates the given X Y coordinates of the point into our Y X of the map,
 * then returns the map tile's type value.
 * 
 * @param map 
 * @param point in X Y coordinates
 */
int	tile_type(t_map *map, float point[])
{
	return (map->map[(int) point[Y]][(int) point[X]]);
}

/**
 * @brief returns the int indicating if collided on X, Y walk or if stopped because render distance exceeded.
 * 
 * @param d 
 * @param point 
 * @param angle 
 * @return int 
 */
int digital_differential_analyser_steps(t_dda *d, int starting_point[], t_ray *r)
{
	float	walked_x;
	float	walked_y;
	float	current_point[NB_DIM];

	walked_x = 0;
	walked_y = 0;
	init_coords_f(current_point, starting_point[X], starting_point[Y]);
	while(true)
	{
		if (walked_x < walked_y)
		{
			current_point[X] += d->recipCos_a;
			current_point[Y] += d->recipSin_a;
			if (tile_type(d->map, current_point) != FLOOR)
				return (r->dist = walked_x, r->axis_of_collision = X);
			walked_x += d->step_x; //diagonal dist walked
			if (walked_x > RENDER_DISTANCE)
				return (r->dist = RENDER_DISTANCE, r->axis_of_collision = X);
		}
		else
		{
			current_point[X] += d->recipCos_a;
			current_point[Y] += d->recipSin_a;
			if (tile_type(d->map, current_point) != FLOOR)
				return (r->dist = walked_y, r->axis_of_collision = Y);
			walked_y += d->step_y;
			if (walked_x > RENDER_DISTANCE)
				return (r->dist = RENDER_DISTANCE, r->axis_of_collision = Y);
		}
	}
}

void	ray_ini(double point[], double angle, t_ray *r)
{
	r->angle = angle;
	init_coords(r->point, point[X], point[Y]); //+ set to camera left
}

void	raycast(t_map *map, double point[], double angle, t_ray *r)
{
	t_dda	d;

	ray_ini(point, angle, r);
	digital_differential_analyser_ini(&d, map, r);
	digital_differential_analyser_steps(&d, point, r);
}

void	rotate_camera(t_camera *c, double angle)
{
	rotate_vector(c->start, angle);
	rotate_vector(c->camera_step, angle);
}




