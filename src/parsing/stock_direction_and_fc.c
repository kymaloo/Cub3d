#include "cub.h"
#include "parsing_interns.h"

static void	save_path(t_mm *mm, t_parsing_map *map, char *line, int dir_index)
{
	if (dir_index == 0)
		map->path_north = safe_strdup(mm, ZONE_1, line);
	else if (dir_index == 1)
		map->path_south = safe_strdup(mm, ZONE_1, line);
	else if (dir_index == 2)
		map->path_west = safe_strdup(mm, ZONE_1, line);
	else if (dir_index == 3)
		map->path_east = safe_strdup(mm, ZONE_1, line);
	else if (dir_index == 4)
		map->color_floor = safe_strdup(mm, ZONE_1, line);
	else if (dir_index == 5)
		map->color_ceiling = safe_strdup(mm, ZONE_1, line);
}

int	process_direction(t_mm *mm, t_parsing_map *map, char *line, int dir_i, int fd)
{
	if (dir_i == 0 && map->path_north != NULL)
		return (check_doublon(mm, "north", line, fd));
	if (dir_i == 1 && map->path_south != NULL)
		return (check_doublon(mm, "south", line, fd));
	if (dir_i == 2 && map->path_west != NULL)
		return (check_doublon(mm, "west", line, fd));
	if (dir_i == 3 && map->path_east != NULL)
		return (check_doublon(mm, "east", line, fd));
	if (dir_i == 4 && map->color_floor != NULL)
		return (check_doublon(mm, "floor", line, fd));
	if (dir_i == 5 && map->color_ceiling != NULL)
		return (check_doublon(mm, "ceiling", line, fd));
	save_path(mm, map, line, dir_i);
	safe_free(mm, ZONE_1, line);
	return (EXIT_SUCCESS);
}

int	check_doublon(t_mm *mm, char *direction, char *line, int fd)
{
	printf("Error: Find duplicate for %s\n", direction);
	safe_free(mm, ZONE_1, line);
	close_map(fd);
	return (EXIT_FAILURE);
}

int	count_dir(t_mm *mm, char **dir, char *str, int count, int fd)
{
	char	*line;

	fd = open_map(str);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = safe_get_next_line(mm, ZONE_1, fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			safe_free(mm, ZONE_1, line);
		else if (strncmp_with_array(line, dir, 5) != -1)
		{
			count++;
			safe_free(mm, ZONE_1, line);
		}
		else
			safe_free(mm, ZONE_1, line);
		line = safe_get_next_line(mm, ZONE_1, fd);
	}
	close_map(fd);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (count);
}

int	count_fc(t_mm *mm, char **fc, char *str, int count, int fd)
{
	char	*line;

	fd = open_map(str);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = safe_get_next_line(mm, ZONE_1, fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			safe_free(mm, ZONE_1, line);
		else if (strncmp_with_array(line, fc, 2) != -1)
		{
			count++;
			safe_free(mm, ZONE_1, line);
		}
		else
			safe_free(mm, ZONE_1, line);
		line = safe_get_next_line(mm, ZONE_1, fd);
	}
	close_map(fd);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (count);
}
