#include "cub.h"
#include "parsing_interns.h"

int	init_tab_direction(t_mm *mm, t_parsing_map *parse)
{
	int	i;

	i = 0;
	map->direction = safe_malloc(mm, ZONE_1, sizeof(char *) * 6);
	if (!map->direction)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	map->direction[i] = safe_strdup(mm, ZONE_1, "NO ./");
	i++;
	map->direction[i] = safe_strdup(mm, ZONE_1, "SO ./");
	i++;
	map->direction[i] = safe_strdup(mm, ZONE_1, "WE ./");
	i++;
	map->direction[i] = safe_strdup(mm, ZONE_1, "EA ./");
	i++;
	map->direction[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_tab_fc(t_mm *mm, t_parsing_map *parse)
{
	int	i;

	i = 0;
	map->fc = safe_malloc(mm, ZONE_1, sizeof(char *) * 3);
	if (!map->fc)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	map->fc[i] = safe_strdup(mm, ZONE_1, "F ");
	i++;
	map->fc[i] = safe_strdup(mm, ZONE_1, "C ");
	i++;
	map->fc[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_fc(t_mm *mm, t_parsing_map *parse, char *str)
{
	char	*line;
	int		fc;
	int		fd;

	fc = count_fc(mm, map->fc, str, 0, 0);
	if (fc != 2)
		return (EXIT_FAILURE);
	fd = open_map(str);
	line = safe_get_next_line(mm, ZONE_1, fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			safe_free(mm, ZONE_1, line);
		else if (ft_strncmp(line, map->fc[0], 2) == 0)
			process_direction(mm, map, line, 4, fd);
		else if (ft_strncmp(line, map->fc[1], 2) == 0)
			process_direction(mm, map, line, 5, fd);
		else
			safe_free(mm, ZONE_1, line);
		line = safe_get_next_line(mm, ZONE_1, fd);
	}
	return (close_map(fd));
}

int	init_direction(t_game *game, char *str, int dir, int fd)
{
	char	*line;

	dir = count_dir(game->mm, game->parse->direction, str, 0, 0);
	if (dir != 4)
		return (EXIT_FAILURE);
	fd = open_map(str);
	line = safe_get_next_line(game->mm, ZONE_1, fd);
	while (line != NULL)
	{
		if (check_white_space(line) == 0)
			safe_free(game->mm, ZONE_1, line);
		else if (ft_strncmp(line, game->parse->direction[0], 5) == 0)
			process_direction(game->mm, game->parse, line, 0, fd);
		else if (ft_strncmp(line, game->parse->direction[1], 5) == 0)
			process_direction(game->mm, game->parse, line, 1, fd);
		else if (ft_strncmp(line, game->parse->direction[2], 5) == 0)
			process_direction(game->mm, game->parse, line, 2, fd);
		else if (ft_strncmp(line, game->parse->direction[3], 5) == 0)
			process_direction(game->mm, game->parse, line, 3, fd);
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
