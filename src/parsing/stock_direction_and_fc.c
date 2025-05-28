/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_direction_and_fc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:46:01 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 09:46:03 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

static void	save_path(t_data *data, char *line, int dir_index)
{
	if (dir_index == 0)
		data->game->path->north = safe_strdup(ZONE_PARSE, line);
	else if (dir_index == 1)
		data->game->path->south = safe_strdup(ZONE_PARSE, line);
	else if (dir_index == 2)
		data->game->path->west = safe_strdup(ZONE_PARSE, line);
	else if (dir_index == 3)
		data->game->path->east = safe_strdup(ZONE_PARSE, line);
	else if (dir_index == 4)
		data->colors->color_floor = safe_strdup(ZONE_PARSE, line);
	else if (dir_index == 5)
		data->colors->color_ceiling = safe_strdup(ZONE_PARSE, line);
}

static	int	check_doublon(char *direction, char *line, int fd)
{
	printf("Error: Find duplicate for %s\n", direction);
	safe_free(ZONE_PARSE, line);
	close_map(fd);
	return (EXIT_FAILURE);
}

int	process_direction(t_data *data, char *line, int dir_i, int fd)
{
	if (dir_i == 0 && data->game->path->north != NULL)
		return (check_doublon("north", line, fd));
	if (dir_i == 1 && data->game->path->south != NULL)
		return (check_doublon("south", line, fd));
	if (dir_i == 2 && data->game->path->west != NULL)
		return (check_doublon("west", line, fd));
	if (dir_i == 3 && data->game->path->east != NULL)
		return (check_doublon("east", line, fd));
	if (dir_i == 4 && data->colors->color_floor != NULL)
		return (check_doublon("floor", line, fd));
	if (dir_i == 5 && data->colors->color_ceiling != NULL)
		return (check_doublon("ceiling", line, fd));
	save_path(data, line, dir_i);
	return (EXIT_SUCCESS);
}

int	count_dir_in_file(t_parsing_map *p, char **dir)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (p->all_file[i])
	{
		if (strncmp_with_array(p->all_file[i], dir, 5) != -1)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

int	count_fc_in_file(t_parsing_map *p, char **dir)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (p->all_file[i])
	{
		if (strncmp_with_array(p->all_file[i], dir, 2) != -1)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}
