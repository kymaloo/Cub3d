#include "cub.h"

/**
 * @brief memory manager area ZONE_1 deletion function
 * 
 * @param mlx_t_adr the adress of the mlx_t to mlx_terminate
 */
void	mlx_deletion_func (void *mlx_t_adr)
{
	mlx_terminate(mlx_t_adr);
}

/**
 * @brief memory manager area ZONE_FDs deletion function
 * 
 * @param fd_adr the fd to close
 */
void	fd_deletion_func (void *fd_adr)
{
	int	*i;

	i = fd_adr;
	close(*i);
}

// int	init_mlx_images()
// {

// }

// int	init_mlx_textures()
// {

// }

void	init_mlx(t_game *g)
{
	mlx_image_t* img;

	g->mlx_infos.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!g->mlx_infos.mlx)
		nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));
	img = mlx_new_image(g->mlx_infos.mlx, 1920, 1080);
	mlx_image_to_window(g->mlx_infos.mlx, img, 0, 0);
	g->mlx_infos.images.next_frame = img;
	g->map.tile_size = 16;
	g->mlx_infos.images.minimap = mlx_new_image(g->mlx_infos.mlx, 360, 360);
	//g->texture->image->minimap->instances[1];
	g->mlx_infos.textures.minimap_player = mlx_load_png(PATH_2D_PLAYER);
	g->mlx_infos.images.minimap_player = mlx_texture_to_image(g->mlx_infos.mlx, g->mlx_infos.textures.minimap_player);
	mlx_image_to_window(g->mlx_infos.mlx, g->mlx_infos.images.minimap_player, g->player.position[X] * 16, g->player.position[Y] * 16);
	stock_radian(&g->player);
}

void	create_memory_manager(void)
{
	memory_manager(CREATE, NULL, NULL);
	memory_manager_area_create(ZONE_1, &free, 256);
	memory_manager_area_create(ZONE_FDS, &fd_deletion_func, 10);
	memory_manager_area_create(ZONE_MLX, &mlx_deletion_func, 1);
}

void	stock_radian(t_player *player)
{
	if (player->facing == 'N')
		player->angle = (M_PI / 2);
	if (player->facing == 'S')
		player->angle = (-M_PI / 2);
	if (player->facing == 'E')
		player->angle = (2 * M_PI);
	if (player->facing == 'W')
		player->angle = (M_PI);
}
	
int	main(int argc, char **argv)
{
	t_game	game_infos;

	if (argc != 2)
	return (ft_error(WHERE, "Bad argument", EXIT_FAILURE));
	create_memory_manager();
	ft_memset(&game_infos, 0, sizeof(game_infos));
	if (parse_map_init_game_infos(&game_infos, argv[1]) != EXIT_SUCCESS)
		nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));
	init_mlx(&game_infos);
	if (mlx_loop_hook(game_infos.mlx_infos.mlx, &ft_hook, &game_infos))
		mlx_loop(game_infos.mlx_infos.mlx);
	mlx_terminate(game_infos.mlx_infos.mlx);
	memory_manager(DESTROY, NULL, NULL);
	printf(BGREEN"\tDone !\n"RESET);
	return (EXIT_SUCCESS);
}