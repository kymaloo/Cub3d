/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_fc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:50:48 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 09:51:10 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

int	check_fc(t_data *data)
{
	char	*tmp;

	data->parse->color_ceiling_cp = safe_strdup(ZONE_PARSE, \
												data->colors->color_ceiling);
	data->parse->color_floor_cp = safe_strdup(ZONE_PARSE, \
													data->colors->color_floor);
	if (ft_isdigit(data->colors->color_ceiling[2])
		|| ft_isdigit(data->colors->color_floor[2]))
		nuclear_exit(ft_error(WHERE, \
		"The ceiling or floor isn't valid", EXIT_FAILURE));
	tmp = safe_strdup(ZONE_PARSE, data->colors->color_ceiling);
	safe_free(ZONE_PARSE, data->colors->color_ceiling);
	if (update_color(&data->colors->color_ceiling, tmp) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "The ceiling isn't valid", EXIT_FAILURE));
	tmp = safe_strdup(ZONE_PARSE, data->colors->color_floor);
	safe_free(ZONE_PARSE, data->colors->color_floor);
	if (update_color(&data->colors->color_floor, tmp) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "The floor isn't valid", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	validate_color_format(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if ((color[i] != ',') && (is_white_space(color[i]) == 0 || \
		ft_isdigit(color[i])))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_format_fc(t_colors *colors)
{
	if (validate_color_format(colors->color_ceiling) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "The ceiling isn't valid", EXIT_FAILURE));
	if (validate_color_format(colors->color_floor) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "The floor isn't valid", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	validate_color_range(char *color)
{
	char	**splited;
	int		i;
	int		tmp;

	splited = safe_split(ZONE_PARSE, color, ',');
	i = 0;
	while (splited[i])
	{
		tmp = ft_atoi(splited[i]);
		if (tmp < 0 || tmp > 255)
		{
			memory_manager(DEL_ELEM, ZONE_PARSE, splited);
			return (EXIT_FAILURE);
		}
		i++;
	}
	memory_manager(DEL_ELEM, ZONE_PARSE, splited);
	return (EXIT_SUCCESS);
}

int	verif_colors(t_colors *colors)
{
	if (validate_color_range(colors->color_ceiling) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Format not valid", EXIT_FAILURE));
	if (validate_color_range(colors->color_floor) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Format not valid", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
