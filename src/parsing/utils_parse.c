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

void	count_line(t_game *game, char *str, int fd)
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
		safe_free(game->mm, ZONE_1, line);
		if (count >= i)
		game->parse->count_line++;
		line = safe_get_next_line(game->mm, ZONE_1, fd);
		count++;
	}
	close_map(fd);
}

int	get_index_before_map(t_game *game, char *str, int count, int fd)
{
	char	*line;

	fd = open_map(str);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = safe_get_next_line(game->mm, ZONE_1, fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			count++;
		else if (strncmp_with_array(line, game->parse->direction, 5) != -1)
			count++;
		else if (strncmp_with_array(line, game->parse->fc, 2) != -1)
			count++;
		else
			break ;
		safe_free(game->mm, ZONE_1, line);
		line = safe_get_next_line(game->mm, ZONE_1, fd);
	}
	close_map(fd);
	trash_gnl(str);
	if (fd == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (count);
}
