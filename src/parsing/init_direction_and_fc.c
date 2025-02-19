#include "cub.h"
#include "parsing_interns.h"

int	init_tab_direction(t_mm *mm, t_parsing_map *parse)
{
	int	i;

	i = 0;
	parse->direction = safe_malloc(mm, ZONE_1, sizeof(char *) * 6);
	if (!parse->direction)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	parse->direction[i] = safe_strdup(mm, ZONE_1, "NO ./");
	i++;
	parse->direction[i] = safe_strdup(mm, ZONE_1, "SO ./");
	i++;
	parse->direction[i] = safe_strdup(mm, ZONE_1, "WE ./");
	i++;
	parse->direction[i] = safe_strdup(mm, ZONE_1, "EA ./");
	i++;
	parse->direction[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_tab_fc(t_mm *mm, t_parsing_map *parse)
{
	int	i;

	i = 0;
	parse->fc = safe_malloc(mm, ZONE_1, sizeof(char *) * 3);
	if (!parse->fc)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	parse->fc[i] = safe_strdup(mm, ZONE_1, "F ");
	i++;
	parse->fc[i] = safe_strdup(mm, ZONE_1, "C ");
	i++;
	parse->fc[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_fc(t_game *game, char *str)
{
	char	*line;
	int		fc;
	int		fd;

	fc = count_fc(game->mm, game->parse->fc, str, 0, 0);
	if (fc != 2)
		return (EXIT_FAILURE);
	fd = open_map(str);
	line = safe_get_next_line(game->mm, ZONE_1, fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			safe_free(game->mm, ZONE_1, line);
		else if (ft_strncmp(line, game->parse->fc[0], 2) == 0)
			process_direction(game, line, 4, fd);
		else if (ft_strncmp(line, game->parse->fc[1], 2) == 0)
			process_direction(game, line, 5, fd);
		else
			safe_free(game->mm, ZONE_1, line);
		line = safe_get_next_line(game->mm, ZONE_1, fd);
	}
	return (close_map(fd));
}

int	init_direction(t_game *game, char *str, int dir, int fd)
{
	char	*line;

	dir = count_dir(game->mm, game->parse->direction, str, 0);
	if (dir != 4)
		return (EXIT_FAILURE);
	fd = open_map(str);
	line = safe_get_next_line(game->mm, ZONE_1, fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			safe_free(game->mm, ZONE_1, line);
		else if (ft_strncmp(line, game->parse->direction[0], 5) == 0)
			process_direction(game, line, 0, fd);
		else if (ft_strncmp(line, game->parse->direction[1], 5) == 0)
			process_direction(game, line, 1, fd);
		else if (ft_strncmp(line, game->parse->direction[2], 5) == 0)
			process_direction(game, line, 2, fd);
		else if (ft_strncmp(line, game->parse->direction[3], 5) == 0)
			process_direction(game, line, 3, fd);
		else
			safe_free(game->mm, ZONE_1, line);
		line = safe_get_next_line(game->mm, ZONE_1, fd);
	}
	return (close_map(fd));
}

int	check_map_reel(t_mm *mm, char *str)
{
	int	fd;

	fd = open_map(str);
	if (fd == -1)
		mm_nuclear_exit(mm, ft_error(WHERE, "check_map_reel() failure", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
