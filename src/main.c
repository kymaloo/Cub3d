#include "cub.h"

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
	game->map->tile_size = 16;
	game->texture->image->minimap = mlx_new_image(game->mlx, 360, 360);
	//game->texture->image->minimap->instances[1];
	game->texture->player = mlx_load_png("images/p3_stand1.png");
	game->texture->image->player_img = mlx_texture_to_image(game->mlx, game->texture->player);
	mlx_image_to_window(game->mlx, game->texture->image->player_img, game->player->position[X] * 16, game->player->position[Y] * 16);
	stock_radian(game->player);
}

int	main(int argc, char **argv)
{
	t_infos_p *infos_p;

	infos_p = NULL;
	if (argc != 2)
		return (ft_error(WHERE, "Bad argument", EXIT_FAILURE));
	create_memory_manager(&infos_p);
	if (init(infos_p, argv[1]) != EXIT_SUCCESS)
	  	nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));
	init_mlx(infos_p->g);
	if (mlx_loop_hook(infos_p->g->mlx, &ft_hook, infos_p->g))
			mlx_loop(infos_p->g->mlx);
	mlx_terminate(infos_p->g->mlx);
	memory_manager(DESTROY, NULL, NULL);
	printf(BGREEN"\tDone !\n"RESET);
	return (EXIT_SUCCESS);
}

static void	ft_close_window(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

void	ft_hook(void *gamed)
{
	t_game	*game;

	game = gamed;
	ft_move_perso(game);
	ft_close_window(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->radian += 0.05;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->radian -= 0.05;
}

void	print_minimap(t_game *g)
{
	draw_radar(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_M))
	{
		g->texture->image->player_img->enabled = true;
		g->texture->image->img_window->enabled = true;
	}
	else if (mlx_is_key_down(g->mlx, MLX_KEY_N))
	{
		g->texture->image->player_img->enabled = false;
		g->texture->image->img_window->enabled = false;
	}
}

void	create_memory_manager(t_infos_p **infos_p)
{
	t_parsing_map 		*parse;
	t_game				*game;

	memory_manager(CREATE, NULL, NULL);
	memory_manager_area_create(ZONE_1, &free, 256);
	memory_manager_area_create(ZONE_FDS, &fd_deletion_func, 10);
	memory_manager_area_create(ZONE_MLX, &mlx_deletion_func, 1);
	*infos_p = safe_calloc(ZONE_1, 1, sizeof(t_infos_p));
	game = safe_calloc(ZONE_1, 1, sizeof(t_game));
	parse = safe_calloc(ZONE_1, 1, sizeof(t_parsing_map));
	(*infos_p)->p = parse;
	(*infos_p)->g = game;
	(*infos_p)->g->player = safe_calloc(ZONE_1, 1, sizeof(t_player));
	(*infos_p)->g->texture = safe_calloc(ZONE_1, 1, sizeof(t_texture));
	(*infos_p)->g->texture->path = safe_calloc(ZONE_1, 1, sizeof(t_path));
	(*infos_p)->g->texture->colors = safe_calloc(ZONE_1, 1, sizeof(t_colors));
	(*infos_p)->g->texture->image = safe_calloc(ZONE_1, 1, sizeof(t_image));
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
