#include "cub.h"
#include "parsing_interns.h"

static int	init_direction_and_fc(t_mm *mm, t_parsing_map *map, char *str)
{
	if (init_tab_direction(mm, map) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "Init Tab Direction Failed", EXIT_FAILURE));
	if (init_tab_fc(mm, map) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "Init Tab Fc Failed", EXIT_FAILURE));
	if (init_direction(mm, map, str, 0, 0) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "Init Direction Failed", EXIT_FAILURE));
	if (init_fc(mm, map, str) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "Init Fc Failed", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static int	init_map(t_mm *mm, t_parsing_map *map, char *str)
{
	map->grid_and_dir = stock_file(mm, str);
	map->grid = extract_map(mm, map, map->grid_and_dir, str);
	if (check_map(map->grid) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_doublon_map(map->grid, "NSEW") != 1)
		mm_nuclear_exit(mm, ft_error(WHERE, "ONE PLEYER PLSSSS 🤓", EXIT_FAILURE));
	copy_map(mm, map);
	return (EXIT_SUCCESS);
}

int	init(t_mm *mm, t_parsing_map *map, char *str)
{
	if (check_map_format_cub(mm, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_map_reel(mm, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_direction_and_fc(mm, map, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_fc(mm, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_format_fc(mm, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (verif_colors(mm, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	count_line(mm, map, str, 0);
	line_size(mm, map, str, 0);
	if (init_map(mm, map, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_wall(mm, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
