/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_translations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:57 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 12:19:43 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	try_move_to(t_player *p, t_map *map, float new_x, float new_y)
{
	if (!is_wall(map, new_x + PLAYER_WIDTH, p->position[Y] + PLAYER_WIDTH) \
	&& !is_wall(map, new_x - PLAYER_WIDTH, p->position[Y] + PLAYER_WIDTH) \
	&& !is_wall(map, new_x + PLAYER_WIDTH, p->position[Y] - PLAYER_WIDTH) \
	&& !is_wall(map, new_x - PLAYER_WIDTH, p->position[Y] - PLAYER_WIDTH))
	{
		p->position[X] = new_x;
	}
	if (!is_wall(map, p->position[X] + PLAYER_WIDTH, new_y + PLAYER_WIDTH) \
	&& !is_wall(map, p->position[X] - PLAYER_WIDTH, new_y + PLAYER_WIDTH) \
	&& !is_wall(map, p->position[X] + PLAYER_WIDTH, new_y - PLAYER_WIDTH) \
	&& !is_wall(map, p->position[X] - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[Y] = new_y;
	}
}

void	move_translate_forward(t_game *game)
{
	t_player	*p;
	float		new_x;
	float		new_y;

	p = game->player;
	new_x = p->position[X] + p->direction[X] * MOVE_SPEED;
	new_y = p->position[Y] + p->direction[Y] * MOVE_SPEED;
	if (DEBUG_KEYS)
	{
		print_debug_prefix(WHERE_FUNC, "UP");
		print_player_infos(game->player, "before");
		print_coord("trying to move to:", "", new_x, new_y);
		print_map_player(game, 5);
	}
	try_move_to(p, game->map, new_x, new_y);
	if (DEBUG_KEYS)
		print_player_infos(game->player, "after");
}

void	move_translate_backward(t_game *game)
{
	t_player	*p;
	float		new_x;
	float		new_y;

	p = game->player;
	new_x = p->position[X] - (p->direction[X] * MOVE_SPEED);
	new_y = p->position[Y] - (p->direction[Y] * MOVE_SPEED);
	if (DEBUG_KEYS)
	{
		print_debug_prefix(WHERE_FUNC, "DOWN");
		print_player_infos(game->player, "before");
		print_coord("trying to move to:", "", new_x, new_y);
		print_map_player(game, 5);
	}
	try_move_to(p, game->map, new_x, new_y);
	if (DEBUG_KEYS)
		print_player_infos(game->player, "after");
}

void	move_translate_left(t_game *game)
{
	t_player	*p;
	float		new_x;
	float		new_y;

	p = game->player;
	new_x = p->position[X] + (p->direction[Y] * MOVE_SPEED);
	new_y = p->position[Y] - (p->direction[X] * MOVE_SPEED);
	if (DEBUG_KEYS)
	{
		print_debug_prefix(WHERE_FUNC, "LEFT");
		print_player_infos(game->player, "before");
		print_coord("trying to move to:", "", new_x, new_y);
		print_map_player(game, 5);
	}
	try_move_to(p, game->map, new_x, new_y);
	if (DEBUG_KEYS)
		print_player_infos(game->player, "after");
}

void	move_translate_right(t_game *game)
{
	t_player	*p;
	float		new_x;
	float		new_y;

	p = game->player;
	new_x = p->position[X] - (p->direction[Y] * MOVE_SPEED);
	new_y = p->position[Y] + (p->direction[X] * MOVE_SPEED);
	if (DEBUG_KEYS)
	{
		print_debug_prefix(WHERE_FUNC, "RIGHT");
		print_player_infos(game->player, "before");
		print_coord("trying to move to:", "", new_x, new_y);
		print_map_player(game, 5);
	}
	try_move_to(p, game->map, new_x, new_y);
	if (DEBUG_KEYS)
		print_player_infos(game->player, "after");
}
