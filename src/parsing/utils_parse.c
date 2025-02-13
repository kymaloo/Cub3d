#include "cub.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	is_white_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (0);
	return (1);
}

void	count_line(t_parsing_map *map, char *str, int fd)
{
	char	*line;
	int		i;
	int		count;

	i = get_index_before_map(map, str, 0, 0);
	count = 0;
	fd = open_map(str);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		if (count >= i)
			map->count_line++;
		line = get_next_line(fd);
		count++;
	}
	free(line);
	close_map(fd);
}

int	get_index_before_map(t_parsing_map *map, char *str, int count, int fd)
{
	char	*line;

	fd = open_map(str);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			count++;
		else if (strncmp_with_array(line, map->direction, 5) != -1)
			count++;
		else if (strncmp_with_array(line, map->fc, 2) != -1)
			count++;
		else
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close_map(fd);
	trash_gnl(str);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (count);
}
