/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:39:50 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 15:25:54 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "debug.h"

void	mlx_deletion_func(void *mlx_t_adr)
{
	mlx_terminate(mlx_t_adr);
}

void	fd_deletion_func(void *fd_adr)
{
	int	*i;

	i = fd_adr;
	close(*i);
}

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

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (DEBUG)
		debug_main_prefix(argv[0]);
	if (argc != 2)
		return (ft_error(WHERE, "Bad argument", EXIT_FAILURE));
	create_memory_manager(&data);
	if (init(data, argv[1]) != EXIT_SUCCESS)
		nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));
	init_spawn_player(data->game->player);
	if (DEBUG)
		debug_main_post_parsing(data->game);
	init_mlx(data->game);
	init_textures(data->game);
	mlx_loop(data->game->mlx);
	mlx_terminate(data->game->mlx);
	memory_manager(DESTROY, NULL, NULL);
	if (DEBUG)
		debug_main_suffix(data->game, argv[0]);
	return (EXIT_SUCCESS);
}

void	print_minimap(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_M))
	{
		draw_map(g);
		g->texture->image->player_img->enabled = true;
		g->texture->image->img_window->enabled = true;
	}
	else if (mlx_is_key_down(g->mlx, MLX_KEY_N))
	{
		g->texture->image->player_img->enabled = false;
		g->texture->image->img_window->enabled = false;
	}
}

void	create_memory_manager(t_data **data)
{
	memory_manager(CREATE, NULL, NULL);
	memory_manager_area_create(ZONE_PARSE, &free, 256);
	memory_manager_area_create(ZONE_FDS, &fd_deletion_func, 10);
	memory_manager_area_create(ZONE_MLX, &mlx_deletion_func, 1);
	*data = safe_calloc(ZONE_PARSE, 1, sizeof(t_data));
	(*data)->parse = safe_calloc(ZONE_PARSE, 1, sizeof(t_parsing_map));
	(*data)->game = safe_calloc(ZONE_PARSE, 1, sizeof(t_game));
	(*data)->game->texture = safe_calloc(ZONE_PARSE, 1, sizeof(t_texture));
	(*data)->game->texture->image = safe_calloc(ZONE_PARSE, 1, sizeof(t_image));
	(*data)->game->player = safe_calloc(ZONE_PARSE, 1, sizeof(t_player));
	(*data)->game->path = safe_calloc(ZONE_PARSE, 1, sizeof(t_path));
	(*data)->colors = safe_calloc(ZONE_PARSE, 1, sizeof(t_colors));
	(*data)->game->ray = safe_calloc(ZONE_PARSE, 1, sizeof(t_ray));
	(*data)->game->colors = (*data)->colors;
}
