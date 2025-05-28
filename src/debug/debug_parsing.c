/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:42:09 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 20:42:51 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	debug_parsing_player_pos(t_game *game, int i, int j)
{
	(void) game;
	print_debug_prefix(WHERE_FUNC, "");
	printf("player position:\t"RED" x: %-4d" \
								GREEN" y: %-4d"RESET"\n", j, i);
}

void	printf_funky_grid_tile(char c)
{
	if (c == '\0')
		printf(BGBLUE"\\0"RESET);
	else if (c == '1')
		printf(BGWHITE" 1"RESET);
	else if (c == '0')
		printf(BGYELLOW" 0"RESET);
	else if (c == 'N' || c == 'S' \
		|| c == 'E' || c == 'W' )
		printf(BGGREEN" %c"RESET, c);
	else if (c == ' ')
		printf(BGBLUE" ."RESET);
	else
		printf(BGMAGENTA" %c"RESET, c);
}

void	debug_map_extraction(t_map *map)
{
	int	y;
	int	x;

	print_debug_prefix(WHERE_FUNC, "Debug map extraction\n\n");
	y = -1;
	while (++y <= map->y_max - 1)
	{
		x = -1;
		while (++x <= map->x_max - 1)
		{
			printf_funky_grid_tile(map->grid[y][x]);
		}
		printf(BGBBLUE"\\0"RESET"\n");
	}
	printf("\n");
}
