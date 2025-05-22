#include "../include/cub.h"

void	mlx_deletion_func (void *mlx_t_adr)
{
	mlx_terminate(mlx_t_adr);
}

void	fd_deletion_func (void *fd_adr)
{
	int	*i;

	i = fd_adr;
	close(*i);
}

void	init_mlx(t_game *game)

{
	mlx_image_t* img;

	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!game->mlx)
		nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));
	img = mlx_new_image(game->mlx, 1920, 1080);
	mlx_image_to_window(game->mlx, img, 0, 0);
	game->texture->image->img_window = img;
	game->texture->player = mlx_load_png("images/p3_stand1.png");
	game->texture->image->player_img = mlx_texture_to_image(game->mlx, game->texture->player);
	mlx_image_to_window(game->mlx, game->texture->image->player_img, game->player->position[X] * (TILE_SIZE_MINIMAP), game->player->position[Y] * (TILE_SIZE_MINIMAP));

}

int	main(int argc, char **argv)
{
	t_data *data;

	data = NULL;
	if (DEBUG)
	{
		printf(BBLUE"\n%s:"BBLUE" executing program:"BYELLOW" mode: Debug"RESET"\n\n\n", argv[0]);
		printf(BWHITE"parsing debug infos:"RESET"\n");
	}
	if (argc != 2)
		return (ft_error(WHERE, "Bad argument", EXIT_FAILURE));
	create_memory_manager(&data);
	if (init(data, argv[1]) != EXIT_SUCCESS)
	  	nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));
	stock_radian(data->game->player);
	if (DEBUG)
	{
		printf(BLUE"%35s"YELLOW"%-3d:    "RESET, WHERE);
		printf("player infos:\t"RED" x: %-4.0f"GREEN" y: %-4.0f"MAGENTA" a: %.2f"RESET"\n",
			data->game->player->position[X], data->game->player->position[Y], data->game->player->radian);
		printf(BWHITE"game hooks debug infos:"RESET"\n");
	}
	init_mlx(data->game);
	
	if (mlx_loop_hook(data->game->mlx, &ft_hook, data->game))
			mlx_loop(data->game->mlx);
	mlx_terminate(data->game->mlx);
	memory_manager(DESTROY, NULL, NULL);
	if (DEBUG)
		printf(BBLUE"\n\n%s:"BBLUE" executing program:"BGREEN" Done !\n"RESET, argv[0]);
	return (EXIT_SUCCESS);
}


/* MOUVEMENT HOOKS : TRANSLATION FUNCTIONS : */

#define MOVE_SPEED 3
#define PLAYER_WIDTH 0.05

void	move_translate_forward(t_game *game)
{
	t_player *p = game->player;
	double new_x = p->position[X] + p->direction[X] * MOVE_SPEED;
	double new_y = p->position[Y] + p->direction[Y] * MOVE_SPEED;

	if (DEBUG)
	{
		printf(BLUE"%15s:"YELLOW"%-3d:"RESET"%-15s:    "BBLUE"\t%4s\t"RESET, __FILE__, __LINE__, __FUNCTION__, "UP");
		printf("\n\ttrying to move to:\t("RED"%.0f"RESET", "GREEN"%.0f"RESET")\n", new_x, new_y);
	}
	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
		!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[0] = new_x;
		p->position[1] = new_y;
	}
	else if (DEBUG)
		printf(BRED"\t\t\t\t(NO)"RESET);
	if (DEBUG)
	{
		printf("\n\tplayer infos after:\t"RED" x: %-4.0f"GREEN" y: %-4.0f"MAGENTA" a: %.2f"RESET"\n",
			game->player->position[X], game->player->position[Y], game->player->radian);
		printf("\tplayer direction:\t("RED"%.0f"RESET","GREEN" %.0f"RESET")\n", game->player->direction[Y], game->player->direction[Y]);
	}
}

void	move_translate_backward(t_game *game)
{
	t_player *p = game->player;
	double new_x = p->position[0] - p->direction[0] * MOVE_SPEED;
	double new_y = p->position[1] - p->direction[1] * MOVE_SPEED;

	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
		!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[0] = new_x;
		p->position[1] = new_y;
	}
}

void	move_translate_left(t_game *game)
{
	t_player *p = game->player;
	double perp_x = -p->direction[1]; // perpendicular vector
	double perp_y = p->direction[0];

	double new_x = p->position[0] + perp_x * MOVE_SPEED;
	double new_y = p->position[1] + perp_y * MOVE_SPEED;

	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
		!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[0] = new_x;
		p->position[1] = new_y;
	}
}

void	move_translate_right(t_game *game)
{
	t_player *p = game->player;
	double perp_x = p->direction[1];
	double perp_y = -p->direction[0];

	double new_x = p->position[0] + perp_x * MOVE_SPEED;
	double new_y = p->position[1] + perp_y * MOVE_SPEED;

	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
		!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[0] = new_x;
		p->position[1] = new_y;
	}
}

/* MLX MOVEMENT HOOKS */



void	ft_keys_player_movements(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		move_translate_forward(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		move_translate_backward(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_translate_left(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_translate_right(game);
	}
}

void	update_player_direction(t_player *player)
{
	player->direction[0] = cos(player->radian); // X component
	player->direction[1] = sin(player->radian); // Y component
}

void	ft_keys_mouse_player_rotations(t_game *game, int32_t old_mouse_x, int32_t old_mouse_y)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->radian += 0.05;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->radian -= 0.05;

	int32_t new_mouse_x;
	int32_t new_mouse_y;

	mlx_get_mouse_pos(game->mlx, &new_mouse_x, &new_mouse_y);
	update_player_direction(game->player);
}

void	ft_keys_other_actions(t_game *game)
{
	if ((mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) \
	|| (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL) && mlx_is_key_down(game->mlx, MLX_KEY_D)))
		mlx_close_window(game->mlx);
}

/* HOOKS */

#include <unistd.h>     // for usleep()
#include <sys/time.h>   // for gettimeofday()

#define TARGET_FPS 60
#define FRAME_DURATION_US (1000000 / TARGET_FPS) // 16,666 microseconds

long long	get_time_us(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000000LL + tv.tv_usec);
}

void	precise_sleep(long long target_us)
{
	long long start = get_time_us();
	long long now = get_time_us();

	// Sleep most of the time, then busy-wait for the final part
	if (target_us > 2000) // Skip usleep if total delay is very small
		usleep(target_us - 1000); // sleep all but last ~1ms

	now = get_time_us();
	while ((now - start) < target_us)
	{
		now = get_time_us();
	}
}

void	ft_hook(void *game_ptr)
{
	t_game	*game;
	static int32_t	old_mouse_x;
	static int32_t	old_mouse_y;

	game = game_ptr;
	long long start = get_time_us();

	ft_keys_player_movements(game);
	ft_keys_mouse_player_rotations(game);
	ft_keys_other_actions(game);


	//ft_move_perso(game);
	//print_minimap(game);
	raycast(game);

	long long end = get_time_us();
	long long elapsed = end - start;

	if (elapsed < FRAME_DURATION_US)
		precise_sleep(FRAME_DURATION_US - elapsed);
	mlx_get_mouse_pos(game->mlx, &old_mouse_x, &old_mouse_y);
}

void	print_minimap(t_game *g)
{
	
	if (mlx_is_key_down(g->mlx, MLX_KEY_M))
	{
		draw_map(g);
		g->texture->image->player_img->enabled = true;
		g->texture->image->img_window->enabled = true;
	}
	else if (mlx_is_key_down(g->mlx, MLX_KEY_N))
	{
		g->texture->image->player_img->enabled = false;
		g->texture->image->img_window->enabled = false;
	}
}

void	create_memory_manager(t_data **data)
{
	memory_manager(CREATE, NULL, NULL);
	memory_manager_area_create(ZONE_PARSE, &free, 256);
	memory_manager_area_create(ZONE_FDS, &fd_deletion_func, 10);
	memory_manager_area_create(ZONE_MLX, &mlx_deletion_func, 1);
	*data = safe_calloc(ZONE_PARSE, 1, sizeof(t_data));
	(*data)->parse = safe_calloc(ZONE_PARSE, 1, sizeof(t_parsing_map));
	(*data)->game = safe_calloc(ZONE_PARSE, 1, sizeof(t_game));
	(*data)->game->texture = safe_calloc(ZONE_PARSE, 1, sizeof(t_texture));
	(*data)->game->texture->image = safe_calloc(ZONE_PARSE, 1, sizeof(t_image));
	(*data)->game->player = safe_calloc(ZONE_PARSE, 1, sizeof(t_player));
	(*data)->path = safe_calloc(ZONE_PARSE, 1, sizeof(t_path));
	(*data)->colors = safe_calloc(ZONE_PARSE, 1, sizeof(t_colors));
	(*data)->game->ray = safe_calloc(ZONE_PARSE, 1, sizeof(t_ray));
}

void	stock_radian(t_player *player)
{
	if (player->facing == 'N')
		player->radian = (M_PI / 2);
	else if (player->facing == 'S')
		player->radian = (-M_PI / 2);
	else if (player->facing == 'E')
		player->radian = (2 * M_PI);
	else if (player->facing == 'W')
		player->radian = (M_PI);
	else
		return (ft_error(WHERE, "Bad player direction", EXIT_FAILURE));
}
