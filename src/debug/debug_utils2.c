/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:00:28 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 13:43:55 by ekrebs           ###   ########.fr       */
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
		printf("{}"RESET);
	else if (map_char == 'N' || map_char == 'S' || map_char == 'E' \
		|| map_char == 'W')
		printf(BBLUE" %c"RESET, map_char);
	else if (map_char == ' ')
		printf(BGBLACK"sp"RESET);
	else if (map_char == '\0')
		printf("\\0"RESET);
	else
		printf(MAGENTA"ER"RESET);
}

static void	init_debug_map(struct s_debug_map *s, t_game *g, int offset)
{
	s->a[X] = g->player->position[X];
	s->a[Y] = g->player->position[Y];
	s->b[X] = g->player->position[X] + g->player->direction[X] * 0.3;
	s->b[Y] = g->player->position[Y] + g->player->direction[Y] * 0.3;
	s->min[X] = s->a[X] - offset;
	s->max[X] = s->a[X] + offset;
	s->min[Y] = s->a[Y] - offset;
	s->max[Y] = s->a[Y] + offset;
	if (s->min[X] < 0)
		s->min[X] = 0;
	if (s->max[X] > g->map->x_max -1)
		s->max[X] = g->map->x_max -1;
	if (s->min[Y] < 0)
		s->min[Y] = 0;
	if (s->max[Y] > g->map->y_max -1)
		s->max[Y] = g->map->y_max -1;
	s->target[X] = s->b[X];
	s->target[Y] = s->b[Y];
	print_coord("player is:", "", s->a[X], s->a[Y]);
	print_coord("targeting move:", "", s->b[X], s->b[Y]);
	print_coord("targeting grid:", "", s->target[X], s->target[Y]);
}

void	print_map_player(t_game *g, int offset)
{
	struct s_debug_map	s;
	int					i;
	int					j;
	t_player			*p;

	p = g->player;
	init_debug_map(&s, g, offset);
	printf("\ncurrent grid situation: \n");
	j = s.min[Y];
	while (j <= s.max[Y])
	{
		i = s.min[X];
		while (i <= s.max[X])
		{
			if (i == s.target[X] && j == s.target[Y])
				printf(BGBLUE"");
			if (i == s.a[X] && j == s.a[Y])
				printf(BBLUE"xx"RESET);
			else
				print_map_tile(g->map->grid[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}
