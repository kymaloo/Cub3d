#include "../include/cub.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	t_mm	*mm;

	if (argc != 2)
		return (ft_error(WHERE, "Bad argument", EXIT_FAILURE));
	mm = mm_create();
	mm_area_create(mm, ZONE_1);
	game = safe_calloc(mm, ZONE_1, 1, sizeof(t_game));
	game->mm = mm;
	mm_area_create(game->mm, ZONE_PARSING_TMP);
	game->parse = safe_calloc(game->mm, ZONE_PARSING_TMP, 1, sizeof(t_parsing_map));
	if (init(game, argv[1]) != EXIT_SUCCESS)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "init() failure", EXIT_FAILURE));
	mm_destroy(game->mm);
	printf(BGREEN"\tDone !\n"RESET);
	return (EXIT_SUCCESS);
}
