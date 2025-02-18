#include "../include/cub.h"

int	main(int argc, char **argv)
{
	t_mm			*mm;
	t_game			*game;
	t_parsing_map	*map;

	if (argc != 2)
		return (ft_error(WHERE, "Bad argument", EXIT_FAILURE));

	mm = mm_create();
	mm_area_create(mm, ZONE_1);

	map = safe_calloc(mm, ZONE_1, 1, sizeof(t_parsing_map));
	game = safe_calloc(mm, ZONE_1, 1, sizeof(t_game));
	mm_area_create(mm, ZONE_PARSING_TMP);
	
	if (init(mm, map, argv[1]) != EXIT_SUCCESS)
		mm_nuclear_exit(mm, ft_error(WHERE, "init() failure", EXIT_FAILURE));
	init_mlx(game);
	//mlx_set_setting(MLX_MAXIMIZED, true);
	//game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	mm_area_create(mm, ZONE_MLX);
	mm_area_delete(mm, ZONE_PARSING_TMP);
	mm_area_delete(mm, ZONE_MLX);
	mm_destroy(mm);
	printf(BGREEN"\tDone !\n"RESET);
	return (EXIT_SUCCESS);
}
void	init_mlx(t_game *game)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	game->mlx = safe_mlx_init(game->mm, ZONE_MLX);
	if (!game->mlx)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "init() failure", EXIT_FAILURE));
}
