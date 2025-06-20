/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:59:09 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 17:50:33 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

int	count_line_in_file(char *str)
{
	int		fd;
	int		count;
	char	*line;

	fd = open_map(str);
	count = 0;
	line = safe_get_next_line(ZONE_PARSE, fd);
	while (line != NULL)
	{
		safe_free(ZONE_PARSE, line);
		count++;
		line = safe_get_next_line(ZONE_PARSE, fd);
	}
	close_map(fd);
	return (count);
}

char	**stock_file(char *str)
{
	int		i;
	int		fd;
	int		count;
	char	**result;

	i = 0;
	fd = open_map(str);
	count = count_line_in_file(str);
	result = safe_malloc(ZONE_PARSE, sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (i < count)
	{
		result[i] = safe_get_next_line(ZONE_PARSE, fd);
		i++;
	}
	result[i] = NULL;
	close_map(fd);
	return (result);
}

char	**extract_map(t_data *data, char **array)
{
	int		i;
	int		j;
	int		len;
	int		size;
	char	**result;

	i = 0;
	j = 0;
	size = get_size_of_array(data, array, 1);
	data->game->map->y_max = size;
	get_line_size(data, array);
	len = data->game->map->x_max;
	result = safe_calloc(ZONE_PARSE, 1, (sizeof(char *) * (size + 1)));
	if (!result)
		return (NULL);
	while (i != get_index_before_array(data, array, 0))
		i++;
	while (array[i])
	{
		result[j] = safe_strdup_with_calloc(ZONE_PARSE, array[i], len + 1);
		i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

void	copy_map(t_data *data)
{
	int		i;
	int		len;
	int		size;

	i = 0;
	size = data->game->map->y_max;
	len = data->game->map->x_max;
	data->parse->grid_copy = safe_calloc(ZONE_PARSE, 1, \
												sizeof(char *) * (size + 1));
	if (!data->parse->grid_copy)
		return ;
	while (data->game->map->grid[i])
	{
		data->parse->grid_copy[i] = safe_strdup_with_calloc(ZONE_PARSE, \
		data->game->map->grid[i], len + 1);
		i++;
	}
	data->parse->grid_copy[i] = NULL;
}

int	char_valid_for_map(char *cmp, char *str)
{
	int	i;
	int	j;
	int	size;
	int	count;

	i = 0;
	count = 0;
	size = ft_strlen_int(str);
	while (str[i])
	{
		j = 0;
		while (cmp[j])
		{
			if (str[i] == cmp[j])
				count++;
			j++;
		}
		i++;
	}
	if (size != count)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
