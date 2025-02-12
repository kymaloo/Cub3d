#include "cub.h"

static void save_path(t_parsing_map *map, char *line, int dir_index)
{
	if (dir_index == 0)
		map->path_north = ft_strdup(line);
	else if (dir_index == 1)
		map->path_south = ft_strdup(line);
	else if (dir_index == 2)
		map->path_west = ft_strdup(line);
	else if (dir_index == 3)
		map->path_east = ft_strdup(line);
	else if (dir_index == 4)
		map->color_floor = ft_strdup(line);
	else if (dir_index == 5)
		map->color_ceiling = ft_strdup(line);
}

int process_direction(t_parsing_map *map, char *line, int dir_index, int fd)
{
	if (dir_index == 0 && map->path_north != NULL)
		return (check_doublon("north", line, fd));
	if (dir_index == 1 && map->path_south != NULL)
		return (check_doublon("south", line, fd));
	if (dir_index == 2 && map->path_west != NULL)
		return (check_doublon("west", line, fd));
	if (dir_index == 3 && map->path_east != NULL)
		return (check_doublon("east", line, fd));
	if (dir_index == 4 && map->color_floor != NULL)
		return (check_doublon("floor", line, fd));
	if (dir_index == 5 && map->color_ceiling != NULL)
		return (check_doublon("ceiling", line, fd));
	save_path(map, line, dir_index);
	free(line);
	return (EXIT_SUCCESS);
}

int check_doublon(char *direction, char *line, int fd)
{
	printf("Error: Find duplicate for %s\n", direction);
	free(line);
	close_map(fd);
	return (EXIT_FAILURE);
}


int	init_direction_and_fc(t_parsing_map *map, char *str)
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
