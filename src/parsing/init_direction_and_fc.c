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

	fc = count_fc(map->fc, str, 0, 0);
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

	dir = count_dir(map->direction, str, 0, 0);
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

int	check_map_reel(char *str)
{
	int	fd;

	fd = open_map(str);
	if (fd == -1)
	{
		printf("Error: The map isn't reel\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
