#include "cub.h"

int	check_map_format_cub(char *str)
{
	int	status;
	int	len_str;

	status = EXIT_FAILURE;
	len_str = ft_strlen(str);
	if (len_str > 4)
	{
		if (ft_strncmp(&str[len_str - 4], ".cub", 4) == 0)
			status = EXIT_SUCCESS;
		else
			printf("Error: The len is false!\n");
	}
	else
		printf("Error: The len of str is too small!\n");
	return (status);
}

int	check_white_space(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	is_white_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (0);
	return (1);
}
int	count_dir(char **dir, char *str, int count, int fd)
{
	char	*line;

	fd = open_map(str);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			free(line);
		else if (strncmp_with_array(line, dir, 5) != -1)
		{
			count++;
			free(line);
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	free(line);
	close_map(fd);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (count);
}

int	count_fc(char **fc, char *str, int count, int fd)
{
	char	*line;

	fd = open_map(str);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			free(line);
		else if (strncmp_with_array(line, fc, 2) != -1)
		{
			count++;
			free(line);
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	free(line);
	close_map(fd);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (count);
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
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close_map(fd);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (count);
}

int	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' &&
			map[i][j] != 'N' && map[i][j] != 'S' &&
			map[i][j] != 'E' && map[i][j] != 'W' &&
			is_white_space(map[i][j]) != 0)
				return (printf("Error: The map is not ready!\n"), -1);
			j++;
		}
		i++;
	}
	return (0);
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
	int 	fd;
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

void	print_map(char **map)
{
	int i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

char	**stock_file(char *str)
{
	int		i;
	int		fd;
	int		count;
	char	**result;

	i = 0;
	fd = open_map(str);
	count = count_line_in_file(str);
	result = malloc(sizeof(char *) * (count + 1));
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

char	**extract_map(t_parsing_map *map, char **src, char *str)
{
	int 	i;
	int		j;
	char 	**result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (map->count_line + 1));
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

void	copy_map(t_parsing_map *map)
{
	int	i;

	i = 0;
	map->grid_copy = malloc(sizeof(char *) * (map->count_line + 1));
	if (!map->grid_copy)
		return ;
	while (map->grid[i])
	{
		map->grid_copy[i] = ft_strdup(map->grid[i]);
		i++;
	}
	map->grid_copy[i] = NULL;
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

bool	isset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (true);
		i++;
	}
	return (false);
}

int	path_finding(int x, int y, char **cells)
{
	int	end;

	end = 0;
	if (isset(cells[x][y], "NSEW0") == false)
		return (end++);
	cells[x][y] = '1';
	if (isset(cells[x + 1][y], "1\0\n") == false)
		end += path_finding(x + 1, y, cells);
	if (isset(cells[x - 1][y], "1\0\n") == false)
		end += path_finding(x - 1, y, cells);
	if (isset(cells[x][y + 1], "1\0\n") == false)
		end += path_finding(x, y + 1, cells);
	if (isset(cells[x][y - 1], "1\0\n") == false)
		end += path_finding(x, y - 1, cells);
	return (end);
}

void	find_last_floor(t_parsing_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid_copy[i])
	{
		j = 0;
		while (map->grid_copy[i][j])
		{
			if (map->grid_copy[i][j] == '0')
			{
				map->x_last_0 = i;
				map->y_last_0 = j;
				printf("%d----%d\n", map->x_last_0, map->y_last_0);
				return ;
			}
			j++;
		}
		i++;
	}
}
