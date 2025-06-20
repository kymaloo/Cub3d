/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:48:17 by ekrebs            #+#    #+#             */
/*   Updated: 2025/06/18 02:17:13 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

/**
 * @brief	check first line is valid
 * @returns true if works, false in case of failure,
 */
static int	line_top(char **array)
{
	int		i;
	char	*legal_char;

	i = 0;
	legal_char = "1\n \t";
	while (array[0][i])
	{
		if (array[0][i] != '\0' && isset(array[0][i], legal_char) == 0)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

static int	line_bot(char **array, int y_max)
{
	char	*legal_char;
	int		i;

	i = 0;
	legal_char = "1\n \t";
	while (array[y_max][i])
	{
		if (array[y_max][i] != '\0' && isset(array[y_max][i], legal_char) == 0)
			return (false);
		i++;
	}
	return (true);
}

static int	line_left(char **array)
{
	char	*legal_char;
	int		y;

	y = 0;
	legal_char = "1\n \t";
	while (array[y])
	{
		if (array[y][0] != '\0' && isset(array[y][0], legal_char) == 0)
			return (false);
		y++;
	}
	return (true);
}

static int	line_right(char **array, int x_max)
{
	char	*legal_char;
	int		y;

	y = 0;
	legal_char = "1\n \t";
	while (array[y])
	{
		if (array[y][x_max] != '\0' \
								&& isset(array[y][x_max], legal_char) == false)
			return (false);
		y++;
	}
	return (true);
}

/**
 * 
 * @returns  
 */
int	check_line_map(t_map *map)
{
	if (line_top(map->grid) == false)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
								"Bad characters for borders\n", EXIT_FAILURE));
	if (line_bot(map->grid, map->y_max - 1) == false)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
								"Bad characters for borders\n", EXIT_FAILURE));
	if (line_left(map->grid) == false)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
								"Bad characters for borders\n", EXIT_FAILURE));
	if (line_right(map->grid, map->x_max - 1) == false)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
								"Bad characters for borders\n", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
