/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:39:50 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 15:28:33 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "debug.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (DEBUG)
		debug_main_prefix(argv[0]);
	if (argc != 2)
		return (ft_error(__FILE__":", __LINE__, \
												"Bad argument", EXIT_FAILURE));
	create_memory_manager(&data);
	if (init(data, argv[1]) != EXIT_SUCCESS)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
											"init() failure", EXIT_FAILURE));
	init_spawn_player(data->game->player);
	if (DEBUG)
		debug_main_post_parsing(data->game);
	init_mlx(data->game);
	init_textures(data->game);
	mlx_loop(data->game->mlx);
	//mlx_terminate(data->game->mlx);
	memory_manager(DESTROY, NULL, NULL);
	if (DEBUG)
		debug_main_suffix(data->game, argv[0]);
	return (EXIT_SUCCESS);
}

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

void	create_memory_manager(t_data **data)
{
	memory_manager(CREATE, NULL, NULL);
	memory_manager_area_create(ZONE_PARSE, &free, 256);
	memory_manager_area_create(ZONE_FDS, &fd_deletion_func, 10);
	memory_manager_area_create(ZONE_MALLOC_EXEC, &fd_deletion_func, 10);
	memory_manager_area_create(ZONE_MLX, &mlx_deletion_func, 2);
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
