/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:08:58 by trgaspar          #+#    #+#             */
/*   Updated: 2025/02/21 15:27:40 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

int	count_line_in_file(t_mm *mm, char *str)
{
	int		fd;
	int		count;
	char	*line;

	fd = open_map(str);
	count = 0;
	line = safe_get_next_line(mm, ZONE_1, fd);
	while (line != NULL)
	{
		safe_free(mm, ZONE_1, line);
		count++;
		line = safe_get_next_line(mm, ZONE_1, fd);
	}
	close_map(fd);
	return (count);
}

char	**stock_file(t_mm *mm, char *str)
{
	int		i;
	int		fd;
	int		count;
	char	**result;

	i = 0;
	fd = open_map(str);
	count = count_line_in_file(mm, str);
	result = safe_malloc(mm, ZONE_PARSING_TMP, sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (i < count)
	{
		result[i] = safe_get_next_line(mm, ZONE_PARSING_TMP, fd);
		i++;
	}
	result[i] = NULL;
	close_map(fd);
	return (result);
}

char	**extract_map(t_game *game, char **array)
{
	int		i;
	int		j;
	int		len;
	int		size;
	char	**result;

	i = 0;
	j = 0;
	size = get_size_of_array(game, array, 0);
	len = get_line_size(game, array);
	result = safe_calloc(game->mm, ZONE_1, 1, (sizeof(char *) * (size + 1)));
	if (!result)
		return (NULL);
	while (i != get_index_before_array(game, array))
		i++;
	while (array[i])
	{
		result[j] = safe_strdup_with_calloc(game->mm, \
		ZONE_1, array[i], len + 1);
		i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

void	copy_map(t_game *game)
{
	int		i;
	int		len;
	int		size;

	i = 0;
	size = get_size_of_array(game, game->parse->grid, 0);
	len = get_line_size(game, game->parse->all_file);
	game->parse->grid_copy = safe_calloc(game->mm, ZONE_1, \
	1, sizeof(char *) * (size + 1));
	if (!game->parse->grid_copy)
		return ;
	while (game->parse->grid[i])
	{
		game->parse->grid_copy[i] = safe_strdup_with_calloc(game->mm, \
		ZONE_1, game->parse->grid[i], len + 1);
		i++;
	}
	game->parse->grid_copy[i] = NULL;
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
