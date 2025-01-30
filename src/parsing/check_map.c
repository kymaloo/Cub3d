#include "cub.h"

int	ft_check_map_format_cub(char *str)
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

int	count_dir(t_parsing_map *map, char *str, int count, int fd)
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
		else if (strncmp_with_array(line, map->direction, 5) != -1)
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

int	count_fc(t_parsing_map *map, char *str, int count, int fd)
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
		else if (strncmp_with_array(line, map->fc, 2) != -1)
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

int	ft_check_map(t_parsing_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] != '1' && map->grid[i][j] != '0' &&
			map->grid[i][j] != 'N' && map->grid[i][j] != 'S' &&
			map->grid[i][j] != 'E' && map->grid[i][j] != 'W')
				return (printf("Error: The map is not ready!\n"), -1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_count_line(t_parsing_map *map, char *str, int fd)
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
	printf("%d\n", map->count_line);
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

void	extract_map(t_parsing_map *map, char *str)
{
	int	status;
	int	i;

	status = EXIT_FAILURE;
	i = 0;
	map->grid = malloc(sizeof(char *) * (map->count_line + 1));
	if (map->grid)
	{
		while (i < map->count_line)
		{
			map->grid[i] = get_next_line(fd);
			if (map->grid[i])
				status = EXIT_SUCCESS;
			else
			{
				ft_printf("Error: The copy failed\n");
				ft_free_all(map->grid, i);
			}
			i++;
		}
		map->grid[i] = NULL;
	}
	else
		ft_printf("Error: The malloc failed\n");
	return (status);
}
