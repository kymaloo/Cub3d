#include "../include/cub.h"

bool	is_within_map_boundaries(t_map *map, int x, int y)
{
	if (DEBUG)
	{
		if(x >= map->x_max)
			printf(BRED"\tx:%d >= %d "RESET, x, map->x_max);
		if(x < 0)
			printf(BRED"\tx:%d < 0 "RESET, x);
		if(y >= map->y_max )
			printf(BRED"\ty:%d >= %d "RESET, y, map->y_max);
		if(y < 0 )
			printf(BRED"\ty:%d < 0 "RESET, y);
	}
	if (y >= map->y_max || y < 0 || x >= map->x_max || x < 0)
		return (false);
	return 	(true);
}

void	perform_dda(t_ray *ray, t_map *map)
{
	int tmp = 0;
	
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	//	printf("%d ----------- %d\n", ray->map_x, ray->map_y);
		# define DEBUG_DDA false
		if (DEBUG_DDA)
		{
			printf("\nmap max:\t("RED"%3d"RESET","GREEN" %3d"RESET")\n", map->x_max -1, map->y_max - 1);
			printf("n*%d:\t", tmp);
			printf("%15s", "within?:  ");
			is_within_map_boundaries(map, ray->map_x, ray->map_y)? printf(GREEN" Y "RESET): printf(RED" N "RESET);
			printf("("RED"%3d"RESET","GREEN"%3d"RESET")\n", ray->map_x, ray->map_y);

			printf("n*%d:\t", tmp);
			printf("%15s", "wall?:  ");
			(map->grid[ray->map_y][ray->map_x] == '1')? printf(GREEN" Y "RESET): printf(RED" N "RESET);
			printf("("RED"%3d"RESET","GREEN"%3d"RESET")\n", ray->map_x, ray->map_y);

			printf("\n");
			tmp++;
			if (tmp > 100)
				nuclear_exit(EXIT_FAILURE);
		}

		//TODO si SEGV hors de la grille : forcer position X Y a l'extremum grille au max
		// if(ray->map_x >= map->x_max)
		// {
		// 	ray->map_x = map->x_max - 1;
		// 	ray->hit = 1;
		// }
		// else if(ray->map_x < 0)
		// {
		// 	ray->map_x = 0;
		// 	ray->hit = 1;
		// }
		// if(ray->map_y >= map->y_max )
		// {
		// 	ray->map_y = map->y_max - 1;
		// 	ray->hit = 1;
		// }
		// else if(ray->map_y < 0 )
		// {
		// 	ray->map_y = 0;
		// 	ray->hit = 1;
		// }
			


		if (map->grid[ray->map_y][ray->map_x] == '1') // plus haut si SEGV
			ray->hit = 1;
	}
}

static void ceilling(t_game *game, int x)
{
	int	y;
	int color_floor;

	y = 0;
	color_floor = C_FLOOR_BROWN;
	while (y < game->ray->draw_start - 2) //FIXME the -2 was necessary, as game->ray->draw_start was set to 1082
	{
		mlx_put_pixel(game->texture->image->img_window, x, y, color_floor);
		y++;
	}
}

void init_textures(t_game *game)
{
   //printf("%s\n", &game->path->north[3]);
    game->texture->north = mlx_load_png(&game->path->north[3]);
    if (!game->texture->north)
        nuclear_exit(ft_error(WHERE, "Texture loading failed", EXIT_FAILURE));
    game->texture->south = mlx_load_png(&game->path->south[3]);
    if (!game->texture->south)
        nuclear_exit(ft_error(WHERE, "Texture loading failed", EXIT_FAILURE));
    game->texture->east = mlx_load_png(&game->path->east[3]);
    if (!game->texture->east)
        nuclear_exit(ft_error(WHERE, "Texture loading failed", EXIT_FAILURE));
    game->texture->west = mlx_load_png(&game->path->west[3]);
    if (!game->texture->west)
        nuclear_exit(ft_error(WHERE, "Texture loading failed", EXIT_FAILURE));
    if (!game->texture->north || !game->texture->south || 
        !game->texture->east || !game->texture->west)
    {
       nuclear_exit(ft_error(WHERE, "Texture loading failed", EXIT_FAILURE));
    }
    if (game->texture->north->width != 512 || game->texture->north->height != 512 ||
        game->texture->south->width != 512 || game->texture->south->height != 512 ||
        game->texture->east->width != 512 || game->texture->east->height != 512 ||
        game->texture->west->width != 512 || game->texture->west->height != 512)
    {
        nuclear_exit(ft_error(WHERE, "Texture dimensions must be 512x512", EXIT_FAILURE));
    }
}

static void setup_texture(t_game *game)
{
    if (game->ray->side == 0)
    {
        if (game->ray->dir_x < 0)
            game->ray->current_texture = game->texture->west;
        else
            game->ray->current_texture = game->texture->east;
    }
    else
    {
        if (game->ray->dir_y < 0)
            game->ray->current_texture = game->texture->south;
        else
            game->ray->current_texture = game->texture->north;
    }
}

static void draw_column(t_game *game, double wall_x, int x)
{
    int tex_x;
    int tex_y;
    int y;
    double step;
    double tex_pos;

    tex_x = (int)(wall_x * game->ray->current_texture->width);

    if (game->ray->side == 0 && game->ray->dir_x < 0)
        tex_x = game->ray->current_texture->width - tex_x - 1;
    if (game->ray->side == 1 && game->ray->dir_y < 0)
        tex_x = game->ray->current_texture->width - tex_x - 1;

    step = 1.0 * game->ray->current_texture->height / game->ray->line_height;
    tex_pos = (game->ray->draw_start - HEIGHT / 2 + game->ray->line_height / 2) * step;
    y = game->ray->draw_start;
    
    while (y <= game->ray->draw_end)
    {
        tex_y = (int)tex_pos & (int)(game->ray->current_texture->height - 1);
        tex_pos += step;
        game->ray->pixel = &game->ray->current_texture->pixels[(tex_x + tex_y * game->ray->current_texture->width) * 4];
        game->ray->color = (game->ray->pixel[0] << 24) | (game->ray->pixel[1] << 16) | (game->ray->pixel[2] << 8) | game->ray->pixel[3];
        mlx_put_pixel(game->texture->image->img_window, x, y, game->ray->color);
        y++;
    }
}

static void wall(t_game *game, int x)
{
    double wall_x;
    
    if (game->ray->side == 0)
        wall_x = game->player->position[1] + game->ray->perp_wall_dist * game->ray->dir_y;
    else
        wall_x = game->player->position[0] + game->ray->perp_wall_dist * game->ray->dir_x;
    wall_x -= floor(wall_x);
    setup_texture(game);
    draw_column(game, wall_x, x);
}

static void floors(t_game *game, int x)
{
	int	y;
	int color_floor;

	y = game->ray->draw_end + 1;
	color_floor = C_GREY_INVALID;
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->texture->image->img_window, x, y, color_floor);
		y++;
	}
}

static	void	setup_colors(t_game *game, int x)
{
	ceilling(game, x);
	wall(game, x);
	floors(game, x);
}

static void onscreen_line(t_ray *ray, int line_height)
{
    if (line_height > HEIGHT * 10)
        line_height = HEIGHT * 10;

    ray->draw_start = -line_height / 2 + HEIGHT / 2;
    ray->draw_end = line_height / 2 + HEIGHT / 2;

    if (ray->draw_start < 0)
        ray->draw_start = 0;
    if (ray->draw_end >= HEIGHT)
        ray->draw_end = HEIGHT - 1;
}

static void init_ray_dir_x_y(t_ray *ray, t_player *player)
{
   if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->position[0] - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - player->position[0]) * ray->delta_dist_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->position[1] - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->position[1]) * ray->delta_dist_y;
    }
}

static void init_var_ray(t_ray *ray, t_player *player, double ray_angle)
{
    ray->dir_x = cos(ray_angle);
    ray->dir_y = sin(ray_angle);
    ray->map_x = (int)player->position[0];
    ray->map_y = (int)player->position[1];
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);
    ray->hit = 0;
    init_ray_dir_x_y(ray, player);
}

static void calculate_perp_wall_dist(t_game *game, double ray_angle)
{
    double angle_diff;

    if (game->ray->side == 0)
        game->ray->perp_wall_dist = fabs((game->ray->map_x - game->player->position[0] + 
            (1 - game->ray->step_x) / 2) / game->ray->dir_x);
    else
        game->ray->perp_wall_dist = fabs((game->ray->map_y - game->player->position[1] + 
            (1 - game->ray->step_y) / 2) / game->ray->dir_y);
    angle_diff = game->player->radian - ray_angle;
    while (angle_diff > M_PI)
        angle_diff -= 2 * M_PI;
    while (angle_diff < -M_PI)
        angle_diff += 2 * M_PI;
    game->ray->perp_wall_dist *= cos(angle_diff);
    if (game->ray->perp_wall_dist < 0.05)
        game->ray->perp_wall_dist = 0.05;
}

void raycast(t_game *game)
{
    int x;
    double camera_x;
    double ray_angle;
    
    x = 0;
    while (x < WIDTH)
    {
        camera_x = 2 * x / (double)WIDTH - 1;
        ray_angle = game->player->radian + atan(camera_x * tan(FOV * M_PI / 360.0));
        init_var_ray(game->ray, game->player, ray_angle);
        perform_dda(game->ray, game->map);
        calculate_perp_wall_dist(game, ray_angle);
        
        if (game->ray->perp_wall_dist < 0.1)
            game->ray->perp_wall_dist = 0.1;
            
        game->ray->line_height = (int)(HEIGHT / game->ray->perp_wall_dist);
        onscreen_line(game->ray, game->ray->line_height);
        setup_colors(game, x);
        x++;
    }
}
