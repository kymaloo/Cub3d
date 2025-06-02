/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:51:26 by ekrebs            #+#    #+#             */
/*   Updated: 2025/06/02 17:39:38 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	check_str_char_valid(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ',' && ft_isdigit(str[i]) != EXIT_SUCCESS)
		{
			nuclear_exit(ft_error(__FILE__":", __LINE__, \
				"str no valid", EXIT_FAILURE));
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
											"str no valid", EXIT_FAILURE));
}

void	char_to_rgb(t_colors *colors, char *str, int id)
{
	char	**split;
	int		i;

	i = 0;
	check_str_char_valid(str);
	split = ft_split(str, ',');
	if (split == NULL)
		return ;
	if (!split[0] || !split[1] || !split[2])
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
											"str NULL", EXIT_FAILURE));
	if (id == 0)
		colors->color_floor_uint = get_rgba(ft_atoi(split[0]), \
									ft_atoi(split[1]), ft_atoi(split[2]), 255);
	if (id == 1)
		colors->color_ceiling_uint = get_rgba(ft_atoi(split[0]), \
									ft_atoi(split[1]), ft_atoi(split[2]), 255);
	ft_free_all(split, 0);
	return ;
}
