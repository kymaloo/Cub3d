#include "cub.h"
#include "parsing_interns.h"

void	line_size(t_game *game, char *str, int fd)
{
	char	*line;
	int		i;
	int		count;

	i = get_index_before_map(game, str, 0, 0);
	count = 0;
	fd = open_map(str);
	line = safe_get_next_line(game->mm, ZONE_1, fd);
	while (line != NULL)
	{
		if (count >= i && ft_strlen_int(line) > game->parse->line_size)
			game->parse->line_size = ft_strlen_int(line);
		safe_free(game->mm, ZONE_1, line);
		line = safe_get_next_line(game->mm, ZONE_1, fd);
		count++;
	}
	close_map(fd);
}

int	count_line_in_file(t_mm *mm, char *str)
{
	int		fd;
	int		count;
	char	*line;

	fd = open_map(str);
	count = 0;
	line = safe_get_next_line(mm, ZONE_1, fd);
	while (line != NULL)
	{
		safe_free(mm, ZONE_1, line);
		count++;
		line = safe_get_next_line(mm, ZONE_1, fd);
	}
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
	count = count_line_in_file(mm, str);
	result = safe_malloc(mm, ZONE_1, sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (i < count)
	{
		result[i] = safe_get_next_line(mm, ZONE_1, fd);
		i++;
	}
	result[i] = NULL;
	close_map(fd);
	return (result);
}

char	**extract_map(t_game *game, char **src, char *str)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	result = safe_malloc(game->mm, ZONE_1, sizeof(char *) * (game->parse->count_line + 1));
	if (!result)
		return (NULL);
	while (i < get_index_before_map(game, str, 0, 0))
		i++;
	while (src[i])
	{
		result[j] = safe_strdup(game->mm, ZONE_1, src[i]);
		i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

void	copy_map(t_game *game)
{
	int	i;

	i = 0;
	game->parse->grid_copy = safe_malloc(game->mm, ZONE_PARSING_TMP, sizeof(char *) * (game->parse->count_line + 1));
	if (!game->parse->grid_copy)
		return ;
	while (game->parse->grid[i])
	{
		game->parse->grid_copy[i] = safe_strdup(game->mm, ZONE_1, game->parse->grid[i]);
		i++;
	}
	game->parse->grid_copy[i] = NULL;
}
