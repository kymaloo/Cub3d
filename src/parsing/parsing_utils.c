/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:51:26 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 20:21:36 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	char_to_rgb(t_colors *colors, char *str, int id)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	if (split == NULL)
		return ;
	if (id == 0)
		colors->color_floor_uint = get_rgba(ft_atoi(split[0]), \
									ft_atoi(split[1]), ft_atoi(split[2]), 255);
	if (id == 1)
		colors->color_ceiling_uint = get_rgba(ft_atoi(split[0]), \
									ft_atoi(split[1]), ft_atoi(split[2]), 255);
	ft_free_all(split, 0);
	return ;
}
