/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:03:59 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 21:01:44 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_keys_movement_translations(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) \
		|| mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		move_translate_forward(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) \
		|| mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		move_translate_backward(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_translate_left(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_translate_right(game);
	}
}

static void	debug_key(t_game *game, char *key)
{
	printf(BLUE"%15s:"YELLOW"%-3d:"RESET"%-15s:    "BBLUE"\tROTATE %4s\t" \
	RESET"\n", __FILE__, __LINE__, __FUNCTION__, key);
	print_player_infos(game->player, "key rotate");
	print_map_player(game, 5);
}

void	ft_keys_movement_rotations(t_game *game)
{
	bool	rotated;

	rotated = false;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		if (DEBUG_KEYS)
			debug_key(game, "RIGHT");
		game->player->radian += 0.05;
		rotated = !rotated;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		if (DEBUG_KEYS)
			debug_key(game, "LEFT");
		game->player->radian -= 0.05;
		rotated = !rotated;
	}
	if (rotated)
	{
		game->player->radian = normalize_angle(game->player->radian);
		update_player_direction(game->player);
	}
}

/* GAME LOGIC HOOK */
void	ft_loop_hook(void *game_ptr)
{
	t_game			*game;
	static double	last_time = 0;
	double			current_time;

	current_time = mlx_get_time();
	if ((current_time - last_time) < FRAME_TIME)
		return ;
	last_time = current_time;
	game = game_ptr;
	ft_keys_movement_translations(game);
	ft_keys_movement_rotations(game);
	raycast(game);
}
