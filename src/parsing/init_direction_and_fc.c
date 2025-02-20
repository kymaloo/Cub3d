#include "cub.h"
#include "parsing_interns.h"

int	init_tab_direction(t_mm *mm, t_parsing_map *parse)
{
	int	i;

	i = 0;
	parse->direction = safe_malloc(mm, ZONE_PARSING_TMP, sizeof(char *) * 6);
	if (!parse->direction)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	parse->direction[i] = safe_strdup(mm, ZONE_PARSING_TMP, "NO ./");
	i++;
	parse->direction[i] = safe_strdup(mm, ZONE_PARSING_TMP, "SO ./");
	i++;
	parse->direction[i] = safe_strdup(mm, ZONE_PARSING_TMP, "WE ./");
	i++;
	parse->direction[i] = safe_strdup(mm, ZONE_PARSING_TMP, "EA ./");
	i++;
	parse->direction[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_tab_fc(t_mm *mm, t_parsing_map *parse)
{
	int	i;

	i = 0;
	parse->fc = safe_malloc(mm, ZONE_PARSING_TMP, sizeof(char *) * 3);
	if (!parse->fc)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	parse->fc[i] = safe_strdup(mm, ZONE_PARSING_TMP, "F ");
	i++;
	parse->fc[i] = safe_strdup(mm, ZONE_PARSING_TMP, "C ");
	i++;
	parse->fc[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_fc(t_game *game, char *str)
{
	int		i;
	int		fd;
	int		fc;

	i = 0;
	fc = count_fc_in_file(game, game->parse->fc);
	if (fc != 2)
		return (EXIT_FAILURE);
	fd = open_map(str);
	
	while (game->parse->all_file[i])
	{
		if (ft_strncmp(game->parse->all_file[i], game->parse->fc[0], 2) == 0)
			process_direction(game, game->parse->all_file[i], 4, fd);
		else if (ft_strncmp(game->parse->all_file[i], game->parse->fc[1], 2) == 0)
			process_direction(game, game->parse->all_file[i], 5, fd);
		i++;
	}
	return (close_map(fd));
}

int	init_direction(t_game *game, char *str, int dir, int fd)
{
	int		i;

	i = 0;
	dir = count_dir_in_file(game, game->parse->direction);
	if (dir != 4)
		return (EXIT_FAILURE);
	fd = open_map(str);
	while (game->parse->all_file[i])
	{
		if (ft_strncmp(game->parse->all_file[i], game->parse->direction[0], 5) == 0)
			process_direction(game, game->parse->all_file[i], 0, fd);
		else if (ft_strncmp(game->parse->all_file[i], game->parse->direction[1], 5) == 0)
			process_direction(game, game->parse->all_file[i], 1, fd);
		else if (ft_strncmp(game->parse->all_file[i], game->parse->direction[2], 5) == 0)
			process_direction(game, game->parse->all_file[i], 2, fd);
		else if (ft_strncmp(game->parse->all_file[i], game->parse->direction[3], 5) == 0)
			process_direction(game, game->parse->all_file[i], 3, fd);
		i++;
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
