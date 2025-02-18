#include "cub.h"
#include "parsing_interns.h"

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

void	count_line(t_mm *mm, t_parsing_map *map, char *str, int fd)
{
	char	*line;
	int		i;
	int		count;

	i = get_index_before_map(mm, map, str, 0, 0);
	count = 0;
	fd = open_map(str);
	line = safe_get_next_line(mm, ZONE_1, fd);
	while (line != NULL)
	{
		safe_free(mm, ZONE_1, line);
		if (count >= i)
			map->count_line++;
		line = safe_get_next_line(mm, ZONE_1, fd);
		count++;
	}
	close_map(fd);
}

int	get_index_before_map(t_mm *mm, t_parsing_map *map, char *str, int count, int fd)
{
	char	*line;

	fd = open_map(str);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = safe_get_next_line(mm, ZONE_1, fd);
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
		safe_free(mm, ZONE_1, line);
		line = safe_get_next_line(mm, ZONE_1, fd);
	}
	close_map(fd);
	trash_gnl(str);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (count);
}
