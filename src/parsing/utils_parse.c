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

int	get_size_of_array(t_game *game, char **array)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	while (array[i])
	{
		size = ft_strlen_int(array[i]);
		if (check_white_space(array[i]) == 0)
			i++;
		else if (ft_strncmp(array[i], game->parse->path_north, size) == 0  || ft_strncmp(array[i], game->parse->path_south, size) == 0)
			i++;
		else if (ft_strncmp(array[i], game->parse->path_east, size) == 0 || ft_strncmp(array[i], game->parse->path_west, size) == 0)
			i++;
		else if (ft_strncmp(array[i], game->parse->color_ceiling_cp, size) == 0 || ft_strncmp(array[i], game->parse->color_floor_cp, size) == 0)
			i++;
		else
			break ;
	}
	j = i;
	while (array[i])
		i++;
	i = i - j;
	return (i);
}

int	get_index_before_array(t_game *game, char **array)
{
	int	i;
	int	size;

	i = 0;
	while (array[i])
	{
		size = ft_strlen_int(array[i]);
		if (check_white_space(array[i]) == 0)
			i++;
		else if (ft_strncmp(array[i], game->parse->path_north, size) == 0  || ft_strncmp(array[i], game->parse->path_south, size) == 0)
			i++;
		else if (ft_strncmp(array[i], game->parse->path_east, size) == 0 || ft_strncmp(array[i], game->parse->path_west, size) == 0)
			i++;
		else if (ft_strncmp(array[i], game->parse->color_ceiling_cp, size) == 0 || ft_strncmp(array[i], game->parse->color_floor_cp, size) == 0)
			i++;
		else
			break ;
	}
	return (i);
}
