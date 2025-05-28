/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:42:01 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 20:29:24 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//+0.5 pour entrer dans la case
void	center_player_in_current_tile(t_player *player)
{
	player->position[X] = player->position[X] + 0.5;
	player->position[Y] = player->position[Y] + 0.5;
}

void	init_spawn_player(t_player *player)
{
	if (player->facing == 'N')
	{
		player->radian = (3 * M_PI / 2);
		center_player_in_current_tile(player);
	}
	else if (player->facing == 'S')
	{
		player->radian = (M_PI / 2);
		center_player_in_current_tile(player);
	}
	else if (player->facing == 'E')
	{
		player->radian = 0;
		center_player_in_current_tile(player);
	}
	else if (player->facing == 'W')
	{
		player->radian = M_PI;
		center_player_in_current_tile(player);
	}
	else
		nuclear_exit(ft_error(WHERE, "Bad player direction", EXIT_FAILURE));
	update_player_direction(player);
}

void	init_textures(t_game *game)
{
	game->texture->north = mlx_load_png(&game->path->north[3]);
	game->texture->south = mlx_load_png(&game->path->south[3]);
	game->texture->east = mlx_load_png(&game->path->east[3]);
	game->texture->west = mlx_load_png(&game->path->west[3]);
	if (!game->texture->north || !game->texture->south \
		|| !game->texture->east || !game->texture->west)
	{
		nuclear_exit(ft_error(WHERE, "Texture loading failed", EXIT_FAILURE));
	}
	if (game->texture->north->width != 512 \
		|| game->texture->north->height != 512 \
		|| game->texture->south->width != 512 \
		|| game->texture->south->height != 512 \
		|| game->texture->east->width != 512 \
		|| game->texture->east->height != 512 \
		|| game->texture->west->width != 512 \
		|| game->texture->west->height != 512)
	{
		nuclear_exit(ft_error(WHERE, "Texture dimensions must be 512x512", \
																EXIT_FAILURE));
	}
}

void	init_mlx(t_game *game)
{
	mlx_image_t	*img;

	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!game->mlx)
		nuclear_exit(ft_error(WHERE, "mlx_init() failure", EXIT_FAILURE));
	img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, img, 0, 0);
	game->texture->image->img_window = img;
	game->toggles.minimap = false;
	if (mlx_loop_hook(game->mlx, &ft_loop_hook, game))
	{
		game->toggles.catch_mouse_cursor = true;
		if (CAPTURE_MOUSE_ON_STARTUP == true)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		mlx_cursor_hook(game->mlx, &ft_cursor_hook, game);
		mlx_mouse_hook(game->mlx, &ft_mouse_hook, game);
		mlx_key_hook(game->mlx, &ft_keys_hook, game);
	}
	else
		nuclear_exit(ft_error(WHERE, "mlx_loop_hook() failure", EXIT_FAILURE));
}
