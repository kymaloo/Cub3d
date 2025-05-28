/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:15:24 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 10:16:52 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_wall(t_map *map, int x, int y)
{
	if (x > map->x_max -1 || x < 0 || y > map->y_max -1 || y < 0)
		return (true);
	if (isset(map->grid[y][x], "1D") == true)
		return (true);
	return (false);
}

static int	check_colors_for_map(char c)
{
	if (c == '1')
		return (C_WALL_BLACK);
	if (c == '0')
		return (C_FLOOR_BROWN);
	if (c == 'D')
		return (C_BLUE);
	return (C_GREY_INVALID);
}

static void	draw_square(t_game *g, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	printf("%d\n", TILE_SIZE_MINIMAP);
	while (i < TILE_SIZE_MINIMAP)
	{
		j = 0;
		while (j < TILE_SIZE_MINIMAP)
		{
			mlx_put_pixel(g->texture->image->img_window, \
											x + j, y + i, g->colors_minimap);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map->grid[y])
	{
		x = 0;
		while (game->map->grid[y][x])
		{
			game->colors_minimap = check_colors_for_map(game->map->grid[y][x]);
			draw_square(game, x * TILE_SIZE_MINIMAP, y * TILE_SIZE_MINIMAP);
			x++;
		}
		y++;
	}
}
