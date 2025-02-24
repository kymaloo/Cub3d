/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:01 by trgaspar          #+#    #+#             */
/*   Updated: 2025/02/24 16:18:52 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	is_white_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (0);
	return (1);
}

int	get_size_of_array(t_textures *textures, t_parsing_map *p, char **t, int i)
{
	int	j;
	int	size;

	i = 0;
	while (t[i])
	{
		size = ft_strlen_int(t[i]);
		if (check_white_space(t[i]) == 0)
			i++;
		else if (ft_strncmp(t[i], textures->path_north, size) == 0
			|| ft_strncmp(t[i], textures->path_south, size) == 0)
			i++;
		else if (ft_strncmp(t[i], textures->path_east, size) == 0
			|| ft_strncmp(t[i], textures->path_west, size) == 0)
			i++;
		else if (ft_strncmp(t[i], p->color_ceiling_cp, size) == 0
			|| ft_strncmp(t[i], p->color_floor_cp, size) == 0)
			i++;
		else
			break ;
	}
	j = i;
	while (t[i])
		i++;
	return (i - j);
}

int	get_index_before_array(t_infos_p *infos_p, char **array, int i)
{
	int	size;

	i = 0;
	while (array[i])
	{
		size = ft_strlen_int(array[i]);
		if (check_white_space(array[i]) == 0)
			i++;
		else if (ft_strncmp(array[i], \
		infos_p->g->textures->path_north, size) == 0
			|| ft_strncmp(array[i], \
			infos_p->g->textures->path_south, size) == 0)
			i++;
		else if (ft_strncmp(array[i], \
		infos_p->g->textures->path_east, size) == 0
			|| ft_strncmp(array[i], infos_p->g->textures->path_west, size) == 0)
			i++;
		else if (ft_strncmp(array[i], \
		infos_p->p->color_ceiling_cp, size) == 0
			|| ft_strncmp(array[i], infos_p->p->color_floor_cp, size) == 0)
			i++;
		else
			break ;
	}
	return (i);
}

void	get_line_size(t_infos_p *infos_p, char **array)
{
	int	i;
	int	size;

	i = 0;
	size = get_index_before_array(infos_p, array, 0);
	while (i != size)
		i++;
	infos_p->g->map->x_max = ft_strlen_int(array[i]);
	while (array[i])
	{
		if (infos_p->g->map->x_max < ft_strlen_int(array[i]))
			infos_p->g->map->x_max = ft_strlen_int(array[i]);
		i++;
	}
}
