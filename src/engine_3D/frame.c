
#include "cub.h"

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
draw_column_to_buffer(t_game *g, t_ray *r, float angle, int x_current)
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
		int color = get_vertical_xth_percent_pixel_color(r, x_current, current_wall_y);
		mlx_put_pixel(image, x_current, offset_from_ground + current_wall_y, );
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
	double		camera_current[NB_DIM];
	int			i;

	p = g->player;
	c = &p->camera;
	camera_current[X] = c->start[X];
	camera_current[Y] = c->start[Y];
	i = 0;
	while(i < SCREEN_WIDTH)
	{
		r.angle = atan2(camera_current[Y], camera_current[X]);	//whatch out we're in Y X coordinates
		raycast(g->player->position, r.angle, &r);
		draw_column_to_buffer(g, &r, i);
		camera_current[X] += c->camera_step[X];
		camera_current[Y] += c->camera_step[Y];
		i++;
	}
}

void	draw_frame(t_game *g)
{
	t_time *t;

	t = g->time;
	gettimeofday(&t->old, NULL);
	draw_screen_to_buffer(g);
	gettimeofday(&t->now, NULL);
	t->time_taken_to_draw_frame = (t->old.tv_usec - t->old.tv_usec) * 1e6;
	display_buffer(g);
	printf(BLUE"time taken to display buffered frame: %4d"RESET, t->time_taken_to_draw_frame);
}

void game_loop(t_game *g)
{
	draw_frame(g);
	try_move(g);
}
