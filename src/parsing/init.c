#include "cub.h"
#include "parsing_interns.h"

static int	init_direction_and_fc(t_game *game, char *str)
{
	if (init_tab_direction(game->mm, game->parse) == EXIT_FAILURE)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "Init Tab Direction Failed", EXIT_FAILURE));
	if (init_tab_fc(game->mm, game->parse) == EXIT_FAILURE)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "Init Tab Fc Failed", EXIT_FAILURE));
	if (init_direction(game, str, 0, 0) == EXIT_FAILURE)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "Init Direction Failed", EXIT_FAILURE));
	if (init_fc(game, str) == EXIT_FAILURE)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "Init Fc Failed", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	init_map(t_game *game, char *str)
{
	game->parse->grid_and_dir = stock_file(game->mm, str);
	game->parse->grid = extract_map(game, game->parse->grid_and_dir, str);
	if (check_map(game->parse->grid) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_doublon_map(game->parse->grid, "NSEW") != 1)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "ONE PLEYER PLSSSS 🤓", EXIT_FAILURE));
	copy_map(game);
	return (EXIT_SUCCESS);
}

int	init(t_game *game, char *str)
{
	if (check_map_format_cub(game, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_map_reel(game->mm, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_direction_and_fc(game, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_fc(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_format_fc(game->mm, game->parse) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (verif_colors(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	count_line(game, str, 0);
	line_size(game, str, 0);
	if (init_map(game, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_wall(game->mm, game->parse) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
