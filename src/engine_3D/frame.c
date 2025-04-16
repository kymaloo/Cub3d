
#include "cub.h"

get_texture_pixel_color(t_game *g, t_ray *r, int current_x, int current_y, int wall_display_height)
{
	int tile_relative_x_impact;
	int tile_relative_y_impact;

	tile_relative_x_impact = current_x % MAP_SQUARE_SIDE_X;
	tile_relative_y_impact = current_y / wall_display_height;
	if (r->type_collided == RAYHIT_WALL_EAST)
	{
		return (g->mlx_infos.textures.wall_east->pixels[ \
			tile_relative_y_impact * WALL_HEIGHT + tile_relative_x_impact]);
	}
	else if(r->type_collided == RAYHIT_WALL_WEST)
	{
		return (g->mlx_infos.textures.wall_east->pixels[ \
			tile_relative_y_impact * WALL_HEIGHT + tile_relative_x_impact]);
	}
	else if (r->type_collided == RAYHIT_WALL_NORTH)
	{
		return (g->mlx_infos.textures.wall_east->pixels[ \
			tile_relative_y_impact * WALL_HEIGHT + tile_relative_x_impact]);
	}
	else if (r->type_collided == RAYHIT_WALL_SOUTH)
	{
		return (g->mlx_infos.textures.wall_east->pixels[ \
			tile_relative_y_impact * WALL_HEIGHT + tile_relative_x_impact]);
	}
	else
		nuclear_exit(ft_error(__FILE__, __LINE__, "Ray collided Unknown type", EXIT_FAILURE));
}

/**
 * @brief
 * 
 * 0) determine wall height from ground (wall_bottom[Y])
 * 
 * 1) determine the number of pixels from the sky in the screen
 * 
 * 2)
 * 
 * @param g 
 * @param r 
 * @param angle 
 * @param ith_screen_column 
 */
draw_column_to_buffer_img(t_game *g, t_ray *r, int x_current)
{
	float	recip_dist;
	int		wall_screen_height;

	recip_dist = 1 / r->dist;
	if (r->dist == 0)
		wall_screen_height = SCREEN_HEIGHT;
	else
		wall_screen_height = SCREEN_HEIGHT * recip_dist;

	int current_wall_y;
	int offset_from_ground;
	offset_from_ground = (SCREEN_HEIGHT - wall_screen_height) * 0.5;
	current_wall_y = 0;
	while(current_wall_y < wall_screen_height) //on offset from the ground, puis on dessine le wall de bas en haut
	{
		int color = get_texture_pixel_color(g, r, x_current, current_wall_y, wall_screen_height);
		mlx_put_pixel(g->mlx_infos.images.next_frame, x_current, offset_from_ground + current_wall_y, color);
	}
}

/**
 * @brief 
 * 
 * 0) for each pixel column of the current DISPLAY_WIDTH :
 * 
 * 1) raycasts to get the distance with the detected collision. 
 * 
 * 2) draws each column.
 * 
 * 
 * @param g 
 */
draw_screen(t_game *g)
{
	t_player	*p;
	t_camera	*c;
	t_ray		r;
	float		camera_current[NB_DIM];
	int			i;

	p = &g->player;
	c = &p->camera;

	
	camera_current[X] = c->camera_leftmost_point[X];
	camera_current[Y] = c->camera_leftmost_point[Y];
	i = 0;
	while(i < SCREEN_WIDTH)
	{
		r.angle = atan2(camera_current[Y], camera_current[X]);	//whatch out we're in Y X coordinates
		raycast(p->position, r.angle, &r);
		draw_column_to_buffer(g, &r, i);
		camera_current[X] += c->camera_step_vect[X];
		camera_current[Y] += c->camera_step_vect[Y];
		i++;
	}
}

void	draw_frame(t_game *g)
{
	t_time *t;

	t = &g->time;
	gettimeofday(&t->old, NULL);
	draw_screen(g);
	gettimeofday(&t->now, NULL);
	t->time_taken_to_draw_frame = (t->old.tv_usec - t->old.tv_usec) * 1e6;
	display_buffer(g);
	printf(BLUE"time taken to display buffered frame: %4d"RESET, t->time_taken_to_draw_frame);
}

void	game_loop(t_game *g)
{
	draw_frame(g);
	try_move(g);
}
