/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:56:02 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 10:47:24 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_map_tile(char map_char)
{
	if (map_char == '1')
		printf(BWHITE"[]"RESET);
	else if (map_char == '0')
		printf(" ."RESET);
	else if (map_char == 'D')
		printf(BGYELLOW"++"RESET);
	else if (map_char == 'd')
		printf(BGYELLOW"  "RESET);
	else if (map_char == 'P')
		printf(BBLUE"xx"RESET);
	else
		printf(BGMAGENTA"ER"RESET);
}

void	print_map_around(t_game *g, int x, int y, int offset)
{
	int	xmin;
	int	xmax;
	int	ymin;
	int	ymax;
	int	i;
	int	j;

	xmin = x - offset;
	xmax = x + offset;
	ymin = y - offset;
	ymax = y + offset;
	if (xmin < 0)
		xmin = 0;
	if (xmax >= g->map->x_max)
		xmax = g->map->x_max -1;
	if (ymin < 0)
		ymin = 0;
	if (ymax >= g->map->y_max)
		ymax = g->map->y_max -1;
	printf("\ncurrent grid situation: \n");
	j = ymin;
	while (j <= ymax)
	{
		i = xmin;
		while (i <= xmax)
		{
			print_map_tile(g->map->grid[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

void	print_map_player(t_game *g, int offset)
{
	int xmin, xmax, ymin, ymax, i, j;
	int	xa, ya, xt, yt;
	float xb, yb;
	t_player *p;

	p = g->player;
	xa = p->position[X]; 
	ya = p->position[Y]; 
	xb = p->position[X] + p->direction[X] * 0.3; 
	yb = p->position[Y] + p->direction[Y] * 0.3;
	xmin = xa - offset;
	xmax = xa + offset;
	ymin = ya - offset;
	ymax = ya + offset;
	if (xmin < 0)
		xmin = 0;
	if (xmax > g->map->x_max -1)
		xmax = g->map->x_max -1;
	if (ymin < 0)
		ymin = 0;
	if (ymax > g->map->y_max -1)
		ymax = g->map->y_max -1;
	print_coord("player is:", "", xa, ya);
	print_coord("targeting move:", "", xb, yb);
	xt = xb;
	yt = yb;
	print_coord("targeting grid:", "", xt, yt);
	printf("\ncurrent grid situation: \n");
	j = ymin;
	while (j <= ymax)
	{
		i = xmin;
		while (i <= xmax)
		{
			if (i == xt && j == yt)
				printf(BGBLUE"");
			if (i == xa && j == ya)
				printf(BBLUE"xx"RESET);
			else
				print_map_tile(g->map->grid[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}
