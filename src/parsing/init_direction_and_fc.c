/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_direction_and_fc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:51:27 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 09:51:38 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

int	init_tab_direction(t_parsing_map *parse)
{
	int	i;

	i = 0;
	parse->direction = safe_malloc(ZONE_PARSE, sizeof(char *) * 6);
	if (!parse->direction)
		nuclear_exit(ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	parse->direction[i] = safe_strdup(ZONE_PARSE, "NO ./");
	i++;
	parse->direction[i] = safe_strdup(ZONE_PARSE, "SO ./");
	i++;
	parse->direction[i] = safe_strdup(ZONE_PARSE, "WE ./");
	i++;
	parse->direction[i] = safe_strdup(ZONE_PARSE, "EA ./");
	i++;
	parse->direction[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_tab_fc(t_parsing_map *parse)
{
	int	i;

	i = 0;
	parse->fc = safe_malloc(ZONE_PARSE, sizeof(char *) * 3);
	if (!parse->fc)
		nuclear_exit(ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	parse->fc[i] = safe_strdup(ZONE_PARSE, "F ");
	i++;
	parse->fc[i] = safe_strdup(ZONE_PARSE, "C ");
	i++;
	parse->fc[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_fc(t_data *data, char *str)
{
	int		i;
	int		fd;
	int		fc;

	i = 0;
	fc = count_fc_in_file(data->parse, data->parse->fc);
	if (fc != 2)
		return (EXIT_FAILURE);
	fd = open_map(str);
	while (data->parse->all_file[i])
	{
		if (ft_strncmp(data->parse->all_file[i], data->parse->fc[0], 2) == 0)
			process_direction(data, data->parse->all_file[i], 4, fd);
		else if (ft_strncmp(data->parse->all_file[i], \
													data->parse->fc[1], 2) == 0)
			process_direction(data, data->parse->all_file[i], 5, fd);
		i++;
	}
	return (close_map(fd));
}

int	init_direction(t_data *data, char *str, int dir, int fd)
{
	int		i;

	i = 0;
	dir = count_dir_in_file(data->parse, data->parse->direction);
	if (dir != 4)
		return (EXIT_FAILURE);
	fd = open_map(str);
	while (data->parse->all_file[i])
	{
		if (ft_strncmp(data->parse->all_file[i], \
		data->parse->direction[0], 5) == 0)
			process_direction(data, data->parse->all_file[i], 0, fd);
		else if (ft_strncmp(data->parse->all_file[i], \
		data->parse->direction[1], 5) == 0)
			process_direction(data, data->parse->all_file[i], 1, fd);
		else if (ft_strncmp(data->parse->all_file[i], \
		data->parse->direction[2], 5) == 0)
			process_direction(data, data->parse->all_file[i], 2, fd);
		else if (ft_strncmp(data->parse->all_file[i], \
		data->parse->direction[3], 5) == 0)
			process_direction(data, data->parse->all_file[i], 3, fd);
		i++;
	}
	return (close_map(fd));
}

int	check_map_reel(char *str)
{
	int	fd;

	fd = open_map(str);
	if (fd == -1)
		nuclear_exit(ft_error(WHERE, \
		"check_map_reel() failure", EXIT_FAILURE));
	close_map(fd);
	return (EXIT_SUCCESS);
}
