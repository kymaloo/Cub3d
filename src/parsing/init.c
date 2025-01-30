#include "cub.h"

int	init_tab_direction(t_parsing_map *map)
{
	int	i;

	i = 0;
	map->direction = malloc(sizeof(char *) * 6);
	if (!map->direction)
	{
		printf(MALLOC_FAILED);
		return (MALLOC_ERROR);
	}
	map->direction[i] = ft_strdup("NO ./");
	i++;
	map->direction[i] = ft_strdup("SO ./");
	i++;
	map->direction[i] = ft_strdup("WE ./");
	i++;
	map->direction[i] = ft_strdup("EA ./");
	i++;
	map->direction[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_tab_fc(t_parsing_map *map)
{
	int	i;

	i = 0;
	map->fc = malloc(sizeof(char *) * 3);
	if (!map->fc)
	{
		printf(MALLOC_FAILED);
		return (MALLOC_ERROR);
	}
	map->fc[i] = ft_strdup("F ");
	i++;
	map->fc[i] = ft_strdup("C ");
	i++;
	map->fc[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_fc(t_parsing_map *map, char *str)
{
	char	*line;
	int		fc;
	int		fd;

	fc = count_fc(map, str, 0, 0);
	if (fc != 2)
		return (EXIT_FAILURE);
	fd = open_map(str);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			free(line);
		else if (ft_strncmp(line, map->fc[0], 2) == 0)
			process_direction(map, line, 4, fd);
		else if (ft_strncmp(line, map->fc[1], 2) == 0)
			process_direction(map, line, 5, fd);
		else
			free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (close_map(fd));
}

int	init_direction(t_parsing_map *map, char *str, int dir, int fd)
{
	char	*line;

	dir = count_dir(map, str, 0, 0);
	if (dir != 4)
		return (EXIT_FAILURE);
	fd = open_map(str);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			free(line);
		else if (ft_strncmp(line, map->direction[0], 5) == 0)
			process_direction(map, line, 0, fd);
		else if (ft_strncmp(line, map->direction[1], 5) == 0)
			process_direction(map, line, 1, fd);
		else if (ft_strncmp(line, map->direction[2], 5) == 0)
			process_direction(map, line, 2, fd);
		else if (ft_strncmp(line, map->direction[3], 5) == 0)
			process_direction(map, line, 3, fd);
		else
			free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (close_map(fd));
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

void save_path(t_parsing_map *map, char *line, int dir_index)
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
	printf("%s\n", line);
}

