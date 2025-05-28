/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:00:54 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 11:02:10 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_keys_other_actions(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.action == MLX_PRESS && (keydata.key == MLX_KEY_ESCAPE \
		|| (keydata.key == MLX_KEY_D && keydata.modifier & MLX_CONTROL)))
	{
		mlx_close_window(game->mlx);
	}
}

void	ft_keys_hook(mlx_key_data_t keydata, void *game_data)
{
	t_game	*game;

	game = game_data;
	ft_keys_other_actions(keydata, game);
}
