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
	float	pos[NB_DIM];
	float	angle;

	float	wall_hit[NB_DIM];

	enum e_directions hit_dir_of_wall;
} t_ray;

void	ray_ini(float pos[], float angle, t_ray *ray)
{
	ray->angle = angle;
	ray->pos[X] = pos[X];
	ray->pos[Y] = pos[Y];

	ray->wall_hit[X] = -1;
	ray->wall_hit[Y] = -1;
	ray->hit_dir_of_wall = NONE;
}

void	ray_next(float angle_step, t_ray *ray)
{
	ray->angle = nomarlise_angle( ray->angle + angle_step);
	ray->wall_hit[X] = -1;
	ray->wall_hit[Y] = -1;
	ray->hit_dir_of_wall = NONE;
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
					* (1 - modf(ray->pos[X], truc(ray->pos[X])));
	d->first_step_y = (d->step_y) \
					* (1 - modf(ray->pos[Y], truc(ray->pos[Y])));
}

/**
 * @brief 
 * depending on collison axis : 
 * 
 * X:
 * Moving to the East, wall hit on the West side
 * Moving to the West, wall hit on the East side
 * 
 * Y:
 * Moving South, wall hit on the North side
 * Moving North, wall hit on the South side
 * 
 * @param ray 
 * @param step_x 
 * @param step_y 
 * @param collision_axis 
 * @return true 
 * @return false 
 */
bool collide(t_ray *ray, float step_x, float step_y, enum e_axis collision_axis)
{
	if (collision_axis == X)
	{
		if (step_x > 0)
       		ray->hit_dir_of_wall = EAST;  // Moving to the East, wall hit on the West side
		else if (step_x < 0)
        	ray->hit_dir_of_wall WEST;  // Moving to the West, wall hit on the East side
	}
	else if (collision_axis == Y)
	{
		if (step_y > 0)
			ray->hit_dir_of_wall SOUTH;  // Moving South, wall hit on the North side
		else if (step_y < 0)
			ray->hit_dir_of_wall NORTH;  // Moving North, wall hit on the South side
	}
    return NONE;  // Just in case something goes wrong
	return (true);
}



typedef struct s_bdda
{
	float ray_angle;
	float ray_x;
	float ray_y;
	float advanced_dist_y;
	float advanced_dist_x;
	float delta_dist_x;
	float delta_dist_y;
	int	step_x;
	int	step_y;
	int where_x;
	int where_y;
} t_bdda;

// Fonction de normalisation de l'angle entre 0 et 2PI
void normalize_angle(float *ray_angle) 
{
    while (*ray_angle < 0)
	{
        *ray_angle += 2 * M_PI;  // Ajouter 2PI tant que l'angle est négatif
    }
    while (*ray_angle >= 2 * M_PI) 
	{
        *ray_angle -= 2 * M_PI;  // Soustraire 2PI tant que l'angle est >= 2PI
    }
}

// Fonction d'init du better dda
void init_bdda(t_bdda *dda, t_ray *ray)
{
    dda->ray_angle = ray->angle;
    dda->ray_x = ray->pos[X];
    dda->ray_y = ray->pos[Y];


    // Calculate delta distances
    dda->delta_dist_x = fabs(1 / cos(ray->angle));
    dda->delta_dist_y = fabs(1 / sin(ray->angle));

    // Initialize step and initial side distance
    if (cos(ray->angle) < 0)
	{
        dda->step_x = -1;
        dda->advanced_dist_x = (ray->pos[X] - (int) ray->pos[X]) * dda->delta_dist_x;
    } else 
	{
        dda->step_x = 1;
        dda->advanced_dist_x = ((int) ray->pos[X] + 1.0 - ray->pos[X]) * dda->delta_dist_x;
    }

    if (sin(ray->angle) < 0)
	{
        dda->step_y = -1;
        dda->advanced_dist_y = (ray->pos[Y] - (int)ray->pos[Y]) * dda->delta_dist_y;
    } else
	{
        dda->step_y = 1;
        dda->advanced_dist_y = ((int) ray->pos[Y] + 1.0 - ray->pos[Y]) * dda->delta_dist_y;
    }
}
map_wall_direction_hit_check(t_bdda *dda, t_map *m, t_ray *ray, enum e_axis moving_along)
{
	dda->where_x = (int) dda->ray_x;
	dda->where_y = (int) dda->ray_y;
	if ((dda->where_x >= 0 && dda->where_x <= m->x_max) \
				&& (dda->where_y >= 0 && dda->where_y <= m->y_max) \
				&& (m->map[dda->where_y][dda->where_x] == WALL)) 
	{
		collide(ray, dda->step_x, dda->step_y, moving_along);
		return true;
	}
	return false;
}
dda_advance_along_smaller_vect(t_bdda *dda, enum e_axis *moving_along)
{
	if (dda->advanced_dist_x < dda->advanced_dist_y)
	{
		*moving_along = X;
		dda->advanced_dist_x += dda->delta_dist_x;
		dda->ray_x += dda->step_x;
	} 
	else
	{
		*moving_along = Y;
		dda->advanced_dist_y += dda->delta_dist_y;
		dda->ray_y += dda->step_y;
	}
}

// Fonction better dda
void bdda(t_bdda *dda, t_map *m, t_ray *ray)
{
	bool		collided;
	enum e_axis	moving_along;

	init_bdda(dda, ray);
	collided = false;
	while (!collided && (dda->advanced_dist_x < RENDER_DISTANCE \ 
		|| dda->advanced_dist_x < RENDER_DISTANCE))
	{
		dda_advance_along_smaller_axis_unit_vect(dda, &moving_along);
		collided = map_wall_direction_hit_check(dda, m, ray, moving_along);
	}
	if (!collided)
		collide(ray, dda->step_x, dda->step_y, NONE);
	return ;
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
