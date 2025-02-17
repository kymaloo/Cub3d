#include "cub.h"

void	line_size(t_parsing_map *map, char *str, int fd)
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
		if (count >= i && ft_strlen_int(line) > map->line_size)
			map->line_size = ft_strlen_int(line);
		free(line);
		line = get_next_line(fd);
		count++;
	}
	free(line);
	close_map(fd);
}

int	count_line_in_file(char *str)
{
	int		fd;
	int		count;
	char	*line;

	fd = open_map(str);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	free(line);
	close_map(fd);
	return (count);
}

char	**stock_file(t_mm *mm, char *str)
{
	int		i;
	int		fd;
	int		count;
	char	**result;

	i = 0;
	fd = open_map(str);
	count = count_line_in_file(str);
	result = safe_malloc(mm, ZONE_1, sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (i < count)
	{
		result[i] = get_next_line(fd);
		i++;
	}
	result[i] = NULL;
	close_map(fd);
	return (result);
}

char	**extract_map(t_mm *mm, t_parsing_map *map, char **src, char *str)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	result = safe_malloc(mm, ZONE_1, sizeof(char *) * (map->count_line + 1));
	if (!result)
		return (NULL);
	while (i < get_index_before_map(map, str, 0, 0))
		i++;
	while (src[i])
	{
		result[j] = ft_strdup(src[i]);
		i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

void	copy_map(t_mm *mm, t_parsing_map *map)
{
	int	i;

	i = 0;
	map->grid_copy = safe_malloc(mm, ZONE_PARSING_TMP, sizeof(char *) * (map->count_line + 1));
	if (!map->grid_copy)
		return ;
	while (map->grid[i])
	{
		map->grid_copy[i] = ft_strdup(map->grid[i]);
		i++;
	}
	map->grid_copy[i] = NULL;
}
