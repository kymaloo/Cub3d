#include "cub.h"

static int	init_direction_and_fc(t_parsing_map *map, char *str)
{
	if (init_tab_direction(map) == EXIT_FAILURE)
		return (printf("Error: Init Tab Direction Failed"), EXIT_FAILURE);
	if (init_tab_fc(map) == EXIT_FAILURE)
		return (printf("Error: Init Tab Fc Failed"), EXIT_FAILURE);
	if (init_direction(map, str, 0, 0) == EXIT_FAILURE)
		return (printf("Error: Init Direction Failed"), EXIT_FAILURE);
	if (init_fc(map, str) == EXIT_FAILURE)
		return (printf("Error: Init Fc Failed"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	init_map(t_parsing_map *map, char *str)
{
	map->grid_and_dir = stock_file(str);
	map->grid = extract_map(map, map->grid_and_dir, str);
	if (check_map(map->grid) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_doublon_map(map->grid, "NSEW") != 1)
		return (EXIT_FAILURE);
	copy_map(map);
	return (EXIT_SUCCESS);
}

int	init(t_parsing_map *map, char *str)
{
	if (check_map_format_cub(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_direction_and_fc(map, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	count_line(map, str, 0);
	line_size(map, str, 0);
	if (init_map(map, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_wall(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
