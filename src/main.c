#include "../include/cub.h"

// void	mlx_deletion_func (void *mlx_t_adr)
// {
// 	mlx_terminate(mlx_t_adr);
// }

void	fd_deletion_func (void *fd_adr)
{
	int	*i;

	i = fd_adr;
	close(*i);
}

int	main(int argc, char **argv)
{
	t_data *data;

	data = NULL;
	(void)argv;
	if (argc != 2)
		return (ft_error(WHERE, "Bad argument", EXIT_FAILURE));
	create_memory_manager(&data);
	if (init(data, argv[1]) != EXIT_SUCCESS)
	  	nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));
	// init_mlx(data->g);
	// if (mlx_loop_hook(data->g->mlx, &ft_hook, data->g))
	// 		mlx_loop(data->g->mlx);
	// mlx_terminate(data->g->mlx);
	memory_manager(DESTROY, NULL, NULL);
	printf(BGREEN"\tDone !\n"RESET);
	return (EXIT_SUCCESS);
}

// static void	ft_close_window(t_game *game)
// {
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(game->mlx);
// }

// void	ft_hook(void *gamed)
// {
// 	t_game	*game;

// 	game = gamed;
// 	ft_move_perso(game);
// 	ft_close_window(game);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
// 		game->player->radian += 0.05;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
// 		game->player->radian -= 0.05;
// }

// void	print_minimap(t_game *g)
// {
// 	draw_map(g);
// 	if (mlx_is_key_down(g->mlx, MLX_KEY_M))
// 	{
// 		g->texture->image->player_img->enabled = true;
// 		g->texture->image->img_window->enabled = true;
// 	}
// 	else if (mlx_is_key_down(g->mlx, MLX_KEY_N))
// 	{
// 		g->texture->image->player_img->enabled = false;
// 		g->texture->image->img_window->enabled = false;
// 	}
// }

void	create_memory_manager(t_data **data)
{
	memory_manager(CREATE, NULL, NULL);
	memory_manager_area_create(ZONE_PARSE, &free, 256);
	memory_manager_area_create(ZONE_FDS, &fd_deletion_func, 10);
	//memory_manager_area_create(ZONE_MLX, &mlx_deletion_func, 1);
	*data = safe_calloc(ZONE_PARSE, 1, sizeof(t_data));
	(*data)->parse = safe_calloc(ZONE_PARSE, 1, sizeof(t_parsing_map));
	(*data)->game = safe_calloc(ZONE_PARSE, 1, sizeof(t_game));
	(*data)->game->player = safe_calloc(ZONE_PARSE, 1, sizeof(t_player));
	(*data)->path = safe_calloc(ZONE_PARSE, 1, sizeof(t_path));
	(*data)->colors = safe_calloc(ZONE_PARSE, 1, sizeof(t_colors));
}

void	stock_radian(t_player *player)
{
	if (player->facing == 'N')
		player->radian = (M_PI / 2);
	if (player->facing == 'S')
		player->radian = (-M_PI / 2);
	if (player->facing == 'E')
		player->radian = (2 * M_PI);
	if (player->facing == 'W')
		player->radian = (M_PI);
}
