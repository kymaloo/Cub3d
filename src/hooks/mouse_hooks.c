/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:09:23 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 13:47:07 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	mouse_rotations(t_game *game, int32_t old_xpos, int32_t xpos)
{
	bool	moved;
	int32_t	delta_mouse_x;

	moved = false;
	delta_mouse_x = xpos - old_xpos;
	if (delta_mouse_x >= MOUSE_MOUVEMENT_DETECTION_THRESHOLD \
		|| delta_mouse_x <= -MOUSE_MOUVEMENT_DETECTION_THRESHOLD)
	{
		if (DEBUG_MOUSE)
		{
			print_debug_prefix(__FILE__, __LINE__, __FUNCTION__, "MOUSE ROTAT");
			print_player_infos(game->player, "before");
			print_map_player(game, 5);
		}
		game->player->radian += delta_mouse_x * MOUSE_SENSITIVITY;
		moved = true;
	}
	if (moved)
	{
		game->player->radian = normalize_angle(game->player->radian);
		update_player_direction(game->player);
		if (DEBUG_MOUSE)
			print_player_infos(game->player, "rotated");
	}
	return (moved);
}

void	ft_cursor_hook(double xpos, double ypos, void *game_data)
{
	static int32_t	old_xpos = -1;
	t_game			*game;

	game = game_data;
	(void) ypos;
	if (old_xpos == -1)
		old_xpos = (int32_t) xpos;
	if (game->toggles.catch_mouse_cursor == true)
		mouse_rotations(game, old_xpos, xpos);
	old_xpos = (int32_t) xpos;
}

void	toggle_mouse_capture(mlx_t *mlx, t_toggles *toggles)
{
	toggles->catch_mouse_cursor = !toggles->catch_mouse_cursor;
	if (toggles->catch_mouse_cursor == true)
		mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	else
		mlx_set_cursor_mode(mlx, MLX_MOUSE_NORMAL);
}

void	ft_mouse_hook(mouse_key_t button, action_t action, \
										modifier_key_t mods, void *game_data)
{
	t_game	*game;

	(void) mods;
	game = game_data;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		toggle_mouse_capture(game->mlx, &game->toggles);
}
