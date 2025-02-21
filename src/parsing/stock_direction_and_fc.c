/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_direction_and_fc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:08:54 by trgaspar          #+#    #+#             */
/*   Updated: 2025/02/21 16:07:01 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

static void	save_path(t_mm *mm, t_parsing_map *parse, char *line, int dir_index)
static void	save_path(t_mm *mm, t_parsing_map *parse, char *line, int dir_index)
{
	if (dir_index == 0)
		parse->path_north = safe_strdup(mm, ZONE_1, line);
		parse->path_north = safe_strdup(mm, ZONE_1, line);
	else if (dir_index == 1)
		parse->path_south = safe_strdup(mm, ZONE_1, line);
		parse->path_south = safe_strdup(mm, ZONE_1, line);
	else if (dir_index == 2)
		parse->path_west = safe_strdup(mm, ZONE_1, line);
		parse->path_west = safe_strdup(mm, ZONE_1, line);
	else if (dir_index == 3)
		parse->path_east = safe_strdup(mm, ZONE_1, line);
		parse->path_east = safe_strdup(mm, ZONE_1, line);
	else if (dir_index == 4)
		parse->color_floor = safe_strdup(mm, ZONE_1, line);
		parse->color_floor = safe_strdup(mm, ZONE_1, line);
	else if (dir_index == 5)
		parse->color_ceiling = safe_strdup(mm, ZONE_1, line);
		parse->color_ceiling = safe_strdup(mm, ZONE_1, line);
}

static	int	check_doublon(t_mm *mm, char *direction, char *line, int fd)
static	int	check_doublon(t_mm *mm, char *direction, char *line, int fd)
{
	printf("Error: Find duplicate for %s\n", direction);
	safe_free(mm, ZONE_1, line);
	close_map(fd);
	return (EXIT_FAILURE);
}

int	process_direction(t_game *game, char *line, int dir_i, int fd)
{
	if (dir_i == 0 && game->parse->path_north != NULL)
		return (check_doublon(game->mm, "north", line, fd));
	if (dir_i == 1 && game->parse->path_south != NULL)
		return (check_doublon(game->mm, "south", line, fd));
	if (dir_i == 2 && game->parse->path_west != NULL)
		return (check_doublon(game->mm, "west", line, fd));
	if (dir_i == 3 && game->parse->path_east != NULL)
		return (check_doublon(game->mm, "east", line, fd));
	if (dir_i == 4 && game->parse->color_floor != NULL)
		return (check_doublon(game->mm, "floor", line, fd));
	if (dir_i == 5 && game->parse->color_ceiling != NULL)
		return (check_doublon(game->mm, "ceiling", line, fd));
	save_path(game->mm, game->parse, line, dir_i);
	return (EXIT_SUCCESS);
}

int	count_dir_in_file(t_game *game, char **dir)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (game->parse->all_file[i])
	{
		if (strncmp_with_array(game->parse->all_file[i], dir, 5) != -1)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

int	count_fc_in_file(t_game *game, char **dir)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (game->parse->all_file[i])
	{
		if (strncmp_with_array(game->parse->all_file[i], dir, 2) != -1)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}
