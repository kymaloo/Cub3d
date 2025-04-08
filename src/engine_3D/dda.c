#include "cub.h"

#define CAMERA_DISTANCE_FORWARD	10
#define WALL '1'

typedef struct s_camera
{
	float camera_leftmost_point[NB_DIM];
	float camera_angle_to_leftmost_point;
	float camera_vect[NB_DIM];
	float camera_step_vect[NB_DIM];
	float camera_step_angle;
} t_camera;

void	camera_ini(t_player *player, t_camera *camera, float dist_camera, float cam_len)
{	
	camera->camera_leftmost_point[X] = player->position[X] - cam_len / 2;
	camera->camera_leftmost_point[Y] = player->position[Y] + dist_camera;

	camera->camera_vect[X] = cam_len;
	camera->camera_vect[Y] = 0;

	camera->camera_step_vect[X] = camera->camera_vect[X] / SCREEN_WIDTH;
	camera->camera_step_vect[Y] = camera->camera_vect[Y] / SCREEN_WIDTH;

	camera->camera_step_angle = FOV / SCREEN_WIDTH;
}

enum e_axis
{
	NONE = -1,
	X,
	Y,
};

enum e_directions
{
	NONE = -1,
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

typedef struct s_ray
{
	float	start_pos[NB_DIM];
	float	angle;

	float	wall_hit[NB_DIM];

	enum e_directions ray_axis_hit;
	enum e_directions ray_direction_hit;
} t_ray;

void	ray_ini(float start_pos[], float angle, t_ray *ray)
{
	ray->angle = angle;
	ray->start_pos[X] = start_pos[X];
	ray->start_pos[Y] = start_pos[Y];

	ray->wall_hit[X] = -1;
	ray->wall_hit[Y] = -1;
	ray->ray_axis_hit = NONE;
	ray->ray_direction_hit = NONE;
}

void	ray_next(float angle_step, t_ray *ray)
{
	ray->angle = nomarlise_angle( ray->angle + angle_step);
	ray->wall_hit[X] = -1;
	ray->wall_hit[Y] = -1;
	ray->ray_axis_hit = NONE;
	ray->ray_direction_hit = NONE;
}

float nomarlise_angle(float angle)
{
	if (angle > 2 * PI)
		angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}
enum e_directions angle_goes(float angle, enum e_axis axis)
{
	if (axis == X)
	{
		if (angle > 0 && angle < PI)
			return (NORTH);
		else if (angle > PI && angle < 2 * PI)
			return (SOUTH);
	}
	else if (axis == Y)
	{
		if (angle > PI / 2 && angle < 3 * PI / 2)
			return (WEST);
		else if (angle > 3 * PI / 2 && angle < PI / 2)
			return (EAST);
	}
	if (axis == X)
		printf(RED"X axis:\n\t %f rad: angle dir finding failure\n", angle);
	else if (axis == Y)
		printf(RED"Y axis:\n\t %f rad: angle dir finding failure\n", angle);
	else
		printf(RED"Axis failure\n");
	nuclear_exit(ft_error(WHERE, "angle_goes() failure", EXIT_FAILURE));
	return (NONE);
}

void	dda_ini(t_dda *d, t_map *m, t_ray *ray)
{
	d->cos_a = cos(ray->angle);
	d->sin_a = sin(ray->angle);
	d->recipCos_a = 1 / d->cos_a;
	d->recipSin_a = 1 / d->sin_a;
	d->map = m;

	d->dist_step_x = sqrt(1 + );
	d->dist_step_y = sqrt(1 + );




	d->dist_walked_x = 0;
	d->dist_walked_y = 0;

	if (anlges_goes(ray->angle) == WEST)
		d->step_x *= -1;
	if (anlges_goes(ray->angle) == SOUTH)
		d->step_y *= -1;

	d->first_step_x = (d->step_x) \
					* (1 - modf(ray->start_pos[X], truc(ray->start_pos[X])));
	d->first_step_y = (d->step_y) \
					* (1 - modf(ray->start_pos[Y], truc(ray->start_pos[Y])));
}

collide(t_ray *ray, bool *collided)
{

}

do_the_dda_steps(t_dda *d, t_map *m, t_ray *ray)
{
	float	rayLength1D[NB_DIM];
	int		where2D[NB_DIM];
	float	vStep[NB_DIM];
	float	walked_dist1D[NB_DIM];

	bool collided;

	walked_dist1D[X] = 0;
	walked_dist1D[Y] = 0;
	where2D[X] = ray->start_pos[X];
	where2D[Y] = ray->start_pos[Y];

	collided = false;

	if ( !collided && walked_dist1D[X] <= RENDER_DISTANCE && walked_dist1D[Y] <= RENDER_DISTANCE)
	{
		if (walked_dist1D[X] < walked_dist1D[Y])
		{
			where2D[X] += 1;
			d->dist_walked_x += d->unit_step_size[X];
			if (m->map[where2D[X]][where2D[Y]] == WALL)
				collide(ray, &collided);
		}
		else
		{

		}
	}
	if (!collided)
}

void	do_the_dda(t_map *map, t_ray *ray)
{
	t_dda dda_infos;

	dda_ini(&dda_infos, map, ray);
	do_the_dda_steps(&dda_infos, map, ray);
}

draw_the_pixel_column()
{

}

void	raycast_fov_from_player(t_map *map, t_player *player)
{
	t_ray		ray;
	t_camera	camera;
	float		fov;
	float		angle_step;
	int			i;

	fov = 2 * arctan(SCREEN_WIDTH / 2 * CAMERA_DISTANCE_FORWARD);
	angle_step = fov / SCREEN_WIDTH;
	camera_ini(player, &camera, CAMERA_DISTANCE_FORWARD, SCREEN_WIDTH);

	i = 0;
	ray_ini(player->position, player->angle, &ray);
	while(i < SCREEN_WIDTH)
	{
		do_the_dda(map, &ray);
		draw_the_pixel_column(&ray);
		i++;
		ray_next(angle_step, &ray);
	}
}
