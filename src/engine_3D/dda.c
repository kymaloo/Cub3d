#include "cub.h"

// Fonction de normalisation de l'angle entre 0 et 2PI
float	normalize_angle(float ray_angle) 
{
	while (ray_angle < 0)
	{
        ray_angle += 2 * M_PI;  // Ajouter 2PI tant que l'angle est négatif
    }
    while (ray_angle >= 2 * M_PI) 
	{
		ray_angle -= 2 * M_PI;  // Soustraire 2PI tant que l'angle est >= 2PI
    }
	return (ray_angle);
}

//TODO Fix camera INI 
void	camera_ini(t_player *player, t_camera *c)
{
	c->camera_distance_forward = ((SCREEN_WIDTH * 0.5) / tanf(FOV * 0.5)) / MAP_SQUARE_SIDE_Y;
	
	c->camera_leftmost_point[X] = (player->position[X] - SCREEN_WIDTH / 2) / MAP_SQUARE_SIDE_X;
	c->camera_leftmost_point[Y] = (player->position[Y] + c->camera_distance_forward) / MAP_SQUARE_SIDE_Y;

	c->camera_vect[X] = SCREEN_WIDTH / MAP_SQUARE_SIDE_X;
	c->camera_vect[Y] = 0;

	c->camera_step_vect[X] = (c->camera_vect[X] / SCREEN_WIDTH) / MAP_SQUARE_SIDE_X;
	c->camera_step_vect[Y] = (c->camera_vect[Y] / SCREEN_WIDTH) / MAP_SQUARE_SIDE_Y;

	c->camera_step_angle = FOV / (SCREEN_WIDTH);
}

void	ray_ini(float pos[], float angle, t_ray *ray)
{
	ray->angle = angle;
	ray->pos[X] = pos[X];
	ray->pos[Y] = pos[Y];

	ray->coord_wall_hit[X] = -1;
	ray->coord_wall_hit[Y] = -1;
	ray->hit_dir_of_wall = NONE;
}

void	ray_next(t_ray *ray, t_camera *camera)
{
	ray->pos[X] += camera->camera_step_vect[X];
	ray->pos[Y] += camera->camera_step_vect[Y];
	ray->angle = normalize_angle(atan2f(ray->pos[Y], ray->pos[X]));
	ray->coord_wall_hit[X] = -1;
	ray->coord_wall_hit[Y] = -1;
	ray->hit_dir_of_wall = NONE;
}

enum e_directions angle_goes(float angle, t_axis axis)
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


typedef struct s_bdda
{
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	advanced_dist_y;
	float	advanced_dist_x;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		where_tile_x;
	int		where_tile_y;
} t_bdda;



// Fonction d'init du better dda
void	init_bdda(t_bdda *dda, t_ray *ray)
{
	dda->ray_angle = ray->angle;
    dda->ray_x = ray->pos[X];
    dda->ray_y = ray->pos[Y];
	
	
    // Calculate delta distances
    dda->delta_dist_x = fabs(1 / cos(ray->angle));
    dda->delta_dist_y = fabs(1 / sin(ray->angle));
	
    // Initialize step and initial side distance
    if (cosf(ray->angle) < 0)
	{
		dda->step_x = -1;
        dda->advanced_dist_x = (ray->pos[X] - (int) ray->pos[X]) * dda->delta_dist_x;
    } else 
	{
		dda->step_x = 1;
        dda->advanced_dist_x = ((int) ray->pos[X] + 1.0 - ray->pos[X]) * dda->delta_dist_x;
    }
    if (sinf(ray->angle) < 0)
	{
		dda->step_y = -1;
        dda->advanced_dist_y = (ray->pos[Y] - (int)ray->pos[Y]) * dda->delta_dist_y;
    } else
	{
		dda->step_y = 1;
        dda->advanced_dist_y = ((int) ray->pos[Y] + 1.0 - ray->pos[Y]) * dda->delta_dist_y;
    }
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
bool	collide(t_ray *ray, float step_x, float step_y, t_axis collision_axis)
{
	if (collision_axis == X)
	{
		if (step_x > 0)
			   ray->hit_dir_of_wall = EAST;  // Moving to the East, wall hit on the West side
		else if (step_x < 0)
			ray->hit_dir_of_wall = WEST;  // Moving to the West, wall hit on the East side
		ray->percent_tile_texture_hit = ray->coord_wall_hit[X] / GRID_SIZE_X;
	}
	else if (collision_axis == Y)
	{
		if (step_y > 0)
			ray->hit_dir_of_wall = SOUTH;  // Moving South, wall hit on the North side
		else if (step_y < 0)
			ray->hit_dir_of_wall = NORTH;  // Moving North, wall hit on the South side
		ray->percent_tile_texture_hit = ray->coord_wall_hit[Y] / GRID_SIZE_Y;
	}
	else
		return NONE;  // Just in case something goes wrong
	return (true);
}

int	map_wall_direction_hit_check(t_bdda *dda, t_map *m, t_ray *ray, t_axis moving_along)
{
	dda->where_tile_x = (int) dda->ray_x;
	dda->where_tile_y = (int) dda->ray_y;
	if ((dda->where_tile_x >= 0 && dda->where_tile_x <= m->x_max) \
		&& (dda->where_tile_y >= 0 && dda->where_tile_y <= m->y_max) \
		&& (m->map[dda->where_tile_y][dda->where_tile_x] == CHAR_WALL)) 
	{
		ray->coord_wall_hit[X] = dda->ray_x;
		ray->coord_wall_hit[Y] = dda->ray_y;
		if (moving_along == X)
			ray->distance_to_hit = dda->advanced_dist_x;
		else if (moving_along == Y)
			ray->distance_to_hit = dda->advanced_dist_y;
		else
			nuclear_exit(ft_error(WHERE, \
				"map_wall_direction_hit_check failure: bad axis", EXIT_FAILURE));
		collide(ray, dda->step_x, dda->step_y, moving_along);
		return true;
	}
	ray->coord_wall_hit[X] = -1;
	ray->coord_wall_hit[Y] = -1;
	return false;
}
t_axis	dda_advance_along_smaller_axis_unit_vect(t_bdda *dda)
{
	if (dda->advanced_dist_x < dda->advanced_dist_y)
	{
		dda->advanced_dist_x += dda->delta_dist_x;
		dda->ray_x += dda->step_x;
		return (X);
	} 
	else
	{
		dda->advanced_dist_y += dda->delta_dist_y;
		dda->ray_y += dda->step_y;
		return (Y);
	}
	nuclear_exit(ft_error(WHERE, \
		"dda_advance_along_smaller_vect failure: bad axis", EXIT_FAILURE));
}

// Fonction better dda
void	do_the_bdda(t_map *m, t_ray *ray)
{
	t_bdda		bdda;
	bool		collided;
	t_axis	along_axis;

	init_bdda(&bdda, ray);
	collided = false;
	while (!collided && (bdda.advanced_dist_x < RENDER_DISTANCE \
		|| bdda.advanced_dist_y < RENDER_DISTANCE))
	{
		along_axis = dda_advance_along_smaller_axis_unit_vect(&bdda);
		collided = map_wall_direction_hit_check(&bdda, m, ray, along_axis);
	}
	if (!collided)
		nuclear_exit(ft_error(WHERE, \
			"bdda failure: didn't collide after loop end", EXIT_FAILURE));
	return ;
}

int	get_texture_pixel_color(t_game *g, t_ray *r, int current_x, int current_y, int wall_display_height)
{
	int tile_relative_x_impact;
	int tile_relative_y_impact;

	tile_relative_x_impact = current_x % MAP_SQUARE_SIDE_X;
	tile_relative_y_impact = current_y / wall_display_height;
	if (r->hit_dir_of_wall == EAST)
	{
		return (g->mlx_infos.textures.wall_east->pixels[ \
			tile_relative_y_impact * WALL_HEIGHT + tile_relative_x_impact]);
	}
	else if(r->hit_dir_of_wall == WEST)
	{
		return (g->mlx_infos.textures.wall_east->pixels[ \
			tile_relative_y_impact * WALL_HEIGHT + tile_relative_x_impact]);
	}
	else if (r->hit_dir_of_wall == NORTH)
	{
		return (g->mlx_infos.textures.wall_east->pixels[ \
			tile_relative_y_impact * WALL_HEIGHT + tile_relative_x_impact]);
	}
	else if (r->hit_dir_of_wall == SOUTH)
	{
		return (g->mlx_infos.textures.wall_east->pixels[ \
			tile_relative_y_impact * WALL_HEIGHT + tile_relative_x_impact]);
	}
	else
		nuclear_exit(ft_error(__FILE__, __LINE__, "Ray collided Unknown type", EXIT_FAILURE));
	return (0);
}


static inline float distance_size_function(float x)
{
	return (1 / x);
}

void	draw_the_pixel_column(t_game *g, t_ray *ray, unsigned int current_column_x_on_screen)
{
	//distance mur = taill colonne mur
	// % mur hit = colonne mur a dessiner
	// pour haque pixel de taille donne au mur, le %th pixel y de la texture est celuia dessiner
	//  ex : 4 pixels pour dessiner un mur, on prendra les pixels 1/4, 2/4 3/4 et 4/4 de taille y texture respectivement,

	// au dessur du mur : pixels ciel
	// en dessous : pixels sol.

	//murs : tranpasrant au dessus et en dessous, 
	//image background em layer du dessous : ciel/sol,


	unsigned int	column_height;
	//unsigned int	tile_percent; //TODO
	int				color;
	int				offset_from_ground;

	if (ray->distance_to_hit <= 0)
		column_height = SCREEN_HEIGHT;
	else
		column_height = SCREEN_HEIGHT * distance_size_function(ray->distance_to_hit); //  1/x
	offset_from_ground = (SCREEN_HEIGHT - column_height) * 0.5;

	unsigned int	current_column_y;
	current_column_y = offset_from_ground;
	while(current_column_y < column_height)
	{
		//color = get_texture_pixel_color(g, ray, current_column_x_on_screen, current_column_y, column_height);
		if (ray->hit_dir_of_wall == EAST)
		{
			color = C_WALL_EAST;
		}
		else if (ray->hit_dir_of_wall == WEST)
		{
			color = C_WALL_WEST;
		}
		else if (ray->hit_dir_of_wall == NORTH)
		{
			color = C_WALL_NORTH;
		}
		else if (ray->hit_dir_of_wall == SOUTH)
		{
			color = C_WALL_SOUTH;
		}
		mlx_put_pixel(g->mlx_infos.images.next_frame, current_column_x_on_screen, offset_from_ground + current_column_y, color);
	}
}

void	raycast_and_draw_fov_from_player(t_game *g, t_map *map, t_player *player)
{
	t_ray			ray;
	t_camera		*camera;
	float			angle_step;
	unsigned int	ray_number;


	camera = &g->player.camera;
	//angle_step = FOV / SCREEN_WIDTH;
	camera_ini(player, camera);
	ray_number = 0;
	ray_ini(camera->camera_leftmost_point, camera->camera_angle_to_leftmost_point, &ray);
	while (ray_number < SCREEN_WIDTH)
	{
		do_the_bdda(map, &ray);
		draw_the_pixel_column(g, &ray, ray_number);
		ray_number++;
		//ray_next(angle_step, &ray, camera); //FIXME
	}
}

void	draw_frame(t_game *g)
{
	t_time *t;

	t = &g->time;
	gettimeofday(&t->old, NULL);
	raycast_and_draw_fov_from_player(g, &g->map, &g->player);
	gettimeofday(&t->now, NULL);
	t->time_taken_to_draw_frame = (t->old.tv_usec - t->old.tv_usec) * 1e6;
	printf(BLUE"time taken to display buffered frame: %10ld"RESET, t->time_taken_to_draw_frame);
}

void keys_pressed(t_game *g)
{
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_ESCAPE))
	mlx_close_window(g->mlx_infos.mlx);
}


