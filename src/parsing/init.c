/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:08:44 by trgaspar          #+#    #+#             */
/*   Updated: 2025/02/21 16:54:04 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

static int	init_direction_and_fc(t_parsing_map *p)
{
	if (init_tab_direction(p) == EXIT_FAILURE)
		mm_nuclear_exit(ft_error(WHERE, "Init Tab Direction Failed", EXIT_FAILURE));
	if (init_tab_fc(p) == EXIT_FAILURE)
		mm_nuclear_exit(ft_error(WHERE, "Init Tab Fc Failed", EXIT_FAILURE));
	if (init_direction(game, str, 0, 0) == EXIT_FAILURE)
		mm_nuclear_exit(ft_error(WHERE, "Init Direction Failed", EXIT_FAILURE));
	if (init_fc(game, str) == EXIT_FAILURE)
		mm_nuclear_exit(ft_error(WHERE, "Init Fc Failed", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static int	init_map(t_game *game)
{
	game->parse->grid = extract_map(game, game->parse->all_file);
	if (check_map(game->parse->grid) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_doublon_map(game->parse->grid, "NSEW") != 1)
		mm_nuclear_exit(game->mm, ft_error(WHERE, \
		"ONE PLEYER PLSSSS 🤓", EXIT_FAILURE));
	copy_map(game);
	return (EXIT_SUCCESS);
}

static void	is_dir_and_filled(t_game *game)
{
	if (game->parse->path_east == NULL)
		mm_nuclear_exit(game->mm, ft_error(WHERE, \
		"Path east is Null", EXIT_FAILURE));
	if (game->parse->path_west == NULL)
		mm_nuclear_exit(game->mm, ft_error(WHERE, \
		"Path west is Null", EXIT_FAILURE));
	if (game->parse->path_north == NULL)
		mm_nuclear_exit(game->mm, ft_error(WHERE, \
		"Path north is Null", EXIT_FAILURE));
	if (game->parse->path_south == NULL)
		mm_nuclear_exit(game->mm, ft_error(WHERE, \
		"Path south is Null", EXIT_FAILURE));
	if (game->parse->color_ceiling == NULL)
		mm_nuclear_exit(game->mm, ft_error(WHERE, \
		"Path ceilling is Null", EXIT_FAILURE));
	if (game->parse->color_floor == NULL)
		mm_nuclear_exit(game->mm, ft_error(WHERE, \
		"Path floor is Null", EXIT_FAILURE));
}

int	init(t_infos_p *infos_p, char *str)
{
	if (check_map_format_cub(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_map_reel(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	infos_p->p->all_file = stock_file(str);


	
	if (init_direction_and_fc(game, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	is_dir_and_filled(game);
	if (all_line_is_valid(game, game->parse->all_file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_fc(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_format_fc(game->mm, game->parse) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (verif_colors(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_map(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mm_area_free_elem(game->mm, ZONE_1, game->parse->all_file);
	if (check_wall(game->mm, game->parse) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mm_area_delete(game->mm, ZONE_1);
	return (EXIT_SUCCESS);
}

int	all_line_is_valid(t_game *game, char **array)
{
	int	i;
	int	size;

	i = 0;
	while (array[i])
	{
		size = ft_strlen_int(array[i]);
		if (check_white_space(array[i]) == 0 || \
		char_valid_for_map("01NSEWD\t ", array[i]) == 0)
			i++;
		else if (ft_strncmp(array[i], game->parse->path_north, size) == 0 || \
		ft_strncmp(array[i], game->parse->path_south, size) == 0)
			i++;
		else if (ft_strncmp(array[i], game->parse->path_east, size) == 0 || \
		ft_strncmp(array[i], game->parse->path_west, size) == 0)
			i++;
		else if (ft_strncmp(array[i], game->parse->color_ceiling, size) == 0 || \
		ft_strncmp(array[i], game->parse->color_floor, size) == 0)
			i++;
		else
			mm_nuclear_exit(game->mm, ft_error(WHERE, \
			"Line isn't valid", EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}
