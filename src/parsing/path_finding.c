/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:52:05 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 09:54:47 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

static void	find_last_floor(t_parsing_map *p)
{
	int	y;
	int	x;

	y = 0;
	while (p->grid_copy[y])
	{
		x = 0;
		while (p->grid_copy[y][x])
		{
			if (p->grid_copy[y][x] == '0')
			{
				p->x_last_0 = x;
				p->y_last_0 = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

bool	isset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (true);
		i++;
	}
	return (false);
}

static void	flood_fill_rec(int x, int y, t_data *data, int i)
{
	char	**cells;
	char	*legal_grid_chars;

	legal_grid_chars = "NSEW01D\n\0 \t";
	cells = data->parse->grid_copy;
	if (x < 0 || x > data->game->map->x_max || y < 0 \
											|| y > data->game->map->y_max - 1)
		nuclear_exit(ft_error(WHERE, \
			"map walling not valid: illegal coords", EXIT_FAILURE));
	if (isset(cells[y][x], legal_grid_chars) == false)
		nuclear_exit(ft_error(WHERE, \
			"map walling not valid: illegal char used", EXIT_FAILURE));
	if (cells[y][x] == '1')
		return ;
	cells[y][x] = '1';
	i = i + 1;
	flood_fill_rec(x, y + 1, data, i);
	flood_fill_rec(x, y - 1, data, i);
	flood_fill_rec(x + 1, y, data, i);
	flood_fill_rec(x - 1, y, data, i);
	return ;
}

int	check_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->parse->grid_copy[i])
	{
		j = 0;
		while (data->parse->grid_copy[i][j])
		{
			if (isset(data->parse->grid_copy[i][j], "NSEW0") == true)
			{
				find_last_floor(data->parse);
				flood_fill_rec(data->parse->x_last_0, \
												data->parse->y_last_0, data, 1);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	find_pos_player(t_game *game, char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S'
				|| grid[i][j] == 'E' || grid[i][j] == 'W')
			{
				game->player->facing = grid[i][j];
				game->player->position[X] = j;
				game->player->position[Y] = i;
				if (DEBUG)
				{
					print_debug_prefix(WHERE_FUNC, "");
					printf("player position:\t"RED" x: %-4d"GREEN" y: %-4d"RESET"\n", j, i);
				}
				break ;
			}
			j++;
		}
		i++;
	}
}
